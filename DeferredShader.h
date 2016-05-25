/*
 * File:   SphereShader.h
 * Author: caroline
 *
 * Created on 8 de Abril de 2016, 10:53
 */

#ifndef DEFERREDSHADER_H
#define DEFERREDSHADER_H

#include "GraphicsShader.h"
#include <string>

class DeferredShader :
    public GraphicsShader
{
public:
    DeferredShader( std::string vertexShaderFileName = "sphere.vert",
                  std::string fragmentShaderFileName = "sphere.frag" );

    DeferredShader( const DeferredShader& orig );

    virtual ~DeferredShader();

    void setMvpMatrix( double* mvp );

    void setMvMatrix( double* mv );

    void setMMatrix( double* m );

    void setVMatrix( double* v );

    void setNormalMatrix( double* normal );

    void setVertices( double* vertices, int n );

    void setNormal( double* normal );

    void setEye( double* eye );

    void setLight( float* lightPosition, float* lightDifuse,
                   float* lightSpecular, float* lightAmbient );
    
    void setMaterial( float* materialDifuse,
                   float* materialSpecular, float* materialAmbient );
    
    void setShaderPrograms( std::string vertexShaderFileName = "sphere.vert",
                  std::string fragmentShaderFileName = "sphere.frag" );

    void loadVariables();
    
    unsigned int getShaderId();

private:


    std::string readFile( const char* name );

    float _mvpMatrix[ 16 ];

    float _mvMatrix[ 16 ];

    float _mMatrix[ 16 ];

    float _vMatrix[ 16 ];

    float _normalMatrix[ 9 ];

    double* _vertex;
    int _nVertices;

    double* _normal;


    float _eye[ 3 ];

    float _lightPosition[ 4 ];
    float _lightDifuse[ 4 ];
    float _lightSpecular[ 4 ];
    float _lightAmbient[ 4 ];

    float _materialDifuse[ 4 ];
    float _materialSpecular[ 4 ];
    float _materialAmbient[ 4 ];
};

#endif  /* TRIANGLESHADER_H */

