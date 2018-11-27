#ifndef __ModuleScene_h__
#define __ModuleScene_h__

#include "Globals.h"
#include "Module.h"

class ModuleScene
{
public:
	ModuleScene();
	~ModuleScene();

	bool Start();

	update_status Update();
};

#endif // __ModuleScene_h__