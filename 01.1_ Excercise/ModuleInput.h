#ifndef __ModuleInput_h__
#define __ModuleInput_h__

#include "Module.h"
#include "Globals.h"

#include "SDL/include/SDL_scancode.h"

typedef unsigned __int8 Uint8;

/*enum EventWindow
{
	WE_QUIT = 0,
	WE_HIDE = 1,
	WE_SHOW = 2,
	WE_COUNT
};*/

enum KeyState
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class ModuleInput : public Module
{
public:
	ModuleInput();
	~ModuleInput();

	bool Init() override;
	bool CleanUp() override;

	// Check for window events last frame
	//bool GetWindowEvent(EventWindow code) const;

	update_status Update() override;

	// Check key states (includes mouse and joy buttons)
	KeyState GetKey(int id) const
	{
		return keyboard[id];
	}

private:
	//bool		windowEvents[WE_COUNT];
	KeyState*	keyboard;
	//const Uint8 *keyboard = NULL;
};

#endif // __ModuleInput_h__