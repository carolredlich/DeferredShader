#version 440


in vec3 vertex_MS;
in vec3 normal_MS;
in vec2 texCoord_MS;


out vec3 vertex_CS;
out vec3 normal_CS;
out vec3 lightPos_CS;
out vec2 texCoordFrag_MS;


uniform mat4 mvp;
uniform mat4 mv;
uniform mat4 v;
uniform mat3 normalMatrix;
uniform vec3 lightPos_WS;




void main( void )
{
    normal_CS = normalize (normalMatrix * normalize( normal_MS ));

    vertex_CS = ( mv * vec4( vertex_MS, 1 ) ).xyz;

    lightPos_CS = ( v * vec4( lightPos_WS, 1 ) ).xyz;

    //Passa as coordenadas de textura
    texCoordFrag_MS = texCoord_MS;

    //Projeta as coordendas do vertice.
    gl_Position = mvp * vec4( vertex_MS, 1.0f );
}


