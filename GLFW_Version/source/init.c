#include "../include/OpenGL.h"

bool	init_glfw(t_env *env)
{
	env->width = 800 * 2;
	env->height = 600 * 2;
	if (glfwInit() == GLFW_FALSE)
	{
		dprintf(2, "glfwInit Failure");
		return (EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Mac OS X only
	// Create a GLFWwindow object that we can use for GLFW's functions
	if ((env->window = glfwCreateWindow(env->width, env->height, "Win", NULL, NULL)) == NULL)
	{
		dprintf(2, "Creating window Failure");
		glfwTerminate();
		return (EXIT_FAILURE);
	}
	glfwMakeContextCurrent(env->window);
	// Set the required callback functions
	glfwSetKeyCallback(env->window, key_callback);

	return (EXIT_SUCCESS);
}

bool	init_glew(t_env *env)
{
	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (glewInit() != GLEW_OK)
	{
		dprintf(2, "Failed to Initialize GLEW !\n");
		glfwTerminate();
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
