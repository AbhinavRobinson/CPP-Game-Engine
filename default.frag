#version 330 core
out vec4 FragColor;

// get color data from vector
in vec3 color;

in vec2 texCoord;

uniform sampler2D tex0;

void main()
{
	// add color.
	FragColor = texture(tex0, texCoord);
}