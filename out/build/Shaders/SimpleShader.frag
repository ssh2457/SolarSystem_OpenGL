#version 330

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 colour;

uniform sampler2D theTexture;

void main() {
	vec4 finalColour = vec4(1.f, 1.f, 1.f, 1.f);
	colour = texture(theTexture, TexCoord) * finalColour;
}
