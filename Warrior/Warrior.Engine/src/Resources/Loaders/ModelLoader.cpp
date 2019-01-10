#include "Engine/Resources/Loaders/ModelLoader.h"
#include "Engine/Resources/ResourceManager.h"
#include "Engine/Logging/Logging.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <filesystem>

namespace WarriorEngine::Resources::Loaders
{
namespace detail
{
class ModelLoaderImpl
{
public:
    ResourceManager* manager;

    explicit ModelLoaderImpl(ResourceManager* manager);

    void processNode(const std::string& directory,
                     Graphics::Model* model,
                     aiNode* node,
                     const aiScene* scene) const;

    std::unique_ptr<Graphics::Mesh> processMesh(const std::string& directory,
                                                aiMesh* mesh,
                                                const aiScene* scene) const;

    void processMaterialTextures(
        std::vector<std::pair<Resource<Graphics::OpenGL::Texture>, std::string>>& textures,
        const std::string& directory,
        aiMaterial* mat,
        aiTextureType type,
        const std::string& typeName) const;
};

ModelLoaderImpl::ModelLoaderImpl(ResourceManager* manager) : manager(manager) {}

void ModelLoaderImpl::processNode(const std::string& directory,
                                  Graphics::Model* model,
                                  aiNode* node,
                                  const aiScene* scene) const
{
    for (auto i = 0u; i < node->mNumMeshes; ++i)
    {
        const auto mesh = scene->mMeshes[node->mMeshes[i]];
        model->addMesh(processMesh(directory, mesh, scene));
    }

    for (auto i = 0u; i < node->mNumChildren; ++i)
        processNode(directory, model, node->mChildren[i], scene);
}

std::unique_ptr<Graphics::Mesh> ModelLoaderImpl::processMesh(const std::string& directory,
                                                             aiMesh* mesh,
                                                             const aiScene* scene) const
{
    std::vector<Graphics::Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<std::pair<Resource<Graphics::OpenGL::Texture>, std::string>> textures;

    vertices.reserve(mesh->mNumVertices);

    // vertices
    for (auto i = 0u; i < mesh->mNumVertices; ++i)
    {
        vertices.push_back({});
        auto& vertex = vertices.back();

        vertex.position.x = mesh->mVertices[i].x;
        vertex.position.y = mesh->mVertices[i].y;
        vertex.position.z = mesh->mVertices[i].z;

        // normals
        if (mesh->mNormals)
        {
            vertex.normal.x = mesh->mNormals[i].x;
            vertex.normal.y = mesh->mNormals[i].y;
            vertex.normal.z = mesh->mNormals[i].z;
        }

        // texture coordinates
        if (mesh->mTextureCoords[0])
        {
            vertex.texCoords.x = mesh->mTextureCoords[0][i].x;
            vertex.texCoords.y = mesh->mTextureCoords[0][i].y;
        }
        else
            vertex.texCoords = glm::vec2(0.0f, 0.0f);

        // tangent
        if (mesh->mTangents)
        {
            vertex.tangent.x = mesh->mTangents[i].x;
            vertex.tangent.y = mesh->mTangents[i].y;
            vertex.tangent.z = mesh->mTangents[i].z;
        }

        // bitangent
        if (mesh->mBitangents)
        {
            vertex.bitangent.x = mesh->mBitangents[i].x;
            vertex.bitangent.y = mesh->mBitangents[i].y;
            vertex.bitangent.z = mesh->mBitangents[i].z;
        }
    }

    auto indicesCount = 0u;

    for (auto i = 0u; i < mesh->mNumFaces; ++i)
    {
        const auto& face = mesh->mFaces[i];
        indicesCount += face.mNumIndices;
    }

    indices.reserve(indicesCount);

    // indices
    for (auto i = 0u; i < mesh->mNumFaces; ++i)
    {
        const auto& face = mesh->mFaces[i];

        for (unsigned int j = 0; j < face.mNumIndices; ++j)
            indices.push_back(face.mIndices[j]);
    }

    // materials
    const auto material = scene->mMaterials[mesh->mMaterialIndex];

    auto texturesCount = 0u;

    texturesCount += material->GetTextureCount(aiTextureType_DIFFUSE);
    texturesCount += material->GetTextureCount(aiTextureType_SPECULAR);
    texturesCount += material->GetTextureCount(aiTextureType_HEIGHT);
    texturesCount += material->GetTextureCount(aiTextureType_AMBIENT);

    textures.reserve(texturesCount);

    processMaterialTextures(textures, directory, material, aiTextureType_DIFFUSE, "texture_diffuse");
    processMaterialTextures(textures, directory, material, aiTextureType_SPECULAR, "texture_specular");
    processMaterialTextures(textures, directory, material, aiTextureType_HEIGHT, "texture_normal");
    processMaterialTextures(textures, directory, material, aiTextureType_AMBIENT, "texture_height");

    return std::make_unique<Graphics::Mesh>(std::move(vertices), std::move(indices), std::move(textures));
}

void ModelLoaderImpl::processMaterialTextures(
    std::vector<std::pair<Resource<Graphics::OpenGL::Texture>, std::string>>& textures,
    const std::string& directory,
    aiMaterial* mat,
    const aiTextureType type,
    const std::string& typeName) const
{
    for (auto i = 0u; i < mat->GetTextureCount(type); ++i)
    {
        aiString str;
        (void)mat->GetTexture(type, i, &str);

        const auto textureFile = std::filesystem::path(directory) / std::filesystem::path(str.C_Str());

        textures.emplace_back(manager->getTexture(textureFile.string()), typeName);
    }
}
}  // namespace detail

ModelLoader::ModelLoader(ResourceManager* manager)
{
    pImpl_ = std::make_unique<detail::ModelLoaderImpl>(manager);
}

std::unique_ptr<Graphics::Model> ModelLoader::fromFile(const std::string& file) const
{
    Assimp::Importer importer;

    const auto scene =
        importer.ReadFile(file, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        WE_ENGINE_ERROR(
            "Warrior.Engine.Resources.Loaders.ModelLoader error: error while trying to load model file: %s",
            importer.GetErrorString());
        return nullptr;
    }

    auto directory = std::filesystem::path(file).parent_path().string();
    const auto resourcePath = pImpl_->manager->getResourcesPath() + std::string("\\");  // todo

    const auto pos = directory.find(resourcePath);

    if (pos != std::string::npos)
        directory.erase(pos, resourcePath.size());

    auto model = std::make_unique<Graphics::Model>();

    pImpl_->processNode(directory, model.get(), scene->mRootNode, scene);

    return model;
}
}  // namespace WarriorEngine::Resources::Loaders
