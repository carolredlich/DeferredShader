#version 440 

uniform vec4 lightAmbient;
uniform vec4 lightDifuse;
uniform vec4 lightSpecular;
uniform vec3 lightPos_WS;
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

    vec3 lightDir = lightPos_WS - position;
    vec3 L = normalize( lightDir );

    vec4 mDif = texture( DifTex, UV );
    vec4 mAmb = texture( AmbTex, UV );
    vec4 mSpec = texture( SpecTex, UV );

    color = (mAmb * lightAmbient).rgb;
    
    float diff = max( 0.0f, dot( normal, L ) );
    color += diff * lightDifuse.rgb * mDif.rgb;
    
    vec3 eyeDir = eyePos_WS - position;

    if( diff != 0 )
    {
        vec3 r = normalize( reflect( -L, normal ) );
        float spec = max( 0.0, dot( normalize( lightDir ), r ) );
        float fSpec = pow( spec  , 30 ); 

        color += lightSpecular.rgb * fSpec * mSpec.rgb;
       
    }


}
