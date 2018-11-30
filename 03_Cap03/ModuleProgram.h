#ifndef __ModuleProgram_h__
#define __ModuleProgram_h__

class ModuleProgram : public Module
{
public:
	ModuleProgram();
	~ModuleProgram();

	bool Init();

	update_status Update();

	char* readShaderFile(const char* shaderPath);

	void CheckCompilationErrors(GLuint shader);

	bool CleanUp();

	GLuint program;
};


#endif // #ifndef __ModuleProgram_h__