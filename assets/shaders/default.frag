#version 330 core

struct DirLight
{
    vec3 color;
    float intensity;
    vec3 dir;
};
uniform DirLight u_dirLight;

uniform mat4 u_modelViewProj;
uniform vec4 u_tint;
uniform mat4 u_normalMat;

in vec3 v_normal;

vec3 dir_light_calc(DirLight light, vec3 normal)
{
    return light.color * max(dot(normal, light.dir), 0.0) * light.intensity;
}

void main()
{
    gl_FragColor = u_tint * vec4(dir_light_calc(u_dirLight, v_normal), 1.0);
}