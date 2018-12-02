#include "Application.h"

#include "ModuleScene.h"
#include "ModuleWindow.h"
#include "ModuleProgram.h"
#include "ModuleCamera.h"

#include "GL\glew.h"
#include "SDL.h"

#include "MathGeoLib\include\Geometry\Frustum.h"
#include "MathGeoLib\include\Math\MathConstants.h"
#include "MathGeoLib\include\Math\float3.h"
#include "MathGeoLib\include\Math\float4.h"

ModuleScene::ModuleScene()
{
}

ModuleScene::~ModuleScene()
{
}

bool ModuleScene::Init()
{
//	texture = App->textures->Load("./Textures/Lenna.png");

	float vertex_buffer_data[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	-1.0f,  1.0f, 0.0f,

	1.0f, -1.0f, 0.0f,
	1.0f,  1.0f, 0.0f,
	-1.0f, 1.0f, 0.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	0.0f, 1.0f,

	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,
	};

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return vbo;
}

update_status ModuleScene::Update()
{
	glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(
            0,                  // attribute 0
            3,                  // number of componentes (3 floats)
            GL_FLOAT,           // data type
            GL_FALSE,           // should be normalized?
            0,                  // stride
            (void*)0            // array buffer offset
	);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)(sizeof(float) * 3 * 6) // buffer offset
	);

	glUseProgram(App->program->program);

	math::float4x4 model(math::float4x4::identity);

	glUniformMatrix4fv(glGetUniformLocation(App->program->program, "model"), 1, GL_TRUE, &model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(App->program->program, "view"), 1, GL_TRUE, &App->camera->LookAt(App->camera->cameraPosition, App->camera->cameraFront, App->camera->cameraUp)[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(App->program->program, "proj"), 1, GL_TRUE, &App->camera->frustum.ProjectionMatrix()[0][0]);

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, texture);
	//glUniform1i(glGetUniformLocation(App->program->program, "texture0"), 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);

	return UPDATE_CONTINUE;
}
/*
float4x4 ModuleScene::Transform(float3 eye, float3 target)
{
	float4x4 resultMatrix;

	float3 f(target - eye);
	f.Normalize();
	float3 s(f.Cross(up));
	s.Normalize();
	float3 u(s.Cross(f));

	viewMatrix[0][0] = s.x; viewMatrix[0][1] = s.y; viewMatrix[0][2] = s.z; viewMatrix[3][0] = 0;
	viewMatrix[1][0] = u.x; viewMatrix[1][1] = u.y; viewMatrix[1][2] = u.z; viewMatrix[3][1] = 0;
	viewMatrix[2][0] = -f.x; viewMatrix[2][1] = -f.y; viewMatrix[2][2] = -f.z; viewMatrix[3][2] = 0;
	viewMatrix[0][3] = -s.Dot(eye); viewMatrix[1][3] = -u.Dot(eye); viewMatrix[2][3] = f.Dot(eye); viewMatrix[3][3] = 1;

	Frustum frustum;
	float aspect = SCREEN_WIDTH / SCREEN_HEIGHT;
	frustum.type = FrustumType::PerspectiveFrustum;
	frustum.pos = float3::zero;
	frustum.front = -float3::unitZ;
	frustum.up = float3::unitY;
	frustum.nearPlaneDistance = 0.1f;
	frustum.farPlaneDistance = 100.0f;
	frustum.verticalFov = math::pi / 4.0f;
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f)) * aspect;
	math::float4x4 proj = frustum.ProjectionMatrix();

	this->viewMatrix = viewMatrix;
	this->projectionMatrix = proj;

	resultMatrix = proj * viewMatrix;


	return resultMatrix;
}
*/
bool ModuleScene::CleanUp()
{
    if(vbo != 0)
    {
        glDeleteBuffers(1, &vbo);
    }

	return true;
}