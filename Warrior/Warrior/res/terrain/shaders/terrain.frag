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
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_diffuse4;
uniform sampler2D texture_diffuse5;
uniform sampler2D texture_specular1;

uniform vec3 u_ViewPosition;
uniform Light u_Light;
uniform vec3 u_SkyColor;

void main()
{    
    vec4 blendMapColor = texture(texture_diffuse5, TexCoords);
    float backTextureAmount = 1 - (blendMapColor.r + blendMapColor.g + blendMapColor.b);

    vec2 tiledCoords = TexCoords * 40.0;

    vec4 texture_diffuse1Color = texture(texture_diffuse1, tiledCoords) * backTextureAmount;
    vec4 texture_diffuse2Color = texture(texture_diffuse2, tiledCoords) * blendMapColor.r;
    vec4 texture_diffuse3Color = texture(texture_diffuse3, tiledCoords) * blendMapColor.g;
    vec4 texture_diffuse4Color = texture(texture_diffuse4, tiledCoords) * blendMapColor.b;

    vec4 totalColor = texture_diffuse1Color + texture_diffuse2Color + texture_diffuse3Color + texture_diffuse4Color;

	// ambient lighting
	vec3 ambient = u_Light.ambientIntensity * u_Light.color;

	// diffuse lighting
	vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(u_Light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = u_Light.diffuseIntensity * diff * u_Light.color;  

	// specular lighting
	//vec3 viewDir = normalize(u_ViewPosition - FragPos);
    //vec3 reflectDir = reflect(-lightDir, norm);  
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64.0);
    //vec3 specular = u_Light.specularIntensity * spec * texture(texture_specular1, TexCoords).rgb;  

	vec3 finalColor = ambient + diffuse;// + specular;
    FragColor = vec4(finalColor, 1.0) * totalColor;
	FragColor = mix(vec4(u_SkyColor, 1.0), FragColor, Visibility);
}