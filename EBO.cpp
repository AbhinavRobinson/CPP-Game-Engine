#include"EBO.h"

EBO::EBO(GLuint* indices, GLsizeiptr size)
{
	// Generate buffer with no. of objects, refernce to buffer.
	// pass arg "1" since we only have one 3D object.
	glGenBuffers(1, &ID);
	// Bind object as Current Object (GL Current object is target for GL functions).
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	// Provide data to buffer.
	// GL_STATIC_DRAW : Current Data (singular) will be used to draw images on screen multiple times.
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete()
{
	glDeleteBuffers(1, &ID);
}