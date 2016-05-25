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

void DeferredShader::setMvpMatrix( double* mvp )
{
    for( int i = 0; i < 16; i++ )
    {
        _mvpMatrix[ i ] = mvp[ i ];
    }
}

void DeferredShader::setMvMatrix( double* mv )
{
    unsigned int j = 0;
    for( int i = 0; i < 16; i++ )
    {
        _mvMatrix[ i ] = mv[ i ];
    }
}

void DeferredShader::setMMatrix( double* m )
{
    unsigned int j = 0;
    for( int i = 0; i < 16; i++ )
    {
        _mMatrix[ i ] = m[ i ];
    }
}

void DeferredShader::setVMatrix( double* v )
{
    unsigned int j = 0;
    for( int i = 0; i < 16; i++ )
    {
        _vMatrix[ i ] = v[ i ];
    }
}

void DeferredShader::setNormalMatrix( double* normal )
{
    for( int i = 0; i < 9; i++ )
    {
        _normalMatrix[ i ] = normal[ i ];
    }
}

void DeferredShader::setVertices( double* vertices, int n )
{
    _vertex = vertices;
    _nVertices = n;
}


void DeferredShader::setNormal( double* normal )
{
    _normal = normal;
}

void DeferredShader::setEye( double* eye )
{
    _eye[ 0 ] = eye[ 0 ];
    _eye[ 1 ] = eye[ 1 ];
    _eye[ 2 ] = eye[ 2 ];
}

void DeferredShader::setLight( float* lightPosition, float* lightDifuse,
    float* lightSpecular, float* lightAmbient )
{
    memcpy( _lightPosition, lightPosition, 4 * sizeof ( float ) );
    memcpy( _lightDifuse, lightDifuse, 4 * sizeof ( float ) );
    memcpy( _lightSpecular, lightSpecular, 4 * sizeof ( float ) );
    memcpy( _lightAmbient, lightAmbient, 4 * sizeof ( float ) );
}

void DeferredShader::setMaterial( float* materialDifuse,
    float* materialSpecular, float* materialAmbient )
{
    memcpy( _materialDifuse, materialDifuse, 4 * sizeof ( float ) );
    memcpy( _materialSpecular, materialSpecular, 4 * sizeof ( float ) );
    memcpy( _materialAmbient, materialAmbient, 4 * sizeof ( float ) );
}

