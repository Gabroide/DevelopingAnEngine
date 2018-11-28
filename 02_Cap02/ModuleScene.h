#ifndef __ModuleScene_h__
#define __ModuleScene_h__

#include "Globals.h"
#include "Module.h"

class ModuleScene
{
public:
	ModuleScene();
	~ModuleScene();

	bool Init();
	bool CleanUp();

	update_status Update();

private:
	unsigned vbo;
};

#endif // __ModuleScene_h__