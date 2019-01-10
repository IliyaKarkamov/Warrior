#version 330 core
out vec4 FragColor;

struct Light 
{
    vec3 position;
	vec3 color;

    vec3 ambientIntensity;
    vec3 diffuseIntensity;
    vec3 specularIntensity;
};

in vec2 TexCoords;
uniform Light u_Light;

void main()
{    
	FragColor = vec4(u_Light.color, 1.0);
}