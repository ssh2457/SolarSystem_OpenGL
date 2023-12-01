#include "include/Mesh.h"

Mesh::Mesh() : mVAO(0) , mVBO(0) , mIBO(0) , mIndexCount(0) {

}

Mesh::~Mesh() {
	ClearMesh();
}

void Mesh::CreateMesh(GLfloat* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices) {
	mIndexCount = numOfIndices;

	// Generate VAO
	glGenVertexArrays(1, &mVAO);

	// Bind VAO
	glBindVertexArray(mVAO);

	// Generate IBO
	glGenBuffers(1, &mIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * mIndexCount, indices, GL_STATIC_DRAW);

	// Generate VBO
	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW);

	// Register attribute pointer
	/*
	glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)

	index: ID
	size: Number of data to input for each vertex
	type: data type
	normalized: bool value
	stride: The Number of data for each vertex


	==
	glEnableVertexAttribArray(GLuint index)
	index: ID
	*/

	// Register position(x, y, z)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, 0);
	glEnableVertexAttribArray(0);

	// Register UV
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 3));
	glEnableVertexAttribArray(1);

	// Register normal vector(nx, ny, nz)
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 5));
	glEnableVertexAttribArray(2);

	// Unbind VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Unbind VAO
	glBindVertexArray(0);

	// Unbind IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::RenderMesh() {
	// Bind VAO
	glBindVertexArray(mVAO);

	// Bind IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);


	// Draw
	glDrawElements(GL_TRIANGLES, mIndexCount, GL_UNSIGNED_INT, 0);

	// Unbind VAO
	glBindVertexArray(0);

	// Unbind IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::ClearMesh() {
	if (mIBO != 0) {
		glDeleteBuffers(1, &mIBO);
	}

	if (mVBO != 0) {
		glDeleteBuffers(1, &mVBO);
	}

	if (mVAO != 0) {
		glDeleteBuffers(1, &mVAO);
	}

	mIndexCount = 0;

}
