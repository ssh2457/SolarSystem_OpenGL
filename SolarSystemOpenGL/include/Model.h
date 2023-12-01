#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <string>

#include "Mesh.h"
#include "Texture.h"

class Model {
public:
	Model() = default;
	virtual ~Model();

	void LoadModel(const std::string& fileName);
	void RenderModel();
	void ClearModel();

private:
	std::vector<std::unique_ptr<Mesh>> mMeshList;
	std::vector<std::unique_ptr<Texture>> mTextureList;
	std::vector<unsigned int> mMeshToTex;

	void LoadMode(aiNode* node, const aiScene* scene);
	void LoadMesh(aiMesh* mesh, const aiScene* scene);
	void LoadMaterials(const aiScene* scene);
};