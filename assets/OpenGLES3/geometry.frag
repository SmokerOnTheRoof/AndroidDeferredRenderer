#version 300 es

in vec3 normalWS;

uniform vec3 color;

// Output data

layout (location = 0) out vec3 diffuseOut; 
layout (location = 1) out vec2 normalWSOut; 

vec2 encodeNormal(vec3 normal)
{
    // Spheremap transform from crytek
    //vec3 normalized = normalize(normal);
    //vec2 normalOut = normalize(normalized.xy) * sqrt(normalized.z*0.5+0.5);
    //normalOut = normalOut * 0.5f + 0.5f;
    //return normalOut;
    vec3 n = normalize(normal);
    float f = sqrt(8.0f*normal.z+8.0f);
    return normal.xy / f + 0.5;

}

void main()
{
    diffuseOut = color;
    normalWSOut = encodeNormal(normalWS);
}