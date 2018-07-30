#version 330 core
out vec4 FragColor;

struct Light {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec2 TexCoords;
in vec3 FragPos;

uniform Light light;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;

void main()
{
    vec3 ambient = light.ambient * texture(texture_diffuse1, TexCoords).rgb;

    vec3 normal = normalize(texture(texture_normal1, TexCoords).rgb);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(texture_diffuse1, TexCoords).rgb;

    vec3 viewPos = vec3(0.0, 0.0, 0.6);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 25.0);
    vec3 specular = light.specular * spec * texture(texture_specular1, TexCoords).rgb;

    vec3 result = ambient + diffuse + specular;
    //FragColor = vec4(result, 1.0);
    FragColor = texture(texture_diffuse1, TexCoords);
}
