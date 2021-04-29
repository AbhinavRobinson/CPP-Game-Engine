#version 330 core
out vec4 FragColor;

// get color data from vector
in vec3 color;

void main()
{
	// add color.
	FragColor = vec4(color , 1.0f);
}