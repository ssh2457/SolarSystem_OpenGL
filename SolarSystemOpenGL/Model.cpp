#include "include/Model.h"

Model::~Model() {
	ClearModel();
}

void Model::LoadModel(const std::string& fileName) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(fileName,
											aiProcess_Triangulate |
											aiProcess_FlipUVs |
											aiProcess_GenSmoothNormals |
											aiProcess_JoinIdenticalVertices);

	if (!scene) {
		SPDLOG_ERROR("Model {} failed to load: {}", fileName.c_str(), importer.GetErrorString());
		return;
	}

	LoadMode(scene->mRootNode, scene);
	LoadMaterials(scene);
}

void Model::RenderModel() {
	for (size_t i = 0; i < mMeshList.size(); ++i) {
		unsigned int materialIdx = mMeshToTex[i];

		if (materialIdx < mTextureList.size() && mTextureList[materialIdx]) {
			mTextureList[materialIdx]->UseTexture();
		}
		mMeshList[i]->RenderMesh();
	}
}

void Model::ClearModel() {
	for (size_t i = 0; i < mMeshList.size(); ++i) {
		if (mMeshList[i]) {
			mMeshList[i] = nullptr;
		}
	}

	for (size_t i = 0; i < mTextureList.size(); ++i) {
		if (mTextureList[i]) { 
			mTextureList[i] = nullptr;
		}
	}
}

void Model::LoadMode(aiNode* node, const aiScene* scene) {
	for (size_t i = 0; i < node->mNumMeshes; ++i) {
		LoadMesh(scene->mMeshes[node->mMeshes[i]], scene);
	}

	for (size_t i = 0; i < node->mNumChildren; ++i) {
		LoadMode(node->mChildren[i], scene);
	}
}

void Model::LoadMesh(aiMesh* mesh, const aiScene* scene) {
	std::vector<GLfloat> vertices;
	vertices.reserve(8 * mesh->mNumVertices);

	std::vector<unsigned int> indices;

	for (size_t i = 0; i < mesh->mNumVertices; ++i) {
		// Input vertex position (x, y, z)
		vertices.push_back(mesh->mVertices[i].x);
		vertices.push_back(mesh->mVertices[i].y);
		vertices.push_back(mesh->mVertices[i].z);

		// Input texture position (UV position)
		if (mesh->mTextureCoords[0]) {
			vertices.push_back(mesh->mTextureCoords[0][i].x);
			vertices.push_back(mesh->mTextureCoords[0][i].y);
		}
		else {
			vertices.push_back(0.f);
			vertices.push_back(0.f);
		}

		// Input normal vector (nx, ny, nz)
		vertices.push_back(-mesh->mNormals[i].x);
		vertices.push_back(-mesh->mNormals[i].y);
		vertices.push_back(-mesh->mNormals[i].z);
	}

	for (size_t i = 0; i < mesh->mNumFaces; ++i) {
		aiFace face = mesh->mFaces[i];
		for (size_t j = 0; j < face.mNumIndices; ++j) {
			indices.push_back(face.mIndices[j]);
		}
	}

	std::unique_ptr<Mesh> newMesh = std::make_unique<Mesh>();
	newMesh->CreateMesh(&vertices[0], &indices[0], vertices.size(), indices.size());
	mMeshList.push_back(std::move(newMesh));

	mMeshToTex.push_back(mesh->mMaterialIndex);
}

void Model::LoadMaterials(const aiScene* scene) {
	mTextureList.resize(scene->mNumMaterials);
	for (size_t i = 0; i < scene->mNumMaterials; ++i) {
		aiMaterial* material = scene->mMaterials[i];
		mTextureList[i] = nullptr;

		if (material->GetTextureCount(aiTextureType_DIFFUSE)) {
			aiString path;
			if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) {
				int idx = std::string(path.data).rfind("\\");
				std::string fileName = std::string(path.data).substr(idx + 1);
				std::string texPath = std::string("../../Textures/") + fileName;

				mTextureList[i] = std::move(std::make_unique<Texture>(texPath.c_str()));


				size_t pngIdx = texPath.find(".png");
				if (pngIdx != std::string::npos) {
					if (!mTextureList[i]->LoadTextureA()) {
						SPDLOG_ERROR("Failed to load texture at {}", texPath.c_str());
						mTextureList[i] = nullptr;
					}
				}
				else {
					if (!mTextureList[i]->LoadTexture()) {
						SPDLOG_ERROR("Failed to load texture at {}", texPath.c_str());
						mTextureList[i] = nullptr;
					}
				}
			}
		}

		if (!mTextureList[i]) {
			mTextureList[i] = std::move(std::make_unique<Texture>("../../Textures/plain.png"));
			mTextureList[i]->LoadTextureA();
		}
	}
}