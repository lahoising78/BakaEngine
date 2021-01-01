#version 330 core

struct Light
{
    vec3 color;
    float intensity;
};

struct AmbientLight
{
    Light light;
};
uniform AmbientLight u_ambientLight;

struct DirLight
{
    Light light;
    vec3 dir;
};
uniform DirLight u_dirLight;

struct PointLight
{
    Light light;
    vec3 position;
};
uniform PointLight u_pointLight;

uniform mat4 u_modelViewProj;
uniform mat4 u_normalMat;

#uniforms
uniform vec4 u_tint;
#enduniforms

in vec3 v_normal;
in vec3 v_pos;

vec3 ambient_light_calc(AmbientLight light)
{
    return light.light.color * light.light.intensity;
}

vec3 dir_light_calc(DirLight light, vec3 normal)
{
    return light.light.color * max(dot(normal, light.dir), 0.0) * light.light.intensity;
}

vec3 point_light_calc(PointLight light, vec3 normal, vec3 pos)
{
    vec3 posToLight = light.position - pos;
    vec3 lightDir = normalize(posToLight);
    float r = length(posToLight);
    vec3 color = light.light.intensity * light.light.color / (r * r);
    
    float dot_nl = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = dot_nl * color;
    return diffuse;
}

void main()
{
    vec3 result = ambient_light_calc(u_ambientLight);
    result += dir_light_calc(u_dirLight, v_normal);
    result += point_light_calc(u_pointLight, v_normal, v_pos);
    gl_FragColor = vec4(result, 1.0) * u_tint;
}