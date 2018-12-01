#include "ModuleCamera.h"

#include "Application.h"
#include "ModuleInput.h"
#include "ModuleProgram.h"

#include "glew-2.1.0\include\GL\glew.h"
#include "SDL\include\SDL.h"
#include "MathGeoLib\include\MathGeoLib.h"

ModuleCamera::ModuleCamera()
{
}

ModuleCamera::~ModuleCamera()
{
}

bool ModuleCamera::Init()
{
	frustum.type = FrustumType::PerspectiveFrustum;
	frustum.pos = math::float3(0.0f, 1.0f, 10.0f);
	frustum.front = -float3::unitZ;
	frustum.up = float3::unitY;
	frustum.nearPlaneDistance = 0.1f;
	frustum.farPlaneDistance = 100.0f;
	frustum.verticalFov = math::pi / 4.0f;
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f) * ((float)screenWidth / (float)screenHeight));

	return true;
}

math::float4x4 ModuleCamera::LookAt(const math::float3& cameraPosition, math::float3& cameraFront, const math::float3& cameraUp)
{
	math::float4x4 matrix;

	cameraFront.Normalize();
	math::float3 side(cameraFront.Cross(cameraUp));
	side.Normalize();
	math::float3 up(side.Cross(cameraFront));

	matrix[0][0] = side.x; matrix[0][1] = side.y; matrix[0][2] = side.z;
	matrix[1][0] = up.x; matrix[1][1] = up.y; matrix[1][2] = up.z;
	matrix[2][0] = -cameraFront.x; matrix[2][1] = -cameraFront.y; matrix[2][2] = -cameraFront.z;
	matrix[0][3] = -side.Dot(cameraPosition); matrix[1][3] = -up.Dot(cameraPosition); matrix[2][3] = cameraFront.Dot(cameraPosition);
	matrix[3][0] = 0.0f; matrix[3][1] = 0.0f; matrix[3][2] = 0.0f; matrix[3][3] = 1.0f;
	return matrix;
}

