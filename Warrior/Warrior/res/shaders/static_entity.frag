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
in vec3 FragPos;  
in vec3 Normal;  
in float Visibility;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

uniform vec3 u_ViewPosition;
uniform Light u_Light;
uniform vec3 u_SkyColor;

void main()
{    
    vec4 textureColor = texture(texture_diffuse1, TexCoords);

	if (textureColor.a < 0.3)
	{
		discard;
	}

	// ambient lighting
	vec3 ambient = u_Light.ambientIntensity * u_Light.color;

	// diffuse lighting
	vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(u_Light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = u_Light.diffuseIntensity * diff * u_Light.color;  

	// specular lighting
	vec3 viewDir = normalize(u_ViewPosition - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64.0);
    vec3 specular = u_Light.specularIntensity * spec * texture(texture_specular1, TexCoords).rgb;  

	vec3 finalColor = ambient + diffuse + specular;
    FragColor = vec4(finalColor, 1.0) * textureColor;
	FragColor = mix(vec4(u_SkyColor, 1.0), FragColor, Visibility);
}