#version 420

layout (location = 0) in vec3 positionMS;
layout (location = 1) in vec3 normalMS;

uniform mat4 MVP;
uniform mat4 M;
uniform mat4 V;

out vec3 normalWS; 
out vec3 positionWS;

void main(){
    gl_Position = MVP * vec4(positionMS, 1.0f);;

    // ToDo: This transformation doesn't work always
    normalWS = (V * M * vec4(normalMS, 0.0f)).xyz;
}