#ifndef __ModuleRenderScene_h__
#define __ModuleRenderScenee_h__

#include "Module.h"

#include "Math\float4x4.h"
#include "Math\float3.h"

class ModuleScene : public Module
{
public:
    ModuleScene();
    ~ModuleScene();

	bool Init() override;
	bool CleanUp() override;

	//update_status PreUpdate();
	update_status Update() override;

	float4x4 Transform(float3 eye, float3 target);

private:
    unsigned vbo = 0;

	float3 target = { 0,0,0 };
	float3 eye = { 1,1,5 };
	float3 up = { 0,1,0 };
	//float triangle[30];
	float4x4 viewMatrix;
	float4x4 projectionMatrix;
	float4x4 transformationMatrix;
	//float pitch;
};

#endif /* __ModuleScene_h__ */
