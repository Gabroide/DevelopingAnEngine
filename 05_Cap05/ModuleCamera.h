#ifndef __ModuleCamera_h__
#define __ModuleCamera_h__

#include "Module.h"
#include "Point.h"

#include "glew-2.1.0\include\GL\glew.h"

#include "MathGeoLib\include\Math\float4x4.h"
#include "MathGeoLib\include\Math\float3.h"
#include "MathGeoLib\include\Geometry\Frustum.h"

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

	Frustum frustum;
	math::float3& cameraPosition = math::float3(0.0f, 1.0f, 10.0f);
	math::float3& cameraFront = math::float3(0.0f, 0.0f, -1.0f);
	math::float3& cameraUp = math::float3(0.0f, 1.0f, 0.0f);

	float mSpeed = 0.5f;
	float rSpeed = 1.0f;

	float pitch = 0;
	float yaw = 0;

	bool firstMouse = true;
	int lastX = 0;
	int lastY = 0;

	float fovY = 45.0f;
	float fovX = 45.0f;

	int screenWidth = SCREEN_WIDTH;
	int screenHeight = SCREEN_HEIGHT;
};

#endif // __ModuleCamera_h__