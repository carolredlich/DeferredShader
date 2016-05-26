#version 440

in vec3 vertex;

out vec2 UV;

void main()
{
	gl_Position =  vec4( vertex, 1 );
	UV = ( vertex.xy + vec2( 1, 1 ) ) / 2.0;
}

