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

	// Create a Vertex Array Object (an array of buffers).
	// Create a Vertex Buffer Object (to transfer data between CPU and GPU in batch).
	// Create a Element Array Buffer to store indices.
	GLuint VAO, VBO, EBO;

	// Our VAO has 1 Buffer object.
	glGenVertexArrays(1, &VAO);
	// Generate buffer with no. of objects, refernce to buffer.
	// pass arg "1" since we only have one 3D object.
	glGenBuffers(1, &VBO);
	// Generate a buffer for indices.
	glGenBuffers(1, &EBO);

	// Tell GL about the VAO of buffer.
	glBindVertexArray(VAO);
	// Bind object as Current Object (GL Current object is target for GL functions).
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Bind the EBO.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// Create Link with indices array.
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// Provide data to buffer.
	// GL_STATIC_DRAW : Current Data (singular) will be used to draw images on screen multiple times.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Define the VAO with the VBO.
	// 0 is the location of the Vertex.
	// 3 is the number of floats per Vertex.
	// GL_FLOAT is the datatype, GL_FALSE since we are not using normalized integers.
	// Next is the size of each Vertex.
	// Last is a (weird?) Null Pointer.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Bind the VBO, VAO, EBO so it's not accidently modified.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

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
		// Bind the Buffer.
		glBindVertexArray(VAO);
		// Draw Triangle :)
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		// Swap back and front buffers.
		glfwSwapBuffers(window);
		// Respond to Events.
		glfwPollEvents();
	}

	// ---------------- MEMORY CLEANUP ----------------
	// Delete VBO, VAO and EBO.
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	// Cleanup GLFW context.
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}