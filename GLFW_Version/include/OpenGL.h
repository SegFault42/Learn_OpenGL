#ifndef OPENGL_H
# define OPENGL_H

# define GLEW_STATIC
# include "../../glew-2.0.0/include/GL/glew.h"
# include "../glfw-3.2.1/include/GLFW/glfw3.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h>
# include "../../SimpleOpenGLImageLibrary/src/SOIL.h"
#include "../include/libft.h"

typedef struct		s_shader
{
	GLuint			shaderProgram;
	GLchar			*fragment_shader;
	GLchar			*vertex_shader;
}					t_shader;

typedef struct		s_env
{
	GLFWwindow		*window;
	GLuint			width;
	GLuint			height;
	struct s_shader		shader;
}					t_env;


bool	init_glfw(t_env *env);
bool	init_glew(t_env *env);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void	compile_shader(t_env *env);

#endif
