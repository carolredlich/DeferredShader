#version 440

uniform vec4 lightAmbient;
uniform vec4 lightDifuse;
uniform vec4 lightSpecular;



in vec3 normal_CS;
in vec3 vertex_CS;
in vec3 eyeDir_CS;
in vec3 lightDir_CS;

//out vec4 color;
layout(location = 0) out vec4 color;

void main( void )
{
    //Transforma rgb para normal
    vec3 normal = normalize( normal_CS ); //Descomentar e comentar acima para não ter bumpmap

    //Normaliza as direcoes das luzes
    vec3 L =  normalize( lightDir_CS );//Descomentar e comentar acima para não ter bumpmap

    //Inicializa a cor do fragmento com a cor ambiente.
    color = vec4(1, 0, 0, 1);

    //Faz o calculo da cor difusa
    float diff = max( 0.0f, dot( normal, L ) );
    color.rgb += diff * lightDifuse.rgb;


    //Calcula a especular da luz.
    if( diff != 0 )
    {
        vec3 r = normalize( reflect( -L, normal ) );
        float spec = max( 0.0, dot( normalize( eyeDir_CS ), r ) );
        float fSpec = pow( spec  , 30 ); //Futebol

        color.rgb += lightSpecular.rgb * fSpec;
       
    }
}



