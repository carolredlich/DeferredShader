#version 440
uniform vec3 materialAmbient;
uniform vec3 materialDifuse;
uniform vec3 materialSpecular;

uniform sampler2D colorTextureSampler;
uniform sampler2D normalTextureSampler;

in vec3 vertex_WS;
in vec3 normal_WS;

in vec2 texCoordFrag_MS;



out vec4 position;
out vec4 normal;
out vec3 difuse;
out vec3 ambient;
out vec3 specular;


void main( void )
{
    position = vec4( vertex_WS, 1) ;
    normal = vec4( normal_WS, 1);
    difuse = texture( colorTextureSampler, texCoordFrag_MS ).rgb;
    ambient = materialAmbient;
    specular = materialSpecular;
    
}
