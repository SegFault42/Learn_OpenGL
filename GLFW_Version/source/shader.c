#include "../include/OpenGL.h"

void	get_sahder(t_env *env, GLchar **shader, char *file)
{
	char	*line;
	int		fd;
	int		size;

	if (access(file, F_OK | R_OK) < 0)
	{
		printf("%s not found : %s\n", file, strerror(errno));
		exit(EXIT_FAILURE) ;
	}
	fd = open(file, O_RDONLY);
	size = lseek (fd, 0L, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	if ((*shader = (char *)ft_memalloc(sizeof(char) * size + 1)) == NULL)
	{
		dprintf(2, "Memory allocation failure\n");
		close(fd);
		exit(EXIT_FAILURE);
	}
	while (get_next_line(fd, &line) > 0)
	{
		ft_strcat(*shader, line);
		ft_strcat(*shader, "\n");
		ft_strdel(&line);
	}
	close(fd);
}

void	compile_shader(t_env *env)
{
	GLint		success;
	GLchar		infoLog[512];
	GLuint		vertexShader;
	GLuint		fragmentShader;

	get_sahder(env, &env->shader.fragment_shader, "./fragment_shader.glsl");
	get_sahder(env, &env->shader.vertex_shader, "./vertex_shader.glsl");
	//=========================================================================
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, (const char **)&env->shader.vertex_shader, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED : %s\n", infoLog);
	}
	//=========================================================================
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (const char **)&env->shader.fragment_shader, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED : %s\n", infoLog);
	}
	//=========================================================================
	env->shader.shaderProgram = glCreateProgram();
	glAttachShader(env->shader.shaderProgram, vertexShader);
	glAttachShader(env->shader.shaderProgram, fragmentShader);
	glLinkProgram(env->shader.shaderProgram);
	glGetProgramiv(env->shader.shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(env->shader.shaderProgram, 512, NULL, infoLog);
		printf("ERROR::SHADER::PROGRAM::LINKING_FAILED : %s\n", infoLog);
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	free(env->shader.fragment_shader);
	free(env->shader.vertex_shader);
}
