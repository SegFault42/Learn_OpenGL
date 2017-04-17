#version 330
layout(location = 0)
in vec3 vertexPosition;
out vec4 myColor;
uniform mat4 MVP;

void main()
{
	gl_Position =  MVP * vec4(vertexPosition, 1);
	myColor = vec4(gl_Position.x, gl_Position.x, gl_Position.x, 1);
}

