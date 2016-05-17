#include "OpenGLMatrixManager.h"
#include <cstring>
#include <cmath>



void OpenGLMatrixManager::computeCrossProduct( double x1, double y1, double z1,
                                               double x2, double y2, double z2,
                                               double& x, double& y, double& z )
{
    x = y1 * z2 - z1 * y2;
    y = z1 * x2 - x1 * z2;
    z = x1 * y2 - y1 * x2;
}


OpenGLMatrixManager::OpenGLMatrixManager()
{
}


OpenGLMatrixManager::~OpenGLMatrixManager()
{
}


void OpenGLMatrixManager::push()
{
//    //Empilha uma copia da matriz corrente.
    _matrixStack.push( _currentMatrix );
}


void OpenGLMatrixManager::pop()
{
    //Torna a matriz do topo da pilha como matriz corrente.
    if( !_matrixStack.empty() )
    {
        _currentMatrix = _matrixStack.top();
        _matrixStack.pop();
    }
}


void OpenGLMatrixManager::loadIdentity()
{
    //Carrega a matriz identidade.
    _currentMatrix.loadIdentity();
}


void OpenGLMatrixManager::loadMatrix( const double* m )
{
    _currentMatrix.setMatrix( m );
}


void OpenGLMatrixManager::multMatrix( const double* m )
{
    _currentMatrix = _currentMatrix * Math4f( m );
}


void OpenGLMatrixManager::translate( double x, double y, double z )
{
    //Constroi a matriz de translacao.
    Math4f translateMatrix;
    translateMatrix.at( 3, 0 ) = x;
    translateMatrix.at( 3, 1 ) = y;
    translateMatrix.at( 3, 2 ) = z;
    translateMatrix.at( 3, 3 ) = 1;

    //Multiplica pela matriz corrente.
    _currentMatrix = _currentMatrix * translateMatrix;
}


void OpenGLMatrixManager::scale( double x, double y, double z )
{
    //Constroi a matriz de escala.
    Math4f scaleMatrix;
    scaleMatrix.at( 0, 0 ) = x;
    scaleMatrix.at( 1, 1 ) = y;
    scaleMatrix.at( 2, 2 ) = z;
    scaleMatrix.at( 3, 3 ) = 1;

    //Multiplica pela matriz corrente.
    _currentMatrix = _currentMatrix * scaleMatrix;
}


void OpenGLMatrixManager::rotate( double a, double x, double y, double z )
{
    //Fonte: http://www.opengl.org/sdk/docs/man2/xhtml/glRotate.xml

    //Converte o angulo para radianos
    double angle = a * M_PI / 180.0;

    double c = cos( ( double ) angle );
    double s = sin( ( double ) angle );
    double lenght = sqrt( x * x + y * y + z * z );

    //Se o vetor for nulo nao faz nada.
    if( lenght < 10E-5 )
    {
        return;
    }

    //Normaliza o vetor passado.
    x /= lenght;
    y /= lenght;
    z /= lenght;

    //Constroi a matriz de rotacao.
    double m[ 16 ] = {
        x* x* ( 1 - c ) + c, y * x * ( 1 - c ) + z * s, x * z * ( 1 - c ) - y * s, 0,
        x * y * ( 1 - c ) - z * s, y * y * ( 1 - c ) + c, y * z * ( 1 - c ) + x * s, 0,
        x * z * ( 1 - c ) + y * s, y * z * ( 1 - c ) - x * s, z * z * ( 1 - c ) + c, 0,
        0, 0, 0, 1
    };

    //Multiplica a matriz de rotacao pela matriz corrente.
    _currentMatrix = _currentMatrix * Math4f( m );
}


