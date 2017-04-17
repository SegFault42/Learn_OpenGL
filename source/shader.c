#include "../include/OpenGL.h"

int		check_file(char *file)
{
	if (access(file, R_OK) == -1)
	{
		printf("The file '%s' cannot be read\n", file);
		return (FALSE);
	}
	return (TRUE);
}

char			*shader_load_source(char *file)
{
	char	*re;
	char	*tmp;
	char	buff[BUFF_SIZE + 1];
	int		fd;
	int		readre;

	if (check_file(file) == FALSE)
		return (NULL);
	if ((fd = open(file, O_RDONLY)) != -1)
	{
		while ((readre = read(fd, buff, BUFF_SIZE - 1)) > 0)
		{
			tmp = re;
			buff[readre] = '\0';
			if (re)
				re = ft_strjoin(re, buff);
			else
				re = ft_strdup(buff);
			ft_strdel(&tmp);
		}
		return (re);
	}
	return (NULL);
}

static GLuint	shader_com_file(GLenum type, char *file_path)
{
	char	*source;
	GLuint	shader;
	GLint	length;
	GLint	result;
	char	*log;

	source = shader_load_source(file_path);
	if (!source)
		return (0);
	shader = glCreateShader(type);
	length = ft_strlen(source);
	glShaderSource(shader, 1, (const char **)&source, &length);
	glCompileShader(shader);
	ft_strdel(&source);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		log = malloc(length);
		glGetShaderInfoLog(shader, length, &result, log);
		fprintf(stderr, "Unable to compile %s: %s\n", file_path, log);
		ft_strdel(&log);
		return (0);
	}
	return (shader);
}

GLuint			shader_attach_file(GLuint program, GLenum type, char *file_path)
{
	GLuint shader;

	shader = shader_com_file(type, file_path);
	if (shader != 0)
	{
		glAttachShader(program, shader);
	}
	return (shader);
}

void			error(GLint *result, GLuint program_id)
{
	GLint	length;
	char	*log;

	glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &length);
	log = malloc(length);
	glGetProgramInfoLog(program_id, length, result, log);
	fprintf(stderr, "sceneInit(): Program linking failed: %s\n", log);
	ft_strdel(&log);
	glDeleteProgram(program_id);
}

GLuint			load_program(char *vertex_shader, char *fragment_shader)
{
	GLint	result;
	GLuint	program_id;
	GLuint	shaders[2];

	program_id = glCreateProgram();
	shaders[0] = shader_attach_file(program_id,
			GL_VERTEX_SHADER, vertex_shader);
	shaders[1] = shader_attach_file(program_id,
			GL_FRAGMENT_SHADER, fragment_shader);
	glLinkProgram(program_id);
	glGetProgramiv(program_id, GL_LINK_STATUS, &result);
	if (result == GL_FALSE)
	{
		error(&result, program_id);
		program_id = 0;
	}
	glDetachShader(program_id, shaders[0]);
	glDetachShader(program_id, shaders[1]);
	glDeleteShader(shaders[0]);
	glDeleteShader(shaders[1]);
	return (program_id);
}
