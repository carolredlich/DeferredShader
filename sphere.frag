#version 440
uniform vec3 materialAmbient;
uniform vec3 materialDifuse;
uniform vec3 materialSpecular;

in vec3 vertex_WS;
in vec3 normal_WS;

out vec4 position;
out vec4 normal;
out vec3 difuse;
out vec3 ambient;
out vec3 specular;


void main( void )
{
    position = vec4( vertex_WS, 1) ;
    normal = vec4( normal_WS, 1);
    difuse = materialDifuse;
    ambient = materialAmbient;
    specular = materialSpecular;
    
}
