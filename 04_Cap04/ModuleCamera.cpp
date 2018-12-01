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

void ModuleCamera::Focus()
{
	math::AABB boundingBox = math::AABB(App->modelLoader->minPoint, App->modelLoader->maxPoint);
	math::float3 center = boundingBox.FaceCenterPoint(5);

	//Reset all variables (position, front, up, fov, pitch, yaw, firstmouse)
	frustum.pos = cameraPosition = math::float3(center.x, center.y, 0.0f);
	frustum.front = cameraFront = math::float3(0.0f, 0.0f, -1.0f);
	frustum.up = cameraUp = math::float3(0.0f, 1.0f, 0.0f);
	frustum.verticalFov = math::pi / 4.0f;
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f) * ((float)screenWidth / (float)screenHeight));
	fovY = 45.0f;
	fovX = 45.0f;
	pitch = 0;
	yaw = 0;
	firstMouse = true;

	//Add distance still we can see all the bounding box
	while (!App->camera->frustum.Contains(boundingBox))
	{
		App->camera->cameraPosition.z = App->camera->frustum.pos.z += 10;
	}
}

void ModuleCamera::Move(const Directions dir)
{
	switch (dir) {
	case UP:
		frustum.pos = cameraPosition += cameraUp.Normalized() * mSpeed;
		break;
	case DOWN:
		frustum.pos = cameraPosition -= cameraUp.Normalized() * mSpeed;
		break;
	case FORWARD:
		frustum.pos = cameraPosition += cameraFront.Normalized() * mSpeed;
		break;
	case BACKWARD:
		frustum.pos = cameraPosition -= cameraFront.Normalized() * mSpeed;
		break;
	case LEFT:
		frustum.pos = cameraPosition += cameraUp.Cross(cameraFront).Normalized() * mSpeed;
		break;
	case RIGHT:
		frustum.pos = cameraPosition -= cameraUp.Cross(cameraFront).Normalized() * mSpeed;
		break;
	}
}

void ModuleCamera::SetPlaneDistances(const float nearDist, const float farDist)
{
	if (nearDist > 0.0f && nearDist < frustum.farPlaneDistance)
	{
		frustum.nearPlaneDistance = nearDist;
	}

	if (farDist > 0.0f && farDist > frustum.nearPlaneDistance)
	{
		frustum.farPlaneDistance = farDist;
	}
}

void ModuleCamera::WindowResized(const unsigned width, const unsigned height)
{
	glViewport(0, 0, width, height);
	screenWidth = width;
	screenHeight = height;
	SetHorizontalFOV(fovX);
	SetVerticalFOV(fovY);
}

void ModuleCamera::SetHorizontalFOV(const float fovX) {
	frustum.horizontalFov = math::DegToRad(fovX);
	frustum.verticalFov = 2.0f * atanf(tanf(frustum.horizontalFov * 0.5f) * ((float)screenHeight / (float)screenWidth));
}

void ModuleCamera::SetVerticalFOV(const float fovY) {
	frustum.verticalFov = math::DegToRad(fovY);
	frustum.horizontalFov = 2.0f * atanf(tanf(frustum.verticalFov * 0.5f) * ((float)screenWidth / (float)screenHeight));
}

void ModuleCamera::RefenceGround() const
{
	glLineWidth(1.0f);
	float d = 200.0f;
	float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glUniform4fv(glGetUniformLocation(App->program->axisProgram, "newColor"), 1, color);
	glBegin(GL_LINES);
	for (float i = -d; i <= d; i += 1.0f)
	{
		glVertex3f(i, 0.0f, -d);
		glVertex3f(i, 0.0f, d);
		glVertex3f(-d, 0.0f, i);
		glVertex3f(d, 0.0f, i);
	}
	glEnd();
}

void ModuleCamera::ReferenceAxis() const
{
	glLineWidth(2.0f);

	// red X
	float red[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glUniform4fv(glGetUniformLocation(App->program->axisProgram, "newColor"), 1, red);

	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.1f, 0.0f); glVertex3f(1.1f, -0.1f, 0.0f);
	glVertex3f(1.1f, 0.1f, 0.0f); glVertex3f(1.0f, -0.1f, 0.0f);
	glEnd();

	// green Y
	float green[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
	glUniform4fv(glGetUniformLocation(App->program->axisProgram, "newColor"), 1, green);

	glBegin(GL_LINES);
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.05f, 1.25f, 0.0f); glVertex3f(0.0f, 1.15f, 0.0f);
	glVertex3f(0.05f, 1.25f, 0.0f); glVertex3f(0.0f, 1.15f, 0.0f);
	glVertex3f(0.0f, 1.15f, 0.0f); glVertex3f(0.0f, 1.05f, 0.0f);
	glEnd();

	// blue Z
	float blue[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
	glUniform4fv(glGetUniformLocation(App->program->axisProgram, "newColor"), 1, blue);

	glBegin(GL_LINES);
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.05f, 0.1f, 1.05f); glVertex3f(0.05f, 0.1f, 1.05f);
	glVertex3f(0.05f, 0.1f, 1.05f); glVertex3f(-0.05f, -0.1f, 1.05f);
	glVertex3f(-0.05f, -0.1f, 1.05f); glVertex3f(0.05f, -0.1f, 1.05f);
	glEnd();

	glLineWidth(1.0f);
}

bool ModuleCamera::CleanUp()
{
	return true;
}