#ifndef __Application_h__
#define __Application_h__

#include<list>
#include "Globals.h"
#include "Module.h"
#include "ModuleScene.h"

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
	ModuleRender *renderer;
	ModuleWindow *window;
	ModuleTextures *textures;
	ModuleInput *input;
	ModuleScene *scene;

private:

	std::list<Module*> modules;

};

extern Application* App;

#endif // __Application_h__