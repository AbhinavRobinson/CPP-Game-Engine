#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

/// <summary>
/// Program Starts here! 
/// 
/// Creates a GLFW Window.
/// </summary>
int main() {
	glfwInit();

	/// <summary>
	/// Tell GLFW about the enviorment.
	/// </summary>
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/// <summary>
	/// Create Window of size 800x800.
	/// </summary>
	/// <returns>GLFW Window pointer</returns>
	GLFWwindow* window = glfwCreateWindow(800, 800, "CPP-GameEngine", NULL, NULL);
	
	/// <summary>
	/// If window is not created, exit program.
	/// </summary>
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	/// <summary>
	/// If window is made, show it!
	/// </summary>
	glfwMakeContextCurrent(window);

	/// <summary>
	/// Init GLAD.
	/// </summary>
	gladLoadGL();

	/// <summary>
	/// Create Viewport with window dimensions.
	/// </summary>
	glViewport(0, 0, 800, 800);

	/// <summary>
	/// Repaint Window with dark coral blue color.
	/// </summary>
	glClearColor(0.0f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	/// <summary>
	/// Keep window open until closed by user.
	/// </summary>
	while (!glfwWindowShouldClose(window)) {
		/// <summary>
		/// Respond to Events.
		/// </summary>
		glfwPollEvents();
	}

	/// <summary>
	/// Cleanup GLFW context.
	/// </summary>
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}