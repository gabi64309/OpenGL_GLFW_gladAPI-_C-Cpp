/*
Last update: February 17, 2026
Version: 1.0
Author: Gabriel A. Rivera
Title: Setting a fullscreen with OpenGL, GLFW & glad API
Made with: Visual Studio 2022. Version: 17.

Additional information:
Feel free to use this skeleton/boilerplate code.
*/

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main()
{
	glfwInit();
	// Getting OpenGL current version in use. Using API gl: 3.3. https://glad.dav1d.de/
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


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
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}