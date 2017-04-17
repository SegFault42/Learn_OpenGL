#include "../include/OpenGL.h"

int main(int argc, char **argv)
{
	SDL_Event		evenements;
	t_sdl			sdl;
	GLuint			program_id;
	float	vertices[] = {-0.5, -0.5,   0.0, 0.5,   0.5, -0.5};
	float color_vertices[] = {1.0, 0.0, 0.0,  0.0, 1.0, 0.0,  0.0, 0.0, 1.0};

	memset(&sdl, 0, sizeof(t_sdl));
	if (init_sdl() == EXIT_FAILURE || create_window(&sdl) == EXIT_FAILURE ||
			create_context(&sdl) == EXIT_FAILURE || init_glew(&sdl) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	program_id = load_program("./Shaders/couleur2D.vert", "./Shaders/couleur2D.frag");
	if (program_id == 1)
		printf("Creating shader success !\n");
	else
		printf("Creating shader failure !\n");


	glClearColor(0.2, 0.2, 0.2, 1.0);
	while(42)
	{
		SDL_WaitEvent(&evenements);
		if(evenements.window.event == SDL_WINDOWEVENT_CLOSE)
			break ;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(program_id);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, color_vertices);
		glEnableVertexAttribArray(1);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);

		glUseProgram(0);

		SDL_GL_SwapWindow(sdl.window);
	}
	SDL_GL_DeleteContext(sdl.contexte_opengl);
	SDL_DestroyWindow(sdl.window);
	SDL_Quit();
	return (EXIT_SUCCESS);
}
