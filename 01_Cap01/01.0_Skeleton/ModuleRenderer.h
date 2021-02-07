#ifndef __ModuleRenderer_h__
#define __ModuleRenderer_h__

#include "Module.h"
#include "Globals.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class ModuleRenderer : public Module
{
public:
	ModuleRenderer();
	~ModuleRenderer();

	bool Init() override;
	bool CleanUp() override;

	update_status Update() override;

	bool Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section);

public:
	SDL_Renderer* renderer = NULL;
};

#endif // __ModuleRenderer_h__
