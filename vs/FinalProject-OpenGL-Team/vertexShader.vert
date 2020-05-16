#version 330
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 texCoord;


uniform mat4 model = mat4(1.0f);
uniform mat4 view;
uniform mat4 projection;
uniform mat3 inverse;
uniform vec3 lightPos;

out vec3 Normal;
out vec3 FragPos;
out vec3 LightPos;
out vec2 TexCoord;

void main()
{
	gl_Position =  projection * view * model * vec4(position, 1.0f);

	FragPos = vec3(view * model * vec4(position, 1.0f));
	Normal = inverse * aNormal; 
	LightPos = vec3(view * vec4(lightPos, 1.0));

	// We swap the y-axis by substracing our coordinates from 1. This is done because most images have the top y-axis inversed with OpenGL's top y-axis.
	TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
}