void OpenGLMatrixManager::lookAt( double eyeX, double eyeY, double eyeZ, double centerX, double centerY, double centerZ,
                                  double upX, double upY, double upZ )
{
    //Fonte: http://www.opengl.org/sdk/docs/man2/xhtml/gluLookAt.xml

    //Calcula vetor f que vai da posicao do observador ao ponto de referencia.
    double fX = centerX - eyeX;
    double fY = centerY - eyeY;
    double fZ = centerZ - eyeZ;

    //Normaliza vetor f.
    double lenghtF = sqrt( fX * fX + fY * fY + fZ * fZ );
    fX /= lenghtF;
    fY /= lenghtF;
    fZ /= lenghtF;

    //Normalizando vetor normal a� cabeca do observador.
    double lenghtUp = sqrt( upX * upX + upY * upY + upZ * upZ );
    upX /= lenghtUp;
    upY /= lenghtUp;
    upZ /= lenghtUp;

    //Calculando vetor S.
    double sX = 0.0, sY = 0.0, sZ = 0.0;
    computeCrossProduct( fX, fY, fZ, upX, upY, upZ, sX, sY, sZ );

    double lenghtS = sqrt( sX * sX + sY * sY + sZ * sZ );

    sX /= lenghtS;
    sY /= lenghtS;
    sZ /= lenghtS;

    //Calculando vetor U.
    double uX = 0.0, uY = 0.0, uZ = 0.0;
    computeCrossProduct( sX, sY, sZ, fX, fY, fZ, uX, uY, uZ );

    //Montando a matriz M.
    double m[ 16 ] = {
        ( double ) sX, ( double ) uX, -( double ) fX, 0.0f,
        ( double ) sY, ( double ) uY, -( double ) fY, 0.0f,
        ( double ) sZ, ( double ) uZ, -( double ) fZ, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    //Multiplica pela matriz corrente.
    _currentMatrix = _currentMatrix * Math4f( m );

    //Faz uma translacao inversa em relacao a posicao do observador.
    translate( -eyeX, -eyeY, -eyeZ );
}


void OpenGLMatrixManager::frustum( double left, double right, double bottom, double top, double nearVal, double farVal )
{
    //Fonte: http://www.opengl.org/sdk/docs/man2/xhtml/glFrustum.xml

    //Monta a matriz de frustum.
    double f[ 16 ] = {
        2 * nearVal / ( right - left ), 0, 0, 0,
        0, 2 * nearVal / ( top - bottom ), 0, 0,
        ( right + left ) / ( right - left ), ( top + bottom ) / ( top - bottom ),
        -( farVal + nearVal ) / ( farVal - nearVal ), -1,
        0, 0, -( 2 * farVal * nearVal ) / ( farVal - nearVal ), 0
    };

    //Multiplica pela matriz corrente.
    _currentMatrix = _currentMatrix * Math4f( f );
}


void OpenGLMatrixManager::ortho( double left, double right, double bottom, double top, double nearVal, double farVal )
{
    //Fonte: http://www.opengl.org/sdk/docs/man2/xhtml/glOrtho.xml

    //Constroi a matriz de projecao ortografica.
    double o[ 16 ] = {
        2 / ( right - left ), 0, 0, 0,
        0, 2 / ( top - bottom ), 0, 0,
        0, 0, -2 / ( farVal - nearVal ), 0,
        -( right + left ) / ( right - left ), -( top + bottom ) / ( top - bottom ),
        -( farVal + nearVal ) / ( farVal - nearVal ), 1
    };

    //Multiplica pela matriz corrente.
    _currentMatrix = _currentMatrix * Math4f( o );
}


void OpenGLMatrixManager::perspective( double fovY, double aspect, double zNear, double zFar )
{
    //Fonte: http://www.opengl.org/sdk/docs/man2/xhtml/gluPerspective.xml

    //Converte para radianos.
    double angle = fovY * M_PI / 180.0;

    //Calcula a contange.
    double f = 1.0 / tan( angle / 2.0 );

    double p[ 16 ] = {
        ( double ) ( f / aspect ), 0.0f, 0.0f, 0.0f,
        0.0f, ( double ) f, 0.0f, 0.0f,
        0.0f, 0.0f, ( zFar + zNear ) / ( zNear - zFar ), -1.0f,
        0.0f, 0.0f, ( 2.0f * zFar * zNear ) / ( zNear - zFar ), 0.0f
    };

    //Multiplica pela matriz corrente.
    _currentMatrix = _currentMatrix * Math4f( p );
}


void OpenGLMatrixManager::getMatrix( double* m )
{
    memcpy( m, ( const double* ) _currentMatrix, 16 * sizeof ( double ) );
}


void OpenGLMatrixManager::getMatrixInverseTransposed( double* mit )
{
    //Fonte:http://www.tecgraf.puc-rio.br/~celes/inf2610/Home_files/transformacao.pdf
    //Notas de aula do professor Waldemar Celes, pagina 18

    //Calcula a inversa transposta para transformar as normais.
    Math4f matInverseTransposed = _currentMatrix.inverse();
    matInverseTransposed = matInverseTransposed.transposed();
    memcpy( mit, ( double* ) matInverseTransposed, sizeof ( double ) * 3 );
    memcpy( mit + 3, ( double* ) matInverseTransposed + 4, sizeof ( double ) * 3 );
    memcpy( mit + 6, ( double* ) matInverseTransposed + 8, sizeof ( double ) * 3 );
}


Math4f OpenGLMatrixManager::getMatrixInverse()
{
    return _currentMatrix.inverse();
}


//Point3Dd OpenGLMatrixManager::operator*( const Point3Dd point )
//{
//    return _currentMatrix * point;
//}
