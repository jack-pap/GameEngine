#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main() {
	// Initialise GLFW library for use for functions to be used
	glfwInit();

	// GLFW hints are set to determine OpenGL version for us its 3 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Use CORE profile 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Window dimensions and window name set
	GLFWwindow* window = glfwCreateWindow(1000, 1000, "ExtinctEngine", NULL, NULL);

	// Error checking incase glfw fails to create window with terminal output message
	if (window == NULL) 
	{
		std::cout << "ERROR: Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Create window
	glfwMakeContextCurrent(window);

	// Load GLAD to configure OpenGL
	gladLoadGL();

	// Set GLAD viewport for window from x,y coordinates to other x,y coordinates
	glViewport(0, 0, 1000, 1000);

	// Set color to clear window with 
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Clear buffer and specify bg color
	glClear(GL_COLOR_BUFFER_BIT);
	// Swap back buffer with next in front
	glfwSwapBuffers(window);

	// Loop to keep window open
	while (!glfwWindowShouldClose(window)) 
	{
		// Processes GLFW events every frame
		glfwPollEvents();
	}

	// Close window application and all contexts
	glfwDestroyWindow(window);
	// Close GLFW library
	glfwTerminate();
	return 0;
}