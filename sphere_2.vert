#version 440

uniform mat4 mvp;
uniform mat4 mv;
uniform mat4 v;
uniform mat3 normalMatrix;
uniform vec3 lightPos_WS;

in vec3 vertex_MS;
in vec3 normal_MS;
in vec2 texCoord_MS;
in vec3 tangent_MS;
in vec3 bitangent_MS;


smooth out vec3 lightDir_TS;
smooth out vec2 texCoordFrag_MS;
smooth out vec3 eyeDir_TS;

smooth out vec3 vertex_CS;
smooth out vec3 lightDir_CS;

smooth out vec3 normal_CS;


void main( void )
{
    normal_CS = normalMatrix * normalize( normal_MS );
    vec3 tangent_CS = normalMatrix * normalize( tangent_MS );
    vec3 bitangent_CS = normalMatrix * normalize( bitangent_MS );

    mat3 TBN = transpose( mat3( tangent_CS, bitangent_CS, normal_CS ) );

    vec3 light_CS = ( v * vec4( lightPos_WS, 1 ) ).xyz;
    vertex_CS = ( mv * vec4( vertex_MS, 1 ) ).xyz;

    lightDir_CS = light_CS - vertex_CS;
    vec3 eyeDir_CS = -vertex_CS;

    lightDir_TS = TBN * ( light_CS - vertex_CS );
    //light = TBN * ( lightPos_WS - vertex_MS);

    eyeDir_TS = TBN * ( -vertex_CS );

    //Passa as coordenadas de textura
    texCoordFrag_MS = texCoord_MS;

    //Projeta as coordendas do vertice.
    gl_Position = mvp * vec4( vertex_MS, 1.0f );
}


