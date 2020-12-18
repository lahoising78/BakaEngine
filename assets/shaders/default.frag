#version 330 core

uniform mat4 u_modelViewProj;
uniform vec4 u_tint;
uniform mat4 u_normalMat;

in vec3 v_normal;

void main()
{
    vec3 light_dir = normalize(vec3(0.0, 1.0, 0.0));
    
    gl_FragColor = u_tint * max(dot(v_normal, light_dir), 0.0);
}