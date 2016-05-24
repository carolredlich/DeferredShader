/*
 * File:   Surface.cpp
 * Author: caroline
 *
 * Created on 25 de Abril de 2016, 12:18
 */

#include "Surface.h"
#include "Vec3.h"


#include <cstdlib>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>

Surface::Surface( TriangleShader* shader )
{
    _shader = shader;

    generateSphereMesh();
    generateTangentsAndBitangents();
}


Surface::~Surface()
{
}


Surface::Surface( std::string fileName, TriangleShader* shader )
{
    loadMesh( fileName );
    _shader = shader;
    generateTangentsAndBitangents();
    generateNormals();
    gererateTexCoords();
}


void Surface::loadMesh( std::string fileName )
{
    //std::ifstream file("icosaedro.off");
    std::ifstream file( fileName.c_str() );
    if( !file )
    {
        std::cout << "Erro ao abrir arquivo" << std::endl;
    }

    char off[ 3 ];
    file >> off;

    int numVertices, numTriangles, trash;

    file >> numVertices >> numTriangles >> trash;
    _vertex.reserve( 3 * numVertices );

    _normal.resize( 3 * numVertices );
    _tangent.resize( 3 * numVertices );
    _bitangent.resize( 3 * numVertices );

    _texCoord.resize( 2 * numVertices );

    srand( time( NULL ) );

    for( unsigned int i = 0; i < numVertices; i++ )
    {
        double x, y, z;
        file >> x >> y >> z;
        _vertex.push_back( x );
        _vertex.push_back( y );
        _vertex.push_back( z );
    }

    for( unsigned int i = 0; i < numTriangles; i++ )
    {
        int n, v1, v2, v3;
        file >> v1 >> v1 >> v2 >> v3;
        _triangles.push_back( v1 );
        _triangles.push_back( v2 );
        _triangles.push_back( v3 );
    }
}


void Surface::generateSphereMesh()
{
    const int n = 100;
    const int m = 100;

    const int numTriangles = 2 * n * m;
    const int numVertices = ( n + 1 ) * ( m + 1 );

    _triangles.resize( 3 * numTriangles );

    _vertex.resize( 3 * numVertices );
    _normal.resize( 3 * numVertices );
    _tangent.resize( 3 * numVertices );
    _bitangent.resize( 3 * numVertices );

    _texCoord.resize( 2 * numVertices );

    for( unsigned int i = 0; i <= n; i++ )
    {
        for( unsigned int j = 0; j <= m; j++ )
        {
            //Calcula o indice no vetor
            unsigned int k = getVectorIndex( i, j, n );

            //Salva as coordenadas de textura
            _texCoord[ 2 * k + 0 ] = ( double ) i / n;
            _texCoord[ 2 * k + 1 ] = ( double ) j / m;

            //Calcula os parâmetros
            double theta = 2 * _texCoord[ 2 * k + 0 ] * M_PI;
            double phi = _texCoord[ 2 * k + 1 ] * M_PI;
            double sinTheta = sin( theta );
            double cosTheta = cos( theta );
            double sinPhi = sin( phi );
            double cosPhi = cos( phi );

            //Calcula os vértices == equacao da esfera
            _vertex[ 3 * k + 0 ] = cosTheta * sinPhi;
            _vertex[ 3 * k + 1 ] = cosPhi;
            _vertex[ 3 * k + 2 ] = sinTheta * sinPhi;

            //Normal == vertices
            _normal[ 3 * k + 0 ] = _vertex[ 3 * k + 0 ];
            _normal[ 3 * k + 1 ] = _vertex[ 3 * k + 1 ];
            _normal[ 3 * k + 2 ] = _vertex[ 3 * k + 2 ];

//            //Calcula o vertor tangente == dS/DTheta
//            _tangent[3 * k + 0 ] = -sinTheta * sinPhi;
//            _tangent[3 * k + 1 ] = 0.0;
//            _tangent[3 * k + 2 ] = cosTheta * sinPhi;
//
//            //Calcula o vertor bitangente  == dS / dPhi
//            _bitangent[3 * k + 0 ] = cosTheta * cosPhi;
//            _bitangent[3 * k + 1 ] = -sinPhi;
//            _bitangent[3 * k + 2 ] = sinTheta * cosPhi;

            //Calcula o vertor tangente == dS/DTheta
            _tangent[ 3 * k + 0 ] = 0.0;
            _tangent[ 3 * k + 1 ] = 0.0;
            _tangent[ 3 * k + 2 ] = 0.0;

            //Calcula o vertor bitangente  == dS / dPhi
            _bitangent[ 3 * k + 0 ] = 0.0;
            _bitangent[ 3 * k + 1 ] = 0.0;
            _bitangent[ 3 * k + 2 ] = 0.0;
        }
    }

    //Preenche o vetor com a triangulação
    unsigned int k = 0;
    for( unsigned int i = 0; i < n; i++ )
    {
        for( unsigned int j = 0; j < m; j++ )
        {
            _triangles[ k++ ] = getVectorIndex( i, j, n );
            _triangles[ k++ ] = getVectorIndex( i + 1, j + 1, n );
            _triangles[ k++ ] = getVectorIndex( i + 1, j, n );
            _triangles[ k++ ] = getVectorIndex( i, j, n );
            _triangles[ k++ ] = getVectorIndex( i, j + 1, n );
            _triangles[ k++ ] = getVectorIndex( i + 1, j + 1, n );
        }
    }
}


