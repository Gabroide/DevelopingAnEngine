#ifndef __ModuleRenderScene_h__
#define __ModuleRenderScenee_h__

#include "Module.h"

class ModuleScene : public Module
{
public:
    ModuleScene();
    ~ModuleScene();

	bool Init() override;
	bool CleanUp() override;

	update_status Update() override;

private:
    unsigned vbo        = 0;

};

#endif /* __ModuleScene_h__ */
