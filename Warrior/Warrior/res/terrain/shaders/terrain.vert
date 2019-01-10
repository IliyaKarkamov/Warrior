#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 FragPos;
out vec3 Normal;
out float Visibility;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

const float density = 0.0016;
const float gradient = 1.5;

void main()
{
	vec4 worldPosition = u_Model * vec4(aPos, 1.0);
	vec4 positionRelativeToCam = u_View * worldPosition;

    TexCoords = aTexCoords;    
	Normal = mat3(transpose(inverse(u_Model))) * aNormal;
	FragPos = vec3(u_Model * vec4(aPos, 1.0));

	float dist = length(positionRelativeToCam.xyz);
	Visibility = exp(-pow((dist * density), gradient));
	Visibility = clamp(Visibility, 0.0, 1.0);

    gl_Position = u_Projection * positionRelativeToCam;
}