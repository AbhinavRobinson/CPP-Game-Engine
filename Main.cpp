#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Texture.h"

// Vertices coordinates
GLfloat vertices[] =
{ //       COORDINATES       |       COLOR          //
	-0.5f , -0.5f , 0.0f      , 1.0f, 0.0f , 0.0f  , 0.0f, 0.0f,// Lower left corner
	-0.5f ,  0.5f , 0.0f      , 0.0f, 1.0f , 0.0f  , 0.0f, 1.0f,// Upper left corner
	 0.5f ,  0.5f , 0.0f      , 0.0f, 0.0f , 1.0f  , 1.0f, 1.0f,// Upper right corner
	 0.5f , -0.5f , 0.0f      , 1.0f, 1.0f , 1.0f  , 1.0f, 0.0f,// Lower right corner
};

// Indices for vertices order
GLuint indices[] =
{
	0, 2, 1, // Upper triangle
	0, 3, 2  // Lower triangle
};

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
	GLFWwindow* window = glfwCreateWindow(800, 800, "CPP-GameEngine", NULL, NULL);

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
	glViewport(0, 0, 800, 800);

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

	// Add Uniform scaler (size up or down vector shapes).
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// Texture

	// Texture
	Texture popCat("pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popCat.texUnit(shaderProgram, "tex0", 0);

	// ---------------- RENDER LOOP ----------------
	// Keep window open until closed by user.
	while (!glfwWindowShouldClose(window)) {
		// Repaint Window with dark coral blue color.
		glClearColor(0.0f, 0.13f, 0.17f, 1.0f);
		// feed data into buffer.
		glClear(GL_COLOR_BUFFER_BIT);
		// Start Shader Program
		shaderProgram.Activate();
		// Scale the vector.
		glUniform1f(uniID, 0.5f);
		popCat.Bind();
		// Load in the VAO
		VAO1.Bind();
		// Draw Triangle :)
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
	popCat.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}