#include "../include/OpenGL.h"

bool	init_sdl()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("ERROR init sdl : %s\n", SDL_GetError());
		SDL_Quit();
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

bool	create_window(t_sdl *sdl)
{
	if ((sdl->window = SDL_CreateWindow("Test SDL 2.0",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL)) == 0)
	{
		printf("ERROR init window : %s\n", SDL_GetError());
		SDL_Quit();
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

bool	create_context(t_sdl *sdl)
{
	if ((sdl->contexte_opengl = SDL_GL_CreateContext(sdl->window)) == 0)
	{
		printf("%s", SDL_GetError());
		SDL_DestroyWindow(sdl->window);
		SDL_Quit();
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

bool	init_glew(t_sdl *sdl)
{
	if ((sdl->initialisation_glew = glewInit()) != GLEW_OK)
	{
		printf("glew init : %s\n", glewGetErrorString(sdl->initialisation_glew));
		SDL_GL_DeleteContext(sdl->contexte_opengl);
		SDL_DestroyWindow(sdl->window);
		SDL_Quit();
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
