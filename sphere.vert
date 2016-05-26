#version 440

uniform mat4 mvp;
uniform mat4 m;
uniform mat3 normalMatrix;

in vec3 vertex_MS;
in vec3 normal_MS;

out vec3 vertex_WS;
out vec3 normal_WS;

void main( void )
{
    mat4 nM = transpose( inverse( m ));
    normal_WS = ( nM * vec4( normalize( normal_MS ), 1) ).xyz ;

    vertex_WS = (m * vec4( vertex_MS, 1 )).xyz ;
    
    gl_Position = mvp * vec4( vertex_MS, 1.0f );
}