void Surface::generateTangentsAndBitangents()
{
    _tangent.resize( _vertex.size() );
    _bitangent.resize( _vertex.size() );


    for( unsigned int i = 0; i < _triangles.size() / 3; i++ )
    {
        unsigned int id1 = _triangles[ 3 * i + 0 ];
        unsigned int id2 = _triangles[ 3 * i + 1 ];
        unsigned int id3 = _triangles[ 3 * i + 2 ];


        Vec3 v0(
            _vertex[ 3 * id1 ],
            _vertex[ 3 * id1 + 1 ],
            _vertex[ 3 * id1 + 2 ] );

        Vec3 v1(
            _vertex[ 3 * id2 ],
            _vertex[ 3 * id2 + 1 ],
            _vertex[ 3 * id2 + 2 ]
            );

        Vec3 v2(
            _vertex[ 3 * id3 ],
            _vertex[ 3 * id3 + 1 ],
            _vertex[ 3 * id3 + 2 ]
            );


        Vec3 uv0( _texCoord[ 2 * id1 ], _texCoord[ 2 * id1 + 1 ], 0 );
        Vec3 uv1( _texCoord[ 2 * id2 ], _texCoord[ 2 * id2 + 1 ], 0 );
        Vec3 uv2( _texCoord[ 2 * id3 ], _texCoord[ 2 * id3 + 1 ], 0 );

        Vec3 deltaPos1 = v1 - v0;

        Vec3 deltaPos2 = v2 - v0;

        Vec3 deltaUV1 = uv1 - uv0;

        Vec3 deltaUV2 = uv2 - uv0;

        double r = 1.0 / ( deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x );



        Vec3 tangent = ( deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y ) * r;

        Vec3 bitangent = ( deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x ) * r;

        _tangent[ 3 * id1 + 0 ] += tangent.x;
        _tangent[ 3 * id1 + 1 ] += tangent.y;
        _tangent[ 3 * id1 + 2 ] += tangent.z;

        _tangent[ 3 * id2 + 0 ] += tangent.x;
        _tangent[ 3 * id2 + 1 ] += tangent.y;
        _tangent[ 3 * id2 + 2 ] += tangent.z;

        _tangent[ 3 * id3 + 0 ] += tangent.x;
        _tangent[ 3 * id3 + 1 ] += tangent.y;
        _tangent[ 3 * id3 + 2 ] += tangent.z;


        _bitangent[ 3 * id1 + 0 ] += bitangent.x;
        _bitangent[ 3 * id1 + 1 ] += bitangent.y;
        _bitangent[ 3 * id1 + 2 ] += bitangent.z;

        _bitangent[ 3 * id2 + 0 ] += bitangent.x;
        _bitangent[ 3 * id2 + 1 ] += bitangent.y;
        _bitangent[ 3 * id2 + 2 ] += bitangent.z;

        _bitangent[ 3 * id3 + 0 ] += bitangent.x;
        _bitangent[ 3 * id3 + 1 ] += bitangent.y;
        _bitangent[ 3 * id3 + 2 ] += bitangent.z;
    }
}


