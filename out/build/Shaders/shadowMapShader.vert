#version 330

layout (location = 0) in vec3 pos;

uniform mat4 world;
uniform mat4 directionalLightTransform; // directionalLightTransform = projection * cameara??

void main()
{
	gl_Position = directionalLightTransform * world * vec4(pos, 1.0);
}