void DeferredShader::loadVariables( )
{
    if( !isAllocated( ) )
    {
        return;
    }



//    glGenBuffers( 1, &_quad_vertexbuffer );
//    glBindBuffer( GL_ARRAY_BUFFER, _quad_vertexbuffer );
//    glBufferData( GL_ARRAY_BUFFER, sizeof (quadVertices ), quadVertices, GL_STATIC_DRAW );
//    
//    glBindBuffer( GL_ARRAY_BUFFER, _quad_vertexbuffer );
//    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, ( void* ) 0 );
    
    
    unsigned int parameterVertex = glGetAttribLocation( _glShader, "vertex" );
    glBindBuffer( GL_ARRAY_BUFFER, parameterVertex );
    glVertexAttribPointer( parameterVertex, 3, GL_DOUBLE, GL_FALSE, 0, _vertex );
    glEnableVertexAttribArray( parameterVertex );
    
    //
    //    unsigned int parameterNormal = glGetAttribLocation( _glShader, "normal_MS" );
    //    glVertexAttribPointer( parameterNormal, 3, GL_DOUBLE, GL_FALSE, 0, _normal );
    //    glEnableVertexAttribArray( parameterNormal );
    //
    //    //Camera
    //    unsigned int parameterEye = glGetUniformLocation( _glShader, "eyePos_WS" );
    //    glUniform3f( parameterEye, _eye[ 0 ], _eye[ 1 ], _eye[ 2 ] );
    //
    //    
    unsigned int parameterTexture0 = glGetUniformLocation( _glShader, "PositionTex" );
    glUniform1i( parameterTexture0, 0 );
    //
    //    unsigned int parameterTexture3 = glGetUniformLocation( _glShader, "NormalTex" );
    //    glUniform1i( parameterTexture3, 3);
    //    
    //    unsigned int parameterTexture4 = glGetUniformLocation( _glShader, "ColorTex" );
    //    glUniform1i( parameterTexture4, 4 );
    //    
    //    //Material
    //      unsigned int parameterMaterialDifuse = glGetUniformLocation( _glShader, "materialDifuse" );
    //    glUniform4f( parameterMaterialDifuse, _materialDifuse[ 0 ], _materialDifuse[ 1 ], _materialDifuse[ 2 ], _materialDifuse[ 3 ] );
    //
    //    unsigned int parameterMaterialAmbient = glGetUniformLocation( _glShader, "materialAmbient" );
    //    glUniform4f( parameterMaterialAmbient, _materialAmbient[ 0 ], _materialAmbient[ 1 ], _materialAmbient[ 2 ],
    //                 _materialAmbient[ 3 ] );
    //
    //    unsigned int parameterMaterialSpecular = glGetUniformLocation( _glShader, "materialSpecular" );
    //    glUniform4f( parameterMaterialSpecular, _materialSpecular[ 0 ], _materialSpecular[ 1 ], _materialSpecular[ 2 ],
    //                 _materialSpecular[ 3 ] );
    //
    //    //LUZ
    //    unsigned int parameterLightPosition = glGetUniformLocation( _glShader, "lightPos_WS" );
    //    glUniform3f( parameterLightPosition, _lightPosition[ 0 ], _lightPosition[ 1 ], _lightPosition[ 2 ] );
    //
    //    unsigned int parameterLightDifuse = glGetUniformLocation( _glShader, "lightDifuse" );
    //    glUniform4f( parameterLightDifuse, _lightDifuse[ 0 ], _lightDifuse[ 1 ], _lightDifuse[ 2 ], _lightDifuse[ 3 ] );
    //
    //    unsigned int parameterLightAmbient = glGetUniformLocation( _glShader, "lightAmbient" );
    //    glUniform4f( parameterLightAmbient, _lightAmbient[ 0 ], _lightAmbient[ 1 ], _lightAmbient[ 2 ],
    //                 _lightAmbient[ 3 ] );
    //
    //    unsigned int parameterLightSpecular = glGetUniformLocation( _glShader, "lightSpecular" );
    //    glUniform4f( parameterLightSpecular, _lightSpecular[ 0 ], _lightSpecular[ 1 ], _lightSpecular[ 2 ],
    //                 _lightSpecular[ 3 ] );
    //
    //
    //    //Matrizes
    //    unsigned int parameterMvp = glGetUniformLocation( _glShader, "mvp" );
    //    glUniformMatrix4fv( parameterMvp, 1, GL_FALSE, _mvpMatrix );
    //
    //    unsigned int parameterMv = glGetUniformLocation( _glShader, "mv" );
    //    glUniformMatrix4fv( parameterMv, 1, GL_FALSE, _mvMatrix );
    //
    //    unsigned int parameterM = glGetUniformLocation( _glShader, "m" );
    //    glUniformMatrix4fv( parameterM, 1, GL_FALSE, _mMatrix );
    //
    //    unsigned int parameterV = glGetUniformLocation( _glShader, "v" );
    //    glUniformMatrix4fv( parameterV, 1, GL_FALSE, _vMatrix );
    //
    //    unsigned int parameterNM = glGetUniformLocation( _glShader, "normalMatrix" );
    //    glUniformMatrix3fv( parameterNM, 1, GL_FALSE, _normalMatrix );
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

void DeferredShader::setShaderPrograms( std::string vertexShaderFileName,
    std::string fragmentShaderFileName )
{
    std::string vertexShader = readFile( vertexShaderFileName.c_str( ) );
    std::string fragmentShader = readFile( fragmentShaderFileName.c_str( ) );


    std::cout << "Vertex Shader" << std::endl;
    std::cout << vertexShader << std::endl << std::endl << std::endl;
    std::cout << "Fragment Shader" << std::endl;
    std::cout << fragmentShader << std::endl << std::endl << std::endl;

    //Define os programas.
    if( vertexShader.size( ) > 0 )
    {
        setVertexProgram( vertexShader.c_str( ), vertexShader.size( ) );
    }
    if( fragmentShader.size( ) > 0 )
    {
        setFragmentProgram( fragmentShader.c_str( ), fragmentShader.size( ) );
    }
}

unsigned int DeferredShader::getShaderId( )
{
    return _glShader;
}

