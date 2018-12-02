#version 330

layout(loaction = 0) in vec3 vertex position;

void main()
{
	gl_Position = vec4(vertex_position, 1.0);
}