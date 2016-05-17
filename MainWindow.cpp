#include "MainWindow.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <math.h>
#include "Vec3.h"

MainWindow::MainWindow()
{
    _textureImg[ 0 ] = imgReadBMP( ( char* ) "bola.bmp" );
    _textureImg[ 1 ] = imgReadBMP( ( char* ) "bolabumpNormal.bmp" );

//        _textureImg[0] = imgReadBMP( ( char* ) "bolafutebol.bmp" );
//        _textureImg[1] = imgReadBMP( ( char* ) "bolafutebolnormal.bmp" );

    //Cria janela e define suas configuracoes.
    createWindow();


    //Cria o shader
    SphereShader* shader = new SphereShader();

    //Cria uma superficie e insere na lista de superficies
    _surface.push_back( Surface( shader ) );
//    _surface.push_back( Surface( "esfera3.off", shader ) );
}


void MainWindow::createWindow()
{
    //Cria botao de sair.
    Ihandle* exitButton = IupButton( "Sair", NULL );

    //Cria canvas.
    Ihandle* canvas = IupGLCanvas( NULL );

    //Cria composicao para o botao.
    Ihandle* hboxButton = IupHbox( IupFill(), exitButton, NULL );

    //Cria composicao final.
    Ihandle* vboxFinal = IupVbox( canvas, hboxButton, NULL );

    //Cria dialogo.
    _dialog = IupDialog( vboxFinal );

    //Define os atributos do botao
    IupSetAttribute( exitButton, IUP_RASTERSIZE, "80x32" );
    IupSetAttribute( exitButton, IUP_TIP, "Fecha a janela." );

    //Define os atributos do canvas.
    IupSetAttribute( canvas, IUP_RASTERSIZE, "800x600" );
    IupSetAttribute( canvas, IUP_BUFFER, IUP_DOUBLE );
    IupSetAttribute( canvas, IUP_EXPAND, IUP_YES );

    //Define propriedades do dialogo.
    IupSetAttribute( _dialog, IUP_MARGIN, "10x10" );
    IupSetAttribute( _dialog, IUP_TITLE, "Trabalho 1" );
    IupSetAttribute( _dialog, "THIS", ( char* ) this );

    //Define callbacks do botao.
    IupSetCallback( exitButton, IUP_ACTION, ( Icallback ) exitButtonCallback );

    //Define as callbacks do canvas.
    IupSetCallback( canvas, IUP_ACTION, ( Icallback ) actionCanvasCallback );
    IupSetCallback( canvas, IUP_RESIZE_CB, ( Icallback ) resizeCanvasCallback );
    IupSetCallback( canvas, IUP_BUTTON_CB, ( Icallback ) buttonCanvasCallback );
    IupSetCallback( canvas, IUP_WHEEL_CB, ( Icallback ) wheelCanvasCallback );

    //Mapeia o dialogo.
    IupMap( _dialog );

    //Torna o canvas como corrente.
    IupGLMakeCurrent( canvas );

    //Incialia propriedades dos canvas.
    initializeCanvas();
}


MainWindow::~MainWindow()
{
    IupDestroy( _dialog );
}


void MainWindow::show()
{
    IupShow( _dialog );
}


void MainWindow::hide()
{
    IupHide( _dialog );
}


void MainWindow::initializeCanvas()
{
    glClearColor( 0, 0, 0, 1.0 );

    int numTex = 2;

    //Gera um objeto de textura.
    glGenTextures( numTex, _textureId );

    for( unsigned int i = 0; i < numTex; i++ )
    {
        //Faz com que o objeto de textura criado seja o corrente.
        glBindTexture( GL_TEXTURE_2D, _textureId[ i ] );

        //Aloca cores para a textura.
        GLfloat* textura = imgGetData( _textureImg[ i ] );

        //Constroi textura e mipmap
        gluBuild2DMipmaps( GL_TEXTURE_2D, 3, imgGetWidth( _textureImg[ i ] ),
                           imgGetHeight( _textureImg[ i ] ), GL_RGB, GL_FLOAT, imgGetData( _textureImg[ i ] ) );

        // Define os filtros de magnificacao e minificacao
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );

        // Seleciona o modo de aplicacao da textura
        glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE );
        //        glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_INTERPOLATE);

        // Ajusta os parametros de repetição
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    }
}


