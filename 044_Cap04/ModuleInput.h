#ifndef __ModuleInput_h__
#define __ModuleInput_h__

#include "Module.h"
#include "Globals.h"

typedef unsigned __int8 Uint8;

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status Update();
	bool CleanUp();

	private:
		const Uint8 *keyboard = NULL;
};

#endif // #ifndef __ModuleInput_h__