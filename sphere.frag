#version 440

uniform vec4 lightAmbient;
uniform vec4 lightDifuse;
uniform vec4 lightSpecular;


in vec3 vertex_CS;

uniform sampler2D colorTextureSampler;
uniform sampler2D normalTextureSampler;

in vec2 texCoordFrag_MS;
in vec3 lightDir_TS;
in vec3 eyeDir_TS;

in vec3 lightDir_CS;

layout( location = 1) out vec4 color;

void main( void )
{
    //Transforma rgb para normal
    //vec3 normal = normalize( 2 * ( texture( normalTextureSampler, texCoordFrag_MS ).rgb - vec3( 0.5, 0.5, 0.5 ) ) );
    vec3 normal = normalize( vertex_CS ); //Descomentar e comentar acima para não ter bumpmap

    //vec4 texColor = texture( colorTextureSampler, texCoordFrag_MS );

    //Normaliza as direcoes das luzes
    //vec3 L = normalize( lightDir_TS );
    vec3 L =  normalize( lightDir_CS );//Descomentar e comentar acima para não ter bumpmap

    //Inicializa a cor do fragmento com a cor ambiente.
    color = lightAmbient;

    //Faz o calculo da cor difusa
    float diff = max( 0.0f, dot( normal, L ) );
    color.rgb += diff * lightDifuse.rgb;

    //Interpola cor com a textura
    //color.rgb = mix( color, texColor, 0.5 ).rgb;

    //Calcula a especular da luz.
    if( diff != 0 )
    {
        vec3 r = normalize( reflect( -L, normal ) );
        float spec = max( 0.0, dot( normalize( eyeDir_TS ), r ) );
        //float fSpec = pow(spec*0.8, 8); //Basquete
        float fSpec = pow( spec * 0.6, 3 ); //Futebol

        color.rgb += lightSpecular.rgb * fSpec;
       
    }
}

