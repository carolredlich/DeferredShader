#version 440
uniform vec4 materialAmbient;
uniform vec4 materialDifuse;
uniform vec4 materialSpecular;

in vec3 vertex_WS;
in vec3 normal_WS;

out vec4 position;
out vec4 normal;
out vec4 difuse;
out vec4 ambient;
out vec4 specular;


void main( void )
{
    position = vec4( vertex_WS, 1) ;
    normal = vec4( normal_WS, 1);
    difuse = materialDifuse;
    ambient = materialAmbient;
    specular = materialSpecular;
    
}
