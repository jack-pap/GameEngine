#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// Vertex shader source code (shape)
const char* vertexShaderSource = R"(#version 460 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uvs;
out vec2 UVs;
void main()
{
	gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
	UVs = uvs;
})";

// Fragment shader source code (looks)
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

	// Vertices used for triangle vertices pos
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Down left
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Down right
		-0.5f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Up left
		0.5f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Up right

		//-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // In left
		//0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // In right
		//0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Down center
	};

	GLuint indices[] =
	{
		0, 2, 1, // Down left triangle
		1, 3, 2, // Center up triangle
		//5, 4, 1 // Down right triangle
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

	// Create and compile vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Create and compile fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Create shader program controller
	GLuint shaderProgram = glCreateProgram();

	// Attach shaders in order to use
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Link all shaders into the program object
	glLinkProgram(shaderProgram);

	// Deletes shaders after use
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// Object initilization for vertices attributes and objects
	GLuint VAO, VBO, EBO;

	// Generate VAO, VBO and EBO with 1 object
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind VAO to current object
	glBindVertexArray(VAO);

	// Bind VBO to current object and specify it as an GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Give vertices data to VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Bind EBO to current object and specify it as an GL_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// Give indices data to EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// Configure Vertex Attributes for VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// Enable attributes
	glEnableVertexAttribArray(0);

	// Optional binding for VAO and VBO, EBO
	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


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

		// Specify shaders for use, bind them and draw object
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
	
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);

		// Processes GLFW events every frame
		glfwPollEvents();		
	}

	// Delete shaders, VAO, VBO and EBO when done with
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	// Close window application and all contexts
	glfwDestroyWindow(window);
	// Close GLFW library
	glfwTerminate();
	return 0;
}


