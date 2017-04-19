#include "../include/OpenGL.h"

int main()
{
	t_env	env;
	int			width;
	int			height;

	memset(&env, 0, sizeof(t_env));
	if (init_glfw(&env) == EXIT_FAILURE || init_glew(&env) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	// Define the viewport dimensions
	glfwGetFramebufferSize(env.window, &width, &height);
	glViewport(0, 0, width, height);

	unsigned char *image = SOIL_load_image("container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	compile_shader(&env);

	GLfloat vertices[] = {
		// Positions         // Colors
		0.5f, -0.5f, 0.0f,  0.5f, 0.0f, 0.0f,   // Bottom Right
		-0.5f, -0.5f, 0.0f,  0.5f, 0.5f, 0.0f,   // Bottom Left
		0.0f,  -1.0f, 0.0f,  0.5f, 0.0f, 0.5f    // Top 
	};
	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3  // First Triangle
		/*1, 2, 3   // Second Triangle*/
	};
	GLfloat texCoords[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.5f, 1.0f
	};
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	/*glGenBuffers(1, &EBO);*/
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);*/
	/*glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/


	//Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	/*glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind*/

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO


	// Uncommenting this call will result in wireframe polygons.
	/*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/

	// Game loop
	while (!glfwWindowShouldClose(env.window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw our first triangle
		glUseProgram(env.shader.shaderProgram);

		/*GLfloat time_value = glfwGetTime();*/
		/*GLfloat green_value = (sin(time_value) / 2) + 0.5;*/
		/*GLfloat blue_value = (sin(time_value) / 2) + 0.5;*/
		/*GLint vertex_color_location = glGetUniformLocation(env.shader.shaderProgram, "ourColor");*/
		/*glUniform4f(vertex_color_location, 0.0f, green_value, blue_value, 1.0f);*/

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(env.window);
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	/*glDeleteBuffers(1, &EBO);*/
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}
