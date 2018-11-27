#ifndef __Application_h__
#define __Application_h__

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleScene;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	bool CleanUp();
	bool Start();

	update_status Update();

public:
	ModuleRender *renderer = NULL;
	ModuleWindow *window = NULL;
	ModuleTextures *textures = NULL;
	ModuleInput *input = NULL;

private:

	std::list<Module*> modules;

};

extern Application* App;

#endif // __Application_h__