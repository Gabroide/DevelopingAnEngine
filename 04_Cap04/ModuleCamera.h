#ifndef __ModuleCamera_h__
#define __ModuleCamera_h__

#include "Module.h"
#include "MathGeoLib.h"
#include "Point.h"
#include "glew-2.1.0\include\GL\glew.h"

enum Directions {
	UP,
	DOWN,
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};



class ModuleCamera : public Module
{
public:
	ModuleCamera();
	~ModuleCamera();

	bool Init() override;
	bool CleanUp() override;

	update_status PreUpdate() override;
	update_status Update() override;

	void SetPlaneDistances(const float nearDist, const float farDist);
	math::float4x4 LookAt(const math::float3& cameraPosition, math::float3& cameraFront, const math::float3& cameraUp);
	void Move(const Directions dir);
	void MouseUpdate();
	void SetVerticalFOV(const float fovY);
	void SetHorizontalFOV(const float fovX);
	void Orbit();
	void Focus();

	void RefenceGround() const;
	void ReferenceAxis() const;

	void WindowResized(const unsigned width, const unsigned height);

public:

};

#endif // __ModuleCamera_h__