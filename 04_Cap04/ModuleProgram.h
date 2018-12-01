#ifndef __ModuleProgram_h__
#define __ModuleProgram_h__

#include <assert.h>

#include "Module.h"

#include "glew-2.1.0\include\GL\glew.h"
#include "SDL\include\SDL.h"

class ModuleProgram : public Module
{
public:
	ModuleProgram();
	~ModuleProgram();

	bool Init() override;
	bool CleanUp() override;

	update_status PreUpdate() override;
	update_status Update() override;

	char* ReadShader(const char* path) const;

	GLuint CreateProgram(const char* vertexShader, const char* fragmentShader) const;
	
public:
	GLuint program;
	GLuint axisProgram;
};

#endif // #ifndef __ModuleProgram_h__