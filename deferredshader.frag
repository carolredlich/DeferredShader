#version 440 


const int NUM_LIGHTS = 60;
uniform int nLight;
uniform vec3 lightAmbient[NUM_LIGHTS];
uniform vec3 lightDifuse[NUM_LIGHTS];
uniform vec3 lightSpecular[NUM_LIGHTS];
uniform vec3 lightPos_WS[NUM_LIGHTS];;
uniform vec3 eyePos_WS;


in vec2 UV;

out vec3 color;


uniform sampler2D PositionTex;
uniform sampler2D NormalTex;
uniform sampler2D DifTex;
uniform sampler2D AmbTex;
uniform sampler2D SpecTex;

void main()
{
    vec3 normal = texture( NormalTex, UV ).xyz;
    normal = normalize( normal );

    vec3 position = texture( PositionTex, UV ).xyz;
        
    vec3 mDif = texture( DifTex, UV ).xyz;
    vec3 mAmb = texture( AmbTex, UV ).xyz;
    vec3 mSpec = texture( SpecTex, UV ).xyz;
    float shi = texture( SpecTex, UV ).w;
    color = mAmb * lightAmbient[0];
    
    for( int i = 0; i < nLight; i++ )
    {
        vec3 lightDir = lightPos_WS[i] - position;
        vec3 L = normalize( lightDir );
        
        float distance = length( lightDir );

        float diff = max( 0.0f, dot( normal, L ) );
        color += (diff * lightDifuse[i] * mDif) / ( (distance + nLight )*0.3);

        vec3 eyeDir = eyePos_WS - position;

        if( diff != 0 )
        {
            vec3 r = normalize( reflect( -L, normal ) );
            float spec = max( 0.0, dot( normalize( lightDir ), r ) );
            float fSpec = pow( spec  , 30 ); 

            color += (lightSpecular[i] * fSpec * mSpec);
        }
        
    }

}
