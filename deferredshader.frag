#version 440 

in vec2 UV;

out vec3 color;

uniform sampler2D PositionTex;
uniform sampler2D NormalTex;
uniform sampler2D DifTex;

void main()
{
   color = texture( PositionTex, UV ).xyz;// + vec3( 0, 0, 0.5);
   color = texture( NormalTex, UV ).xyz;// + vec3( 0, 0, 0.5);
   color = texture( DifTex, UV ).xyz;// + vec3( 0, 0, 0.5);
}
