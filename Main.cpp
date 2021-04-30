#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Texture.h"
#include"Camera.h"

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

const unsigned int width = 800, height = 800;

// Program Starts here!
// Creates a Window.
int main() {
	// Init GLFW.
	glfwInit();

	// Tell GLFW about the enviorment.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create Window of size 800x800.
	GLFWwindow* window = glfwCreateWindow(width, height, "CPP-GameEngine", NULL, NULL);

	// If window is not created, exit program.
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// If window is made, show it!
	glfwMakeContextCurrent(window);

	// Init GLAD.
	gladLoadGL();

	// Create Viewport with window dimensions.
	glViewport(0, 0, width, height);

	// Load in vertex and fragment shaders into pipeline
	Shader shaderProgram("default.vert", "default.frag");

	// Create a Vertex Array Object to Hold our vector objects
	VAO VAO1;
	VAO1.Bind();

	// Create a Vertex Buffer Object to go in the VAO
	VBO VBO1(vertices, sizeof(vertices));
	// Create a Element Buffer Object to hold our indices
	EBO EBO1(indices, sizeof(indices));

	// Link VAO <---> VBO
	// Coordinate stride
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	// Color stride
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	// Texture stride
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	// Cleanup
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Texture
	Texture brickTex("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	brickTex.texUnit(shaderProgram, "tex0", 0);

	// Add depth to vertices for clipping.
	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	// ---------------- RENDER LOOP ----------------
	// Keep window open until closed by user.
	while (!glfwWindowShouldClose(window)) {
		// Repaint Window with dark coral blue color.
		glClearColor(0.0f, 0.13f, 0.17f, 1.0f);
		// feed data into buffer.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Start Shader Program
		shaderProgram.Activate();

		camera.Inputs(window);
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		brickTex.Bind();
		// Load in the VAO
		VAO1.Bind();
		// Draw Triangle :)
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		// Swap back and front buffers.
		glfwSwapBuffers(window);
		// Respond to Events.
		glfwPollEvents();
	}

	// ---------------- MEMORY CLEANUP ----------------
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	brickTex.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}