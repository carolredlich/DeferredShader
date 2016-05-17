/*
 * File:   Surface.h
 * Author: caroline
 *
 * Created on 25 de Abril de 2016, 12:18
 */

#ifndef SURFACE_H
#define SURFACE_H
#include <vector>
#include "GraphicsShader.h"
#include "SphereShader.h"

class Surface
{
public:

    /**
     * Constroi uma esfera
     * @param shader
     */
    Surface( SphereShader* shader );

    Surface( std::string fileName, SphereShader* shader );

    virtual ~Surface();


    // Array para guardar os vértices da malha
    std::vector< double > _vertex;

    // Array para guardar a normal dos vertices da malha
    std::vector< double > _normal;

    // Array para guardar os vértices da malha
    std::vector< double > _texCoord;

    // Array para guardar os vértices da malha
    std::vector< double > _tangent;

    // Array para guardar os vértices da malha
    std::vector< double > _bitangent;

    //Array para guardar os triangulos da malha
    std::vector< unsigned int > _triangles;

    //Shader
    SphereShader* _shader;



private:

    void  generateSphereMesh();

    void loadMesh( std::string fileName );
    void generateTangentsAndBitangents();
    void generateNormals();
    void gererateTexCoords();

    int getVectorIndex( int i, int j, int n )
    {
        return j + i * ( n + 1 );
    }
};

#endif  /* SURFACE_H */

