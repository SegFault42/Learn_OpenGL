#ifndef OPENGL_H
# define OPENGL_H

#include <stdio.h>
#include <stdbool.h>
#include "../SDL2-2.0.5/include/SDL.h"
#include "../glew-2.0.0/include/GL/glew.h"
#include "./libft.h"
# define TRUE 1
# define FALSE 0

# define GL3_PROTOTYPES	1

# define WIDTH			800
# define HEIGHT			600

typedef struct		s_sdl
{
	SDL_GLContext	contexte_opengl;
	SDL_Window		*window;
	GLenum			initialisation_glew;
}					t_sdl;

bool	init_sdl();
bool	create_window(t_sdl *sdl);
bool	create_context(t_sdl *sdl);
bool	init_glew(t_sdl *sdl);
GLuint			load_program(char *vertex_shader, char *fragment_shader);

#endif
