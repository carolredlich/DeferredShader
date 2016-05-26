/*
 * File:   DeferredShader.cpp
 * Author: caroline
 *
 * Created on 8 de Abril de 2016, 10:53
 */

#include <cstring>
#include <cmath>
#include <string>
#include <cstdio>
#include <fstream>
#include <iostream>

#include "DeferredShader.h"

DeferredShader::DeferredShader( std::string vertexShaderFileName,
    std::string fragmentShaderFileName )
{
    std::string vertexShader = readFile( vertexShaderFileName.c_str( ) );
    std::string tesseletionControlShader = readFile( "triangle.tcs" );
    std::string tesseletionEvaluationShader = readFile( "triangle.tes" );
    std::string geometryShader = readFile( "triangle.geom" );
    std::string fragmentShader = readFile( fragmentShaderFileName.c_str( ) );


    std::cout << "Vertex Shader" << std::endl;
    std::cout << vertexShader << std::endl << std::endl << std::endl;
    std::cout << "Tesseletion Control Shader" << std::endl;
    std::cout << tesseletionControlShader << std::endl << std::endl << std::endl;
    std::cout << "Tesseletion Evaluation Shader" << std::endl;
    std::cout << tesseletionEvaluationShader << std::endl << std::endl << std::endl;
    std::cout << "Geometry Shader" << std::endl;
    std::cout << geometryShader << std::endl << std::endl << std::endl;
    std::cout << "Fragment Shader" << std::endl;
    std::cout << fragmentShader << std::endl << std::endl << std::endl;

    //Define os programas.
    if( vertexShader.size( ) > 0 )
    {
        setVertexProgram( vertexShader.c_str( ), vertexShader.size( ) );
    }
    if( tesseletionControlShader.size( ) > 0 )
    {
        setTesselationControlProgram( tesseletionControlShader.c_str( ), tesseletionControlShader.size( ) );
    }
    if( tesseletionEvaluationShader.size( ) > 0 )
    {
        setTesselationEvaluationProgram( tesseletionEvaluationShader.c_str( ), tesseletionEvaluationShader.size( ) );
    }
    if( geometryShader.size( ) > 0 )
    {
        setGeometryProgram( geometryShader.c_str( ), geometryShader.size( ) );
    }
    if( fragmentShader.size( ) > 0 )
    {
        setFragmentProgram( fragmentShader.c_str( ), fragmentShader.size( ) );
    }

    //Define os atributos para o geomtry shader.
    setGeometryParameters( GL_TRIANGLES, GL_TRIANGLE_STRIP, 3 );
}

DeferredShader::DeferredShader( const DeferredShader& orig ) { }

DeferredShader::~DeferredShader( ) { }

void DeferredShader::setVertices( double* vertices, int n )
{
    _vertex = vertices;
    _nVertices = n;
}

void DeferredShader::setEye( double* eye )
{
    _eye[ 0 ] = eye[ 0 ];
    _eye[ 1 ] = eye[ 1 ];
    _eye[ 2 ] = eye[ 2 ];
}

void DeferredShader::setLight( float* lightPosition, float* lightDifuse,
    float* lightSpecular, float* lightAmbient, unsigned int nLight )
{
    
    _lightPosition = lightPosition;
    _lightDifuse = lightDifuse;
    _lightSpecular = lightSpecular;
    _lightAmbient = lightAmbient;
    _nLight = nLight;
}


void DeferredShader::loadVariables( )
{
    if( !isAllocated( ) )
    {
        return;
    }

    unsigned int parameterVertex = glGetAttribLocation( _glShader, "vertex" );
    glBindBuffer( GL_ARRAY_BUFFER, parameterVertex );
    glVertexAttribPointer( parameterVertex, 3, GL_DOUBLE, GL_FALSE, 0, _vertex );
    glEnableVertexAttribArray( parameterVertex );

    //Camera
    unsigned int parameterEye = glGetUniformLocation( _glShader, "eyePos_WS" );
    glUniform3f( parameterEye, _eye[ 0 ], _eye[ 1 ], _eye[ 2 ] );

    unsigned int parameterTexture0 = glGetUniformLocation( _glShader, "PositionTex" );
    glUniform1i( parameterTexture0, 0 );

    unsigned int parameterTexture1 = glGetUniformLocation( _glShader, "NormalTex" );
    glUniform1i( parameterTexture1, 1 );

    unsigned int parameterTexture2 = glGetUniformLocation( _glShader, "DifTex" );
    glUniform1i( parameterTexture2, 2 );

    unsigned int parameterTexture3 = glGetUniformLocation( _glShader, "AmbTex" );
    glUniform1i( parameterTexture3, 3 );

    unsigned int parameterTexture4 = glGetUniformLocation( _glShader, "SpecTex" );
    glUniform1i( parameterTexture4, 4 );

    //LUZ
    unsigned int parameterLightPosition = glGetUniformLocation( _glShader, "lightPos_WS" );
    glUniform3fv( parameterLightPosition, _nLight, _lightPosition );

    unsigned int parameterLightDifuse = glGetUniformLocation( _glShader, "lightDifuse" );
    glUniform3fv( parameterLightDifuse, _nLight, _lightDifuse );

    unsigned int parameterLightAmbient = glGetUniformLocation( _glShader, "lightAmbient" );
    glUniform3fv( parameterLightAmbient, _nLight, _lightAmbient );

    unsigned int parameterLightSpecular = glGetUniformLocation( _glShader, "lightSpecular" );
    glUniform3fv( parameterLightSpecular, _nLight, _lightSpecular);

    unsigned int parameterNLight = glGetUniformLocation( _glShader, "nLight" );
    glUniform1i( parameterNLight, _nLight );
}

std::string DeferredShader::readFile( const char* name )
{
    std::ifstream in( name );
    std::string shader;

    if( in.fail( ) )
    {
        return "";
    }

    char a;
    while( in.get( a ) && a != EOF )
    {
        shader += a;
    }
    shader += '\0';
    return shader;
}