#ifndef __ModuleApplication_h__
#define __ModuleApplication_h__

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleScene;
class ModuleProgram;
class ModuleEditor;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* renderer = nullptr;
	ModuleWindow* window = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleInput* input = nullptr;
    ModuleScene* scene = nullptr;
	ModuleProgram* program = nullptr;
	ModuleEditor* editor = nullptr;

private:

	std::list<Module*> modules;

};

extern Application* App;

#endif // #ifndef __ModuleApplication_h__