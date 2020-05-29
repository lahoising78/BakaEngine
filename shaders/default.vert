#version 330 core

// layout (location = 2) uniform UBO
// {
//     mat4 model;
// } ubo;

layout(location = 0) in vec4 position;
// uniform mat4 viewProjectionMat;
// layout(location = 1) in vec4 color;

// layout(location = 0) out vec4 v_color;

void main()
{   
    gl_Position = position;
}