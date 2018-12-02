#include "ModuleProgram.h"

#include <errno.h>

#include "glew-2.1.0\include\GL\glew.h"

ModuleProgram::ModuleProgram()
{
}


ModuleProgram::~ModuleProgram()
{
}

bool ModuleProgram::Init()
{
	program = CreateProgram("Default.vs", "default.fs");
	axisProgram = CreateProgram("defaultColor.vs", "defaultColor.fs");

	return true;

/*	bool ret = true;
	// How to: https://badvertex.com/2012/11/20/how-to-load-a-glsl-shader-in-opengl-using-c.html
	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	GLint compileStatus = GL_FALSE;
	int logLength = 0;

	char* vertShaderStr = readShaderFile("default.vs");
	char* fragShaderStr = readShaderFile("default.fs");

	if (vertShaderStr == nullptr || fragShaderStr == nullptr)
	{
		LOG("Error: Reading shaders failed");
		return GL_FALSE;
	}

	// Compile shaders
	glShaderSource(vertShader, 1, &vertShaderStr, NULL);
	glCompileShader(vertShader);
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &compileStatus);

	if (!compileStatus) 
	{
		LOG("Error: Failed compiling vertex shader");
		CheckCompilationErrors(vertShader);
		return GL_FALSE;
	}

	glShaderSource(fragShader, 1, &fragShaderStr, NULL);
	glCompileShader(fragShader);
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &compileStatus);

	if (!compileStatus)
	{
		LOG("Error: Failed compiling fragment shader");
		CheckCompilationErrors(fragShader);
		return GL_FALSE;
	}

	// Compile Program
	program = glCreateProgram();
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &compileStatus);

	// Remove shaders, we wont need them anymore if they are loaded correctly into Program
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	return ret;*/
}

update_status ModuleProgram::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status ModuleProgram::Update()
{

	return UPDATE_CONTINUE;
}

GLuint ModuleProgram::CreateProgram(const char* vertexShaderPath, const char* fragmentShaderPath) const {

	assert(vertexShaderPath != NULL);
	assert(fragmentShaderPath != NULL);

	char* dataVertex = ReadShader(vertexShaderPath);
	char* dataFragment = ReadShader(fragmentShaderPath);

	GLuint vertexShader, fragmentShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, &dataVertex, NULL);
	glCompileShader(vertexShader);

	glShaderSource(fragmentShader, 1, &dataFragment, NULL);
	glCompileShader(fragmentShader);

	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}

char* ModuleProgram::ReadShader(const char* path) const
{
	assert(path != NULL);

	char* dataVertex = nullptr;
	FILE* file = nullptr;
	int sizeFragment;
	fopen_s(&file, path, "rb");
	if (file)
	{
		fseek(file, 0, SEEK_END);
		sizeFragment = ftell(file);
		rewind(file);
		dataVertex = (char*)malloc(sizeFragment + 1);
		fread(dataVertex, 1, sizeFragment, file);
		dataVertex[sizeFragment] = 0;
		fclose(file);
	}

	return dataVertex;
}

bool ModuleProgram::CleanUp()
{
	glDeleteProgram(program);
	glDeleteProgram(axisProgram);
	return true;
}