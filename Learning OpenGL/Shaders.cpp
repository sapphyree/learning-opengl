#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "./shader.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main() {

	// glfw initialise + config
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	GLFWwindow* window = glfwCreateWindow(800, 600, "Shaders", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glfw load function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialise GLAD" << std::endl;
		return -1;
	}

	// Shader file readings
	Shader ourShader("C:\\Users\\Sapphyre\\source\\repos\\Learning OpenGL\\Learning OpenGL\\shader.vs", "C:\\Users\\Sapphyre\\source\\repos\\Learning OpenGL\\Learning OpenGL\\shader.fs");

	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
	};

	// vertex array object (VAO) stores calls to vertex attributes and VBOs to reduce multiple calls
	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// rendering loop
	while (!glfwWindowShouldClose(window)) {
		// input processing
		processInput(window);

		// rendering code
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw triangle
		ourShader.use();
		
		float timeValue = glfwGetTime();
		//float greenValue = sin(timeValue) / 2.0f + 0.5f;
		float xOffset = sin(timeValue);
		float yOffset = cos(timeValue);
		
		ourShader.setFloat("xOffset", xOffset);
		ourShader.setFloat("yOffset", yOffset);		
		
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3); // drawing from vertex array object

		// check & call events & swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// glfw cleanup
	glfwTerminate();
	return 0;
}

// boilerplate
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}