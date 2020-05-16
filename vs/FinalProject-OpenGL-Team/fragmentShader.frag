#version 330 core

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;

out vec4 FragColor;

// Texture samplers
uniform sampler2D ourTexture;
uniform vec3 lightColor;
uniform vec3 viewPos;

void main()
{
    //ambient
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    //diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * lightColor;

    //specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(norm, lightDir);
    float spec = pow(max(dot(reflectDir ,viewDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = ambient + diffuse + specular;
    FragColor = texture(ourTexture, TexCoord) * vec4(result, 1.0f);
}