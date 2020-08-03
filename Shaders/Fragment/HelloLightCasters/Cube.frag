///
#version 330 core
out vec4 color;

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;


struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct DirectionLight
{
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform vec3 viewPos;
uniform Material material;
uniform DirectionLight light;

void main()
{
	//texColor
	vec3 texDiffuseColor = vec3(texture(material.diffuse, TexCoords));
	vec3 texSpecColor = vec3(texture(material.specular, TexCoords));

    // Diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-light.direction);
    float diff_dot = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff_dot * texDiffuseColor;
	
	    // Ambient
    vec3 ambient = light.ambient * texDiffuseColor;
	
    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texSpecColor;
        
    vec3 result = ambient + diffuse + specular;
    color = vec4(result, 1.0f);
} 