#version 330 core

layout(location = 0) out vec4 color; 

// in vec3 v_Position;
in vec4 v_Color;

void main()
{
    // color = vec4(v_Position * 0.5 + 0.5, 1.0f);
    color = v_Color;
    // color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}