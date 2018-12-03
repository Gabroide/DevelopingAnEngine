#ifndef __ModuleModelLoader_h__
#define __ModuleModelLoader_h__

#include <vector>

#include "Module.h"
#include "Globals.h"

#include "GL/glew.h"

#include "MathGeoLib\include\MathGeoLib.h"

#include "Assimp\mesh.h"
#include "Assimp\material.h"

class ModuleModelLoader : public Module
{
public:
	ModuleModelLoader();
	~ModuleModelLoader();

	bool Init() override;
	bool CleanUp() override;

	void ChooseModelToRender(const int num);
	void ImportModel(const char* path);
	void CleanModel();

	void GenerateMeshData(const aiMesh* aiMesh);
	void GenerateMaterialData(const aiMaterial* aiMaterial);
	void ReplaceMaterial(const char* path);
	
public:
	int modelRendered = -1;

	math::float3 minPoint;
	math::float3 maxPoint;
	
public:
	struct Mesh
	{
		unsigned vbo = 0;
		unsigned ibo = 0;
		unsigned material = 0;
		unsigned numVertices = 0;
		unsigned numIndices = 0;
		const char* name = nullptr;
		aiVector3D translation;
		aiVector3D scaling;
		aiQuaternion rotation;
	};

	struct Material
	{
		unsigned texture0 = 0;
		unsigned width = 0;
		unsigned height = 0;
	};

public:
	std::vector<Mesh> meshes;
	std::vector<Material> materials;
};

#endif
