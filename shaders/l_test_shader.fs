#version 330 core
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 
struct Light {
    // vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;
uniform Material material;
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
in vec2 TextureCoord; 
// uniform vec3 lightPos;
uniform vec3 viewPos;
// uniform vec3 lightColor;
// uniform vec3 objectColor;

float specularStrenght = 0.5;
// uniform sampler2D ourTexture;

void main()
{
    // ambient
    // float ambientStrength = 0.1;
    // vec3 ambient = ambientStrength * lightColor;
    // vec3 ambient = light.ambient * material.ambient;
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TextureCoord));
    
    // diffuse 
    vec3 norm = normalize(Normal);
    // vec3 lightDir = normalize(light.position - FragPos);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TextureCoord));
    
    //specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // vec3 specular = specularStrenght * spec * lightColor; 
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TextureCoord));

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
    // FragColor = texture(ourTexture, TextureCoord);
} 