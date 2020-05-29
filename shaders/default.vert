#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 u_modelMat;

void main()
{   
    gl_Position = u_modelMat * position;
    // gl_Position = position;
}