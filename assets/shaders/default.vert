#version 330 core

uniform mat4 u_proj;
uniform vec4 u_tint;
layout(location = 0) in vec3 a_Position;

void main()
{   
    gl_Position = u_proj * vec4(a_Position, 1.0f);
}