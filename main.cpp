/*
Last update: February 18, 2026
Version: 1.0
Author: Gabriel A. Rivera
Title: ************************
Made with: Visual Studio 2022. Version: 17.

Additional information:
*************************
*/

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>


//Vertex and Fragment Shaders defaults.
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main()
{
	glfwInit();
	// Getting OpenGL current version in use. Using API gl: 3.3. https://glad.dav1d.de/
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Drawing a triangle using x, y, z coordinates. They are normalized (i.e., from 0 to 1).
	// You should check OpenGL datatypes here: https://registry.khronos.org/OpenGL-Refpages/gl4/
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,// Left corner.
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Right corner.
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Top corner.
	};

	// Getting the primary monitor for use fullscreen.
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	// Window settings.
	GLFWwindow* window = glfwCreateWindow(
		mode->width,
		mode->height,
		"Open GL",
		monitor,
		NULL
	);

	if (window == NULL)
	{
		std::cout << "Failed to create a GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Loading the needed configurations for OpenGL.
	gladLoadGL();


	// Area of the window we want OpenGL to render in.
	// Specify the viewport of OpenGL in the window.
	// In this case the viewport goes from x = 0, y = 0, to x = primary monitor width, y = primary monitor height.
	glViewport(
		0,
		0,
		mode->width,
		mode->height
	);


	/*
	PART-1
	*/
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

	/*
	PART-2
	*/
	GLuint VAO, VBO;
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Telling OpenGL to prepare to clear the color of a buffer and give it another color.
	// Normalized decimal RGB form of color.
	glClearColor(
		0.02f,
		0.02f,
		0.02f,
		1.0f
	);
	// Executing the command before.
	glClear(GL_COLOR_BUFFER_BIT);
	// Swapping buffers.
	glfwSwapBuffers(window);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(
			0.02f,
			0.02f,
			0.02f,
			1.0f
		);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);

		// Take care of all GLFW events.
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}