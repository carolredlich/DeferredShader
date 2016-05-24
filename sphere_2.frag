#version 440
subroutine void RenderPassType();
subroutine uniform RenderPassType RenderPass;

uniform vec4 lightDifuse;
// The g-buffer textures
uniform sampler2D PositionTex, NormalTex, ColorTex;

in vec3 vertex_CS;
in vec3 normal_CS;
in vec3 lightPos_CS;
in vec2 texCoordFrag_MS;


out vec4 FragColor;
out vec3 PositionData;
out vec3 NormalData;
out vec3 ColorData;

vec3 diffuseModel( vec3 pos, vec3 normal, vec3 diffColor )
{
    vec3 L = normalize( lightPos_CS - pos );
    float diff = max( 0.0f, dot( normal, L ) );
    vec3 diffuse = diff * lightDifuse.rgb * diffColor;
    return diffuse;
}

subroutine (RenderPassType)
void pass1()
{    // Store position, normal, and diffuse color in g-buffer
    PositionData = vertex_CS;
    NormalData = normal_CS;
    ColorData = vec3( 1, 1, 1);
}
subroutine(RenderPassType)
void pass2()
{
    // Retrieve position, normal and color information from 
    // the g-buffer textures
  vec3 pos = vec3( texture( PositionTex, texCoordFrag_MS ) );
  vec3 norm = vec3( texture( NormalTex, texCoordFrag_MS ) );
  vec3 diffColor = vec3( 0, 0, 1);
  FragColor = vec4( diffuseModel(pos,norm,diffColor), 1.0 );
}
void main() 
{
    // This will call either pass1 or pass2
  RenderPass();
}