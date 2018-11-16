#ifndef __ModuleWindow_h__
#define __ModuleWindow_h__

#include "Module.h"
#include "SDL/include/SDL.h"

class Application;

class ModuleWindow : public Module
{
public:
	ModuleWindow();

	// Destructor
	virtual ~ModuleWindow();

	bool Init() override; // Called before quitting
	bool CleanUp() override; // Called before quitting

public:
	SDL_Window* window = NULL; //The window we'll be rendering to
	SDL_Surface* screen_surface = NULL; //The surface contained by the window
};

#endif // __ModuleWindow_h__