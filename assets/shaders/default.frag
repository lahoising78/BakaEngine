#version 330 core

uniform vec4 u_tint;
layout(location = 0) out vec4 color;

void main()
{
    color = u_tint;
}