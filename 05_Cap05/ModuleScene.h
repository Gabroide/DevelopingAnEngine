#ifndef __ModuleScene_h__
#define __ModuleScene_h__

#include "Module.h"
#include "MathGeoLib.h"
#include "GL/glew.h"

class ModuleScene : public Module
{
public:
    ModuleScene();
    ~ModuleScene();

	bool            Init    ();
	update_status   Update  ();
	bool            CleanUp ();

	bool drawLenna = false;
	GLuint texture;
private:
	unsigned vbo = 0;
};

#endif
