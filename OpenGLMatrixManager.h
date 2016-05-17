/*
 * File:   OpenGLMA.h
 * Author: jcoelho
 *
 * Created on June 7, 2013, 2:32 PM
 */

#ifndef OPENGLMatrxManager_H
#define OPENGLMatrxManager_H

#include <stack>

#include "Math4f.h"

class OpenGLMatrixManager
{
public:

    /**
     * Construtor default.
     */
    OpenGLMatrixManager();

    /**
     * Destrutor.
     */
    ~OpenGLMatrixManager();

    /**
     * Empilha a matriz corrente e coloca uma identidade como corrente.
     */
    void push();

    /**
     * Retira a matriz corrente do topo.
     */
    void pop();

    /**
     * Carrega a matriz identidade na matriz corrente.
     */
    void loadIdentity();

    /**
     * Carrega a matriz m no lugar da matriz corrente.
     * @param m - matriz passada por parametro.
     */
    void loadMatrix( const double* m );

    /**
     * Multiplica a matriz corrente pela matriz m.
     * @param m - matriz passada por parametro.
     */
    void multMatrix( const double* m );

    /**
     * Aplica a operacao de translacao na matriz corrente.
     * @param x - coordenada x para o novo ponto de translacao.
     * @param y - coordenada y para o novo ponto de translacao.
     * @param z - coordenada z para o novo ponto de translacao.
     */
    void translate( double x, double y, double z );

    /**
     * Aplica uma esacala nas tres direcoes na matriz corrente.
     * @param x - valor de escala aplicado na direcao x.
     * @param y - valor de escala aplicado na direcao y.
     * @param z - valor de escala aplicado na direcao z.
     */
    void scale( double x, double y, double z );

    /**
     * Aplica a operacao de rotacao de um angulo em torno do vetor
     * (x, y, z).
     * @param a - angulo de rotacao.
     * @param (x, y, z) - vetor de rotacao.
     */
    void rotate( double a, double x, double y, double z );

    /**
     * Define as configuracoes da camera. Equivalente ao gluLookAt.
     * @param (eyeX, eyeY, eyeZ) - posicao do observador.
     * @param (centerX, centerY, centerY) - ponto de referencia para onde o
     * observador esta olhando.
     * @param (upX, upY, upZ) - vetor normal a "cabeca" do usuario.
     */
    void lookAt( double eyeX, double eyeY, double eyeZ,
                 double centerX, double centerY, double centerZ,
                 double upX, double upY, double upZ );

    /**
     * Descreve uma matriz de pespectiva para produzir a uma projecao em pespectiva.
     * Equivalente ao glFrustum.
     * @param (xMin, yMin) - ponto minimo.
     * @param (xMax, yMin) - ponto maximo.
     * @param zNear - distancia minima para o observador.
     * @param zFar - distancia maxima para o observador.
     */
    void frustum( double xMin, double xMax, double yMin, double yMax, double zNear, double zFar );

    /**
     * Matriz ortografica a ser multiplicada com a matriz corrente.
     * Equivalente ao glFrustum.
     * @param (left, right) - ponto minimo.
     * @param (bottom, top) - ponto maximo.
     * @param nearVal - distancia minima para o observador.
     * @param farVal - distancia maxima para o observador.
     */
    void ortho( double left, double right, double bottom, double top, double nearVal, double farVal );

    /**
     * Define a pespectiva.
     * @param fovY - angulo de abertura do eixo y.
     * @param aspect - razao de aspecto. w/h.
     * @param znear - distancia minima pro observador.
     * @param zfar - distancia maxima pro observador.
     */
    void perspective( double fovY, double aspect, double zNear, double zFar );

    /**
     * Retorna a matrix corrente.
     * @param m - variavel onde sera armazenada a matriz corrente.
     */
    void getMatrix( double* m );

    /**
     * Obtem a matrix inversa transposta.
     * @param mit - matriz inversa transposta.
     */
    void getMatrixInverseTransposed( double* mit );

    /**
     * Calcula a matriz inversa e a retorna.
     * @return - matriz inversa da matriz corrente.
     */
    Math4f getMatrixInverse();

    /**
     * Calcula o ponto transformado pela matriz corrente.
     * @param point - ponto a ser transformado.
     * @return - ponto resultante da transformacao.
     */
    // Point3Dd operator*( const Point3Dd point );

    /**
     * Retorna a matrix em double *.
     * @return
     */
    operator double*()
    {
        return ( double* ) _currentMatrix;
    }

    /**
     * Retorna a matrix em double *.
     * @return
     */
    operator const double*() const
    {
        return ( const double* ) _currentMatrix;
    }

    double* getMatrix()
    {
        return _currentMatrix.getMatrix();
    }


private:
    /**
     * Pilha de matrizes
     */
    std::stack< Math4f > _matrixStack;

    /**
     * Matriz corrente
     */
    Math4f _currentMatrix;

private:
    /**
     * Realiza o produto vetorial entre dois vetores.
     * @param x1, y1, z1 - vetor 1.
     * @param x2, y2, z2 - vetor 1.
     * @param [out] - x, y, z - vetor de saida.
     */
    void computeCrossProduct( double x1, double y1, double z1,
                              double x2, double y2, double z2,
                              double& x, double& y, double& z );
};

#endif  /* OPENGLMatrxManager_H */