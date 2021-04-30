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

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)(width / height), 0.1f, 100.0f);

		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		// Scale the vector.
		glUniform1f(uniID, 0.0f);
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