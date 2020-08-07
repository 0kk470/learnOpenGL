///
#version 330 core
out vec4 color;

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;



struct DirectionLight
{
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	bool isOn;
};

struct PointLight
{

	vec3 Position;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float constant;
    float linear;
    float quadratic;
	
	bool isOn;
};

struct SpotLight
{
	vec3 Position;
	vec3 direction;
    float cutOff;
    float outerCutOff;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float constant;
    float linear;
    float quadratic;
	
	bool isOn;
};

#define NR_POINT_LIGHT 4


uniform vec3 viewPos;
uniform DirectionLight dirLight;
uniform PointLight pointlights[NR_POINT_LIGHT];
uniform SpotLight spotLight;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform float shininess;

vec3 CaclDirectionLight(DirectionLight DirLight)
{
	if(!DirLight.isOn)
		return vec3(0,0,0);
	vec3 texDiffuseColor = vec3(texture(texture_diffuse1, TexCoords));
	vec3 texSpecColor = vec3(texture(texture_specular1, TexCoords));

    // Diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-DirLight.direction);
    float diff_dot = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = DirLight.diffuse * diff_dot * texDiffuseColor;
	
	// Ambient
    vec3 ambient = DirLight.ambient * texDiffuseColor;
	
    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = DirLight.specular * spec * texSpecColor;
        
    vec3 result = ambient + diffuse + specular;
    return result;
}

vec3 CaclPointLight(PointLight pLight)
{
	if(!pLight.isOn)
		return vec3(0,0,0);
	vec3 texDiffuseColor = vec3(texture(texture_diffuse1, TexCoords));
	vec3 texSpecColor = vec3(texture(texture_specular1, TexCoords));

    // Diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(pLight.Position - FragPos);
    float diff_dot = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = pLight.diffuse * diff_dot * texDiffuseColor;
	
	// Ambient
    vec3 ambient = pLight.ambient * texDiffuseColor;
	
    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0),shininess);
    vec3 specular = pLight.specular * spec * texSpecColor;
        
	//attenuation
	float Distance = length(pLight.Position - FragPos);
	float attenuation = 1.0f / (pLight.constant + pLight.linear * Distance + pLight.quadratic * Distance * Distance);
	
    vec3 result = (ambient + diffuse + specular) * attenuation;
    return result;
}

vec3 CaclSpotLight(SpotLight _spotLight)
{
	vec3 lightDir = normalize(_spotLight.Position - FragPos);
	
	float theta = dot(lightDir, normalize(-_spotLight.direction));
	float epsilon = _spotLight.cutOff - _spotLight.outerCutOff;
	float intensity = clamp((theta - _spotLight.outerCutOff) / epsilon, 0.0, 1.0);
	
	vec3 result = vec3(0,0,0);
	
	if(_spotLight.isOn)
	{
		vec3 texDiffuseColor = vec3(texture(texture_diffuse1, TexCoords));
		vec3 texSpecColor = vec3(texture(texture_specular1, TexCoords));

		// Diffuse 
		vec3 norm = normalize(Normal);
		float diff_dot = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = _spotLight.diffuse * diff_dot * texDiffuseColor;
	
		// Ambient
		vec3 ambient = _spotLight.ambient * texDiffuseColor;
	
		// Specular
		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);  
		float spec = pow(max(dot(viewDir, reflectDir), 0.0),shininess);
		vec3 specular = _spotLight.specular * spec * texSpecColor;
			
		//attenuation
		float Distance = length(_spotLight.Position - FragPos);
		float attenuation = 1.0f / (_spotLight.constant + _spotLight.linear * Distance + _spotLight.quadratic * Distance * Distance);
		
		result = (ambient + diffuse + specular) * intensity * attenuation;
	}
	return result;
}

void main()
{
	vec3 result = CaclDirectionLight(dirLight);
        
    for(int i = 0;i < NR_POINT_LIGHT; ++i)
		result += CaclPointLight(pointlights[i]);
		
	result += CaclSpotLight(spotLight);
	
    color = vec4(result, 1.0f);
} 