#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

/// Program Starts here! 
/// Creates a GLFW Window.
int main() {
	glfwInit();

	/// Tell GLFW about the enviorment.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/// Create Window of size 800x800.
	/// GLFW Window pointer
	GLFWwindow* window = glfwCreateWindow(800, 800, "CPP-GameEngine", NULL, NULL);
	
	/// If window is not created, exit program.
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	/// If window is made, show it!
	glfwMakeContextCurrent(window);

	/// Init GLAD.
	gladLoadGL();

	/// Create Viewport with window dimensions.
	glViewport(0, 0, 800, 800);

	/// Repaint Window with dark coral blue color.
	glClearColor(0.0f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	/// Keep window open until closed by user.
	while (!glfwWindowShouldClose(window)) {
		/// Respond to Events.
		glfwPollEvents();
	}

	/// Cleanup GLFW context.
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}