#version 300 es

struct DirectionalLight
{
    vec3 color;
    float ambientIntensity;
    float diffuseIntensity;
    vec3 direction;
};

uniform sampler2D colorMap;    // Color map
uniform sampler2D normalVSMap;   // Normal map
uniform sampler2D depthMap; // Position mapp

uniform DirectionalLight directionalLight; // Directional light

uniform float specularIntensity;     
uniform float specularPower;

uniform vec2 screenSize;

out vec4 colorOut;

uniform mat4 V;

// For psotion reconstruction from depth
uniform float projectionA; // zFar / ( zFar - zNear)
uniform float projectionB; // (-zFar * zNear) / (zFar - zNear)
in vec3 viewRay;

float shadow(float x)
{
    const float ks = 1.01f;

    float num = ( 1.0f / pow((1.0f-ks),2.0f) ) - ( 1.0f / pow( ( x- ks ), 2.0f) );

    float den = ( 1.0f / pow( (1.0f-ks), 2.0f) ) - ( 1.0f / pow( ks, 2.0f) );

    return num/den;
}

float fresnel(float x)
{
    const float kf = 1.12f;

    float num = ( ( 1.0f / pow( (x - kf), 2.0f) ) ) - ( 1.0f / pow(kf,2.0f) );

    float den = ( ( 1.0f / pow( (1.0f - kf), 2.0f) ) ) - ( 1.0f / pow(kf,2.0f) );

    return num/den;
}

vec4 calcLight( vec3 diffuseColor,
                DirectionalLight light,
				vec3 positionVS,
				vec3 normalVS,
                float fSmoothness,
                float fMetalness)
{
    // Strauss BRDF

    const float fTransparency = 0.0f;

    vec3 l = normalize(-light.direction);
    vec3 v = normalize(-positionVS);
    vec3 h = reflect(l, normalVS);

    // Aliases
    float nDotL = dot(normalVS, l);
    float nDotV = dot(normalVS, v);
    float hDotV = dot(h, v);
    float fNDotL = fresnel (nDotL);
    float s_cubed = fSmoothness * fSmoothness * fSmoothness;

    // Evaluate diffuse term
    float d = (1.0f - fMetalness * fSmoothness);
    float Rd = (1.0f - s_cubed) * (1.0f - fTransparency);
    vec3 diffuse = nDotL  * d * Rd * diffuseColor;

    // Compute the inputs for the specular term
    float r = (1.0f - fTransparency) - Rd;

    float j = fNDotL * shadow (nDotL) * shadow( nDotV);

    const float k = 0.1f;
    float reflect = min(1.0f, r+j * ( r+k ) );

    vec3 C1 = vec3(1.0f, 1.0f, 1.0f);
    vec3 Cs = C1 + fMetalness * (1.0f - fNDotL) * (diffuseColor - C1);

    // Evaluate the specular term

    vec3 specular = Cs * reflect;
    specular = specular * pow(-hDotV, 3.0f / (1.0f - fSmoothness) );

    diffuse  = max( vec3(0.0f, 0.0f, 0.0f), diffuse);
    specular = max( vec3(0.0f, 0.0f, 0.0f), specular);

    // ToDo: Render seperate ambient light
    vec3 ambient = diffuseColor * light.ambientIntensity;

    return vec4( diffuse + specular + ambient, 1.0f);
    //return vec4( specular, 1.0f);

}

vec2 getTexCoord()
{
    return gl_FragCoord.xy / screenSize;
}

vec3 decodeNormal(vec2 normal){
    
    //vec2 normalEnc = normal * 2.0f - 1.0f;
    
    //vec3 normalOut;

    //normalOut.z = length(normalEnc) * 2.0f - 1.0f;

    //normalOut.xy = normalize(normalEnc) * sqrt(1.0f - normalOut.z * normalOut.z);

    //normalOut = normalize(normalOut);

    //return normalOut;

    vec2 fenc = normal*4.0f-2.0f;
    float f = dot(fenc,fenc);
    float g = sqrt(1.0f-f/4.0f);
    vec3 n;
    n.xy = fenc*g;
    n.z = 1.0f-f/2.0f;
    n = normalize(n);
    return n;

}

void main()
{
    vec2 texCoord = getTexCoord();
	vec3 diffuseColor = texture(colorMap, texCoord).xyz;
    vec3 normalVS = decodeNormal( texture(normalVSMap, texCoord).xy );

	float depth = texture(depthMap, texCoord).r;
    // Scale from [0,1.0] to [-1.0, 1.0f]
    depth = 2.0f * depth - 1.0f;
    // Transform to view space depth
    float linearDepth = -projectionB / ( depth + projectionA);
    // scale the view ray with the depth value
    vec3 positionVS = viewRay * linearDepth;

    float metalness = 0.6f;
    float smoothness = 0.5f;

    DirectionalLight light;

    light.color = directionalLight.color;
    light.ambientIntensity = directionalLight.ambientIntensity;
    light.diffuseIntensity = directionalLight.diffuseIntensity;
    light.direction = (V * vec4(directionalLight.direction, 0.0f) ).xyz;

	colorOut = calcLight(diffuseColor, light, positionVS, normalVS, metalness, smoothness);

    //normalVS = normalVS * 0.5f + 0.5f;
    //colorOut = vec4(normalVS, 0.0f);
}