void MainWindow::drawScene()
{
    glEnable( GL_DEPTH_TEST );
    //Limpa a janela.
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


    //Define parâmetros da luz
    float lightPosition[ 4 ] = { 4, 4, 6, 1 };
    float lightDifuse[ 4 ] = { 0.6, 0.6, 0.6, 1.0 };
    float lightSpecular[ 4 ] = { 1, 1, 1, 1.0 };
    float lightAmbient[ 4 ] = { 0.1, 0.1, 0.1, 1.0 };

    //Descomentar caso queira ver os triangulos
//    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    //Carrega a identidade na model view
    _modelViewMatrix.loadIdentity();
    _viewMatrix.loadIdentity();
    _modelMatrix.loadIdentity();

    //Define a posição da câmera
    //Descomentar o que quiser usar
    //Basquete
//    double eye[ 3 ] = { 2, 2, 3 };
//                double eye[3] = {15, 2, 15 };

    //double eye[3] = {0, 0, 3}; //1 bola
                double eye[3] = {3, 0, 0 }; //1 bola
    //    double eye[3] = { 0, 3, 0.1 }; //1 bola

    //Futebol
    //            double eye[3] = {-15,  2, 0 };
    //            double eye[3] = {-15, 2, 7 };


    //            double eye[3] = {0, 0, 3 }; //1 bola
    //            double eye[3] = {0, -3, 0.1 }; //1 bola

    //Define a câmera
    _viewMatrix.lookAt( eye[ 0 ], eye[ 1 ], eye[ 2 ], 0, 0, 0, 0, 1, 0 );


    unsigned int numSpheres = 1;
    for( unsigned int i = 0; i < numSpheres; i++ )
    {
        for( unsigned int j = 0; j < numSpheres; j++ )
        {
            //Se o shader não estiver alocado, compila
            if( !_surface[ 0 ]._shader->isAllocated() )
            {
                _surface[ 0 ]._shader->compileShader();
            }
            //Passa a posicao da câmera pro shader
            _surface[ 0 ]._shader->setEye( eye );

            //Passa os parametros da luz pro shader
            _surface[ 0 ]._shader->setLight( lightPosition, lightDifuse, lightSpecular, lightAmbient );

            //Passa os vértices da superficie para o shader
            _surface[ 0 ]._shader->setVertices( &_surface[ 0 ]._vertex[ 0 ], _surface[ 0 ]._vertex.size() / 3 );

            //Seta a normal dos vértices da superficie para o shader
            _surface[ 0 ]._shader->setNormal( &_surface[ 0 ]._normal[ 0 ] );

            //Seta as coordenadas de textura dos vértices da superficie para o shader
            _surface[ 0 ]._shader->setTexCoord( &_surface[ 0 ]._texCoord[ 0 ] );

            //Seta as tangentes e bitangentes dos vértices da superficie para o shader
            _surface[ 0 ]._shader->setTangentAndBitangent( &_surface[ 0 ]._tangent[ 0 ],
                                                           &_surface[ 0 ]._bitangent[ 0 ] );

            _surface[ 0 ]._shader->setVMatrix( _viewMatrix );

            _projectionMatrix.push();
            _modelMatrix.push();
            _viewMatrix.push();

            //Se estou desenhando mais de 1 esfera, tenho que translada-las
            if( numSpheres > 1 )
            {
                _modelMatrix.translate( -( float ) numSpheres + i * 2.4, 0, -( float ) numSpheres + j * 2.4 );
            }

            _viewMatrix.multMatrix( _modelMatrix );

            _projectionMatrix.multMatrix( _viewMatrix );

            _surface[ 0 ]._shader->setMvpMatrix( _projectionMatrix );

            _surface[ 0 ]._shader->setMvMatrix( _viewMatrix );


            //Pega a matriz que transforma a normal
            double normal[ 9 ];
            _viewMatrix.getMatrixInverseTransposed( normal );
            _surface[ 0 ]._shader->setNormalMatrix( normal );

            _viewMatrix.pop();

            _surface[ 0 ]._shader->setMMatrix( _modelMatrix );

            _modelMatrix.pop();
            _projectionMatrix.pop();

            _surface[ 0 ]._shader->load();
            _surface[ 0 ]._shader->loadVariables();

            //Habilita o uso de textura 1D.
            glEnable( GL_TEXTURE_2D );
            //Cria um objeto de textura de indice 0
            glActiveTexture( GL_TEXTURE0 );
            //Faz com que o objeto de textura criado seja o corrente.
            glBindTexture( GL_TEXTURE_2D, _textureId[ 0 ] );
            //Cria um objeto de textura com indice 1s
            glActiveTexture( GL_TEXTURE1 );
            //Faz com que o objeto de textura criado seja o corrente.
            glBindTexture( GL_TEXTURE_2D, _textureId[ 1 ] );

            //Desenha a superficie
            glDrawElements( GL_TRIANGLES,
                            _surface[ 0 ]._triangles.size(), GL_UNSIGNED_INT, &_surface[ 0 ]._triangles[ 0 ] );

            _surface[ 0 ]._shader->unload();

            //Desabilita o uso de textura.
            glDisable( GL_TEXTURE_2D );
        }
    }
}


void MainWindow::resizeCanvas( int width, int height )
{
    //Define o viewport.
    glViewport( 0, 0, width, height );

    _projectionMatrix.loadIdentity();

    double angle = 60;
    // Para previnir uma divisão por zero
    if( height == 0 )
    {
        height = 1;
    }
    double fAspect = ( double ) width / height;
    _projectionMatrix.perspective( angle, fAspect, 0.5, 500 );
}


int MainWindow::exitButtonCallback( Ihandle* button )
{
    return IUP_CLOSE;
}


int MainWindow::actionCanvasCallback( Ihandle* canvas )
{
    //Torna o canvas como corrente.
    IupGLMakeCurrent( canvas );

    //Obtem ponteiro para o this.
    MainWindow* window = ( MainWindow* ) IupGetAttribute( canvas, "THIS" );

    //Redesenha a janela.
    window->drawScene();

    //Troca os buffers.
    IupGLSwapBuffers( canvas );

    return IUP_DEFAULT;
}


int MainWindow::resizeCanvasCallback( Ihandle* canvas, int width, int height )
{
    //Torna o canvas como corrente.
    IupGLMakeCurrent( canvas );

    //Obtem ponteiro para o this.
    MainWindow* window = ( MainWindow* ) IupGetAttribute( canvas, "THIS" );

    //Redesenha a janela.
    window->resizeCanvas( width, height );

    //Marca o canvas para ser redesenhado.
    IupUpdate( canvas );

    return IUP_DEFAULT;
}


int MainWindow::buttonCanvasCallback( Ihandle* canvas, int button, int pressed,
                                      int x, int y, char* status )
{
    return IUP_DEFAULT;
}


int MainWindow::wheelCanvasCallback( Ihandle* canvas, float delta, int x,
                                     int y, char* status )
{
    return IUP_DEFAULT;
}


