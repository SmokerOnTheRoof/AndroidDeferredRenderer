#version 300 es                                                                                                                             

layout (location = 0) in vec3 position;

uniform mat4 invP;

out vec3 viewRay;

void main()
{          
    // transform to view space
    // for directional light we render in screen space
    vec3 positionVS = (vec4(position, 1.0f) * invP).xyz;

    // clamp to Z = 1
    viewRay = vec3( positionVS.xy / positionVS.z , 1.0f );

    gl_Position = vec4(position, 1.0);
}

