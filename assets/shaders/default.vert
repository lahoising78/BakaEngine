#version 330 core

uniform mat4 u_modelViewProj;
uniform vec4 u_tint;
uniform mat4 u_normalMat;

in vec3 a_position;
in vec3 a_normal;

out vec3 v_normal;
out vec3 v_pos;

void main()
{   
    vec4 pos = vec4(a_position, 1.0);
    gl_Position = u_modelViewProj * pos;
    v_pos = (u_normalMat * pos).xyz;

    v_normal = normalize((u_normalMat * vec4(a_normal, 0.0)).xyz);
}