void Surface::generateNormals()
{
    _normal.resize( _vertex.size(), 0.0 );


    for( unsigned int i = 0; i < _triangles.size() / 3; i++ )
    {
        unsigned int id1 = _triangles[ 3 * i + 0 ];
        unsigned int id2 = _triangles[ 3 * i + 1 ];
        unsigned int id3 = _triangles[ 3 * i + 2 ];


        Vec3 v1(
            _vertex[ 3 * id1 + 0 ],
            _vertex[ 3 * id1 + 1 ],
            _vertex[ 3 * id1 + 2 ] );

        Vec3 v2(
            _vertex[ 3 * id2 + 0 ],
            _vertex[ 3 * id2 + 1 ],
            _vertex[ 3 * id2 + 2 ]
            );

        Vec3 v3(
            _vertex[ 3 * id3 + 0 ],
            _vertex[ 3 * id3 + 1 ],
            _vertex[ 3 * id3 + 2 ]
            );


        Vec3 e1 = v2 - v1;
        Vec3 e2 = v3 - v1;

        Vec3 normal = e1 % e2;
        normal.normalize();

        _normal[ 3 * id1 + 0 ] += normal.x;
        _normal[ 3 * id1 + 1 ] += normal.y;
        _normal[ 3 * id1 + 2 ] += normal.z;

        _normal[ 3 * id2 + 0 ] += normal.x;
        _normal[ 3 * id2 + 1 ] += normal.y;
        _normal[ 3 * id2 + 2 ] += normal.z;

        _normal[ 3 * id3 + 0 ] += normal.x;
        _normal[ 3 * id3 + 1 ] += normal.y;
        _normal[ 3 * id3 + 2 ] += normal.z;
    }
//    
//        for (unsigned int i = 0; i < _vertex.size(); i++)
//        {
//            _normal[i]  = _vertex[i];
//        }
}


void Surface::gererateTexCoords()
{
    _texCoord.resize( 2 * _normal.size() );


    for( unsigned int i = 0; i < _triangles.size() / 3; i++ )
    {
        unsigned int id1 = _triangles[ 3 * i + 0 ];
        unsigned int id2 = _triangles[ 3 * i + 1 ];
        unsigned int id3 = _triangles[ 3 * i + 2 ];


        Vec3 v1(
            _vertex[ 3 * id1 + 0 ],
            _vertex[ 3 * id1 + 1 ],
            _vertex[ 3 * id1 + 2 ] );

        Vec3 v2(
            _vertex[ 3 * id2 + 0 ],
            _vertex[ 3 * id2 + 1 ],
            _vertex[ 3 * id2 + 2 ]
            );

        Vec3 v3(
            _vertex[ 3 * id3 + 0 ],
            _vertex[ 3 * id3 + 1 ],
            _vertex[ 3 * id3 + 2 ]
            );


        float tx1 = 0.5 + ( atan2( v1.z, v1.x ) ) / ( 2 * M_PI );
        float ty1 = 0.5 - asin( -v1.y ) / M_PI;

        float tx2 = 0.5 + ( atan2( v2.z, v2.x ) ) / ( 2 * M_PI );
        float ty2 = 0.5 - asin( -v2.y ) / M_PI;

//            if(tx2 < 0.75 && tx1 > 0.75)
//            {
//                tx2 += 1.0;
//            }
//            else if(tx2 > 0.75 && tx1 < 0.75)
//            {
//                tx2 -= 1.0;
//            }


        float tx3 = 0.5 + ( atan2( v3.z, v3.x ) ) / ( 2 * M_PI );
        float ty3 = 0.5 - asin( -v3.y ) / M_PI;

//            if(tx3 < 0.75 && tx2 > 0.75)
//            {
//                tx3 += 1.0;
//            }
//            else if(tx3 > 0.75 && tx2 < 0.75)
//            {
//                tx3 -= 1.0;
//            }


        _texCoord[ 2 * id1 + 0 ] = tx1;
        _texCoord[ 2 * id1 + 1 ] = ty1;

        _texCoord[ 2 * id2 + 0 ] = tx2;
        _texCoord[ 2 * id2 + 1 ] = ty2;

        _texCoord[ 2 * id3 + 0 ] = tx3;
        _texCoord[ 2 * id3 + 1 ] = ty3;
    }
    
    
//        for( unsigned int i = 0; i < _normal.size()/3; i++)
//        {
//             Vec3 v(
//            _normal[ 3 * i ],
//            _normal[ 3 * i + 1 ],
//            _normal[ 3 * i + 2 ]
//            );
//
//             _texCoord[2 * i + 0] =  0.5 + (atan2(v.z, v.x))/(2*M_PI);
//             _texCoord[2 * i + 1] = 0.5 - asin(-v.y)/ M_PI;
//
//        }
}