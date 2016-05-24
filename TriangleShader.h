/*
 * File:   SphereShader.h
 * Author: caroline
 *
 * Created on 8 de Abril de 2016, 10:53
 */

#ifndef SPHERESHADER_H
#define SPHERESHADER_H

#include "GraphicsShader.h"
#include <string>

class TriangleShader :
    public GraphicsShader
{
public:
    TriangleShader( std::string vertexShaderFileName = "sphere.vert",
                  std::string geometryShaderFileName = "sphere.geom",
                  std::string fragmentShaderFileName = "sphere.frag" );

    TriangleShader( const TriangleShader& orig );

    virtual ~TriangleShader();

    void setMvpMatrix( double* mvp );

    void setMvMatrix( double* mv );

    void setMMatrix( double* m );

    void setVMatrix( double* v );

    void setNormalMatrix( double* normal );

    void setVertices( double* vertices, int n );

    void setTexCoord( double* texCoord );

    void setNormal( double* normal );

    void setTangentAndBitangent( double* tangent, double* bitangent );

    void setEye( double* eye );

    void setLight( float* lightPosition, float* lightDifuse,
                   float* lightSpecular, float* lightAmbient );
    
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

    double* _texCoords;
    double* _normal;
    double* _tangent;
    double* _bitangent;


    float _eye[ 3 ];

    float _lightPosition[ 4 ];
    float _lightDifuse[ 4 ];
    float _lightSpecular[ 4 ];
    float _lightAmbient[ 4 ];
};

#endif  /* TRIANGLESHADER_H */

