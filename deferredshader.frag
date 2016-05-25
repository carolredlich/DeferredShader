#version 410 core

in vec2 UV;

out vec3 color;

uniform sampler2D PositionTex;

void main()
{
	color = texture( PositionTex, UV ).xyz;// + vec3( 0, 0, 0.5);
}
