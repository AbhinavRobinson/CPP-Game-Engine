#include"VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size) 
{
	// Generate buffer with no. of objects, refernce to buffer.
	// pass arg "1" since we only have one 3D object.
	glGenBuffers(1, &ID);
	// Bind object as Current Object (GL Current object is target for GL functions).
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	// Provide data to buffer.
	// GL_STATIC_DRAW : Current Data (singular) will be used to draw images on screen multiple times.
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}