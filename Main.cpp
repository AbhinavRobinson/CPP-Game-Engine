#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


// Program Starts here! 
// Creates a Window.
int main() {
	// Init GLFW.
	glfwInit();

	// Tell GLFW about the enviorment.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Vertices coordinates for equalateral triangle with inner divisions
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner Left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner Right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner Down
	};

	// Indices to create divisions and not waste Render power of invisible tris
	GLuint indices[] =
	{
		0,3,5, // Lower left Triangle
		3,2,4, // Lower Right Triangle
		5,4,1 // Upper Triangle
	};

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

	// Repaint Window with dark coral blue color.
	glClearColor(0.0f, 0.13f, 0.17f, 1.0f);
	// feed data into buffer.
	glClear(GL_COLOR_BUFFER_BIT);
	// Swap back and front buffers.
	glfwSwapBuffers(window);

	// ---------------- RENDER LOOP ----------------

	// Keep window open until closed by user.
	while (!glfwWindowShouldClose(window)) {
		// Repaint Window with dark coral blue color.
		glClearColor(0.0f, 0.13f, 0.17f, 1.0f);
		// feed data into buffer.
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw Triangle :)
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		// Swap back and front buffers.
		glfwSwapBuffers(window);
		// Respond to Events.
		glfwPollEvents();
	}

	// ---------------- MEMORY CLEANUP ----------------

	// Cleanup GLFW context.
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}