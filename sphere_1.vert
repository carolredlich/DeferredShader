#version 440

uniform mat4 mvp;
uniform mat4 mv;
uniform mat4 v;
uniform mat3 normalMatrix;
uniform vec3 lightPos_WS;

in vec3 vertex_MS;
in vec3 normal_MS;
in vec3 bitangent_MS;


smooth out vec3 eyeDir_CS;
smooth out vec3 vertex_CS;
smooth out vec3 lightDir_CS;
smooth out vec3 normal_CS;


void main( void )
{
    normal_CS = normalMatrix * normalize( normal_MS );

    vertex_CS = ( mv * vec4( vertex_MS, 1 ) ).xyz;

    vec3 lightPos_CS = ( v * vec4( lightPos_WS, 1 ) ).xyz;
    lightDir_CS = lightPos_CS - vertex_CS;

    eyeDir_CS = -vertex_CS;

    //Projeta as coordendas do vertice.
    gl_Position = mvp * vec4( vertex_MS, 1.0f );
}


