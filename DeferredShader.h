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


    void setVertices( double* vertices, int n );

    void setEye( double* eye );

    void setLight( float* lightPosition, float* lightDifuse,
                   float* lightSpecular, float* lightAmbient,
                    unsigned int nLight);
    
   
    void loadVariables();
    
private:


    std::string readFile( const char* name );

    double* _vertex;
    int _nVertices;

    float _eye[ 3 ];

    float *_lightPosition;
    float *_lightDifuse;
    float *_lightSpecular;
    float *_lightAmbient;
    unsigned int _nLight;

};

#endif 

