#version 330 core

uniform mat4 u_proj;
uniform vec4 u_tint;
uniform mat4 u_normalMat;

attribute vec3 a_position;
attribute vec3 a_normal;

varying vec3 v_normal;

void main()
{   
    gl_Position = u_proj * vec4(a_position, 1.0);
    v_normal = a_normal;
}