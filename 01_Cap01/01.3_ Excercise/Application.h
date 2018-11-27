#ifndef __Application_h__
#define __Application_h__

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	bool CleanUp();
	bool Start();

	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();

public:
	ModuleRender *renderer;
	ModuleWindow *window;
	ModuleTextures *textures;
	ModuleInput *input = NULL;

private:

	std::list<Module*> modules;

};

extern Application* App;

#endif // __Application_h__