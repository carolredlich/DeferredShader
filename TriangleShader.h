/*
 * File:   SphereShader.h
 * Author: caroline
 *
 * Created on 8 de Abril de 2016, 10:53
 */

#ifndef TRIANGLESHADER_H
#define TRIANGLESHADER_H

#include "GraphicsShader.h"
#include <string>

class TriangleShader :
    public GraphicsShader
{
public:
    TriangleShader( std::string vertexShaderFileName = "sphere.vert",
                  std::string fragmentShaderFileName = "sphere.frag" );

    TriangleShader( const TriangleShader& orig );

    virtual ~TriangleShader();

    void setMvpMatrix( double* mvp );

    void setMMatrix( double* m );

    void setVertices( double* vertices, int n );

    void setNormal( double* normal );

    void setMaterial( float* materialDifuse,
                   float* materialSpecular, float* materialAmbient );
    
    
    void setTexCoord( double* texCoord );

    void setTangentAndBitangent( double* tangent, double* bitangent );
    
    void loadVariables();
    
private:


    std::string readFile( const char* name );

    float _mvpMatrix[ 16 ];

    float _mMatrix[ 16 ];

    double* _vertex;
    int _nVertices;
    double* _normal;
    
    
    double* _texCoords;
    double* _tangent;
    double* _bitangent;


    float _materialDifuse[ 3 ];
    float _materialSpecular[ 3 ];
    float _materialAmbient[ 3 ];
};

#endif  /* TRIANGLESHADER_H */

