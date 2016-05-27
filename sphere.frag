#version 440
uniform vec3 materialAmbient;
uniform vec3 materialDifuse;
uniform vec3 materialSpecular;
uniform float materialShiness;

uniform sampler2D colorTextureSampler;
uniform sampler2D normalTextureSampler;

in vec3 vertex_WS;
in vec3 normal_WS;

in vec2 texCoordFrag_MS;



out vec3 position;
out vec3 normal;
out vec3 difuse;
out vec3 ambient;
out vec4 specular;


void main( void )
{
    position = vertex_WS;
    normal = normal_WS; 
    //difuse = materialDifuse;
    difuse =  texture( colorTextureSampler, texCoordFrag_MS ).rgb;
    ambient = materialAmbient;
    specular = vec4( materialSpecular, materialShiness);
    
}
