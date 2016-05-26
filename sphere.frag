#version 440

uniform vec4 lightAmbient;
uniform vec4 lightDifuse;
uniform vec4 lightSpecular;

uniform vec4 materialAmbient;
uniform vec4 materialDifuse;
uniform vec4 materialSpecular;


in vec3 lightDir_CS;
in vec3 vertex_CS;
in vec3 normal_CS;
in vec3 eyeDir_CS;

out vec4 color;
out vec4 n;
out vec4 difuse;

void main( void )
{
    //Transforma rgb para normal
    
    vec3 normal = normalize( normal_CS ); 
    n  = vec4( normal, 1);

    //Normaliza as direcoes das luzes
    vec3 L =  normalize( lightDir_CS );

    //Inicializa a cor do fragmento com a cor ambiente.
    color = lightAmbient * materialAmbient;
 
    //Faz o calculo da cor difusa
    float diff = max( 0.0f, dot( normal, L ) );
  
    difuse = diff * materialDifuse * lightDifuse;
    color.rgb += difuse.rgb;

    //Calcula a especular da luz.
    if( diff != 0 )
    {
        vec3 r = normalize( reflect( -L, normal ) );
        float spec = max( 0.0, dot( normalize( eyeDir_CS ), r ) );
        float fSpec = pow( spec , materialSpecular.a ); //Futebol

        color.rgb += lightSpecular.rgb * materialSpecular.rgb * fSpec;
       
    }
}

/*
#version 440

uniform vec4 materialAmbient;
uniform vec4 materialDifuse;
uniform vec4 materialSpecular;

in vec3 vertex_CS;
in vec3 normal_CS;

out vec4 mAmbient;
out vec4 mDifuse;
out vec4 mSpecular;

out vec3 normal;
out vec3 position;


out vec4 color;

void main( void )
{
    mAmbient = materialAmbient;
    mDifuse = materialDifuse;
    mSpecular = materialSpecular;

    normal = normalize( normal_CS ); 

    position = vertex_CS;


  }


*/