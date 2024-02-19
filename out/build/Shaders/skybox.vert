#version 330

layout (location = 0) in vec3 pos;

out vec3 TexCoords;

layout (std140) uniform Matrices {
	mat4 projection;
	mat4 view;
};

void main()
{
    TexCoords = pos;
    gl_Position = projection * view * vec4(pos, 1.0);
}
