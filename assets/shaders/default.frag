#version 330 core

struct Light
{
    vec3 color;
    float intensity;
};

struct DirLight
{
    Light light;
    vec3 dir;
};
uniform DirLight u_dirLight;

struct AmbientLight
{
    Light light;
};
uniform AmbientLight u_ambientLight;

uniform mat4 u_modelViewProj;
uniform vec4 u_tint;
uniform mat4 u_normalMat;

in vec3 v_normal;

vec3 ambient_light_calc(AmbientLight light)
{
    return light.light.color * light.light.intensity;
}

vec3 dir_light_calc(DirLight light, vec3 normal)
{
    return light.light.color * max(dot(normal, light.dir), 0.0) * light.light.intensity;
}

void main()
{
    vec3 result = ambient_light_calc(u_ambientLight);
    result += dir_light_calc(u_dirLight, v_normal);
    gl_FragColor = vec4(result, 1.0) * u_tint;
}