#version 330

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 colour;


uniform sampler2D theTexture;

uniform vec3 cameraPosition;

uniform vec3 lightColour;

uniform float ambientIntensity;
uniform float diffuseIntensity;

uniform vec3 LightPosition;

uniform float constant;
uniform float linear;
uniform float exponent;


void main() {
	vec3 lightDirection = FragPos - LightPosition;
	float distance = length(lightDirection);
	lightDirection = normalize(lightDirection);
	vec3 lightReflection = normalize(reflect(lightDirection, normalize(Normal)));

	vec4 ambientColour  = vec4(lightColour, 1.f) * ambientIntensity;

	float diffuseFactor = max(dot(normalize(Normal), lightReflection), 0.f);
	vec4 diffuseColour = vec4(lightColour * diffuseFactor * diffuseIntensity, 1.f);

	vec4 specularColour = vec4(0.f, 0.f, 0.f, 0.f);
	if (diffuseFactor > 0.f) {
		vec3 fragToEye = normalize(cameraPosition - FragPos);
		float specularFactor = max(dot(fragToEye, lightReflection), 0.f);
		if (specularFactor > 0.f) {
			specularFactor = pow(specularFactor, 20.f);
			specularColour = vec4(lightColour * specularFactor, 1.f);
		}
	}


	float attenuation = exponent * distance * distance +
						linear * distance +
						constant;
                        
    float shadowFactor = 0.0;
	
	vec4 finalColour = (ambientColour + (1.0 - shadowFactor) * (diffuseColour + specularColour)) / attenuation;
	colour = texture(theTexture, TexCoord) * finalColour;
}