#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>


const char* vertexShaderSource = R"(#version 460 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uvs;
out vec2 UVs;
void main()
{
	gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
	UVs = uvs;
})";
const char* fragmentShaderSource = R"(#version 460 core
out vec4 FragColor;
uniform sampler2D screen;
in vec2 UVs;
void main()
{
	FragColor = texture(screen, UVs);
})";

int main() {
	// Initialise GLFW library for use for functions to be used
	glfwInit();

	// GLFW hints are set to determine OpenGL version for us its 3 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Use CORE profile 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
	};

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

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



	GLuint VAO, VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Optional binding
	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0);


	// Set color to clear window with 
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Clear buffer and specify bg color
	glClear(GL_COLOR_BUFFER_BIT);
	// Swap back buffer with next in front
	glfwSwapBuffers(window);

	float prevTime = float(glfwGetTime());
	float angle = 0;

	// Loop to keep window open
	while (!glfwWindowShouldClose(window)) 
	{
		float time = float(glfwGetTime());
		if (time - prevTime >= 0.025f)
		{
			angle += 0.1f;
			prevTime = time;
			glClearColor(sinf(angle), cosf(angle), tanf(angle), 1.0f);

		}

		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);

		// Processes GLFW events every frame
		glfwPollEvents();		
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	// Close window application and all contexts
	glfwDestroyWindow(window);
	// Close GLFW library
	glfwTerminate();
	return 0;
}


