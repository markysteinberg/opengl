#include <glad/glad.h>

#include <assimp/Importer.hpp> 
#include <assimp/scene.h> 
#include <assimp/postprocess.h>

#include "model.h"
#include "texture.h"  
#include "log.h"

void Model::setup() {
    for (auto& mesh : meshes) {
        mesh.setup();
    }
    LOG(INFO, "Model setup complete: meshes=", meshes.size(), " materials=", materials.size());
}

void Model::draw(GLuint hasTexLoc, GLuint diffuseLoc) {
    for (auto& mesh : meshes) {
        const Material& mat = materials[mesh.materialIndex];
        bool hasTex = (mat.diffuseTex != 0);

        glUniform1i(hasTexLoc, hasTex); 

        if (mat.diffuseTex != 0) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, mat.diffuseTex);
        } else { 
            glUniform3fv(diffuseLoc, 1, &mat.diffuse[0]);
        }

        mesh.draw();
    }
}

Model load_model(const char* path) {
    LOG(INFO, "Loading model: ", path);
    
    Assimp::Importer importer;
    
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);

    if (!scene || !scene->mRootNode) {
        LOG(ERROR, "Assimp failed to load: '", path, "': ", importer.GetErrorString());
        return {};
    } 
    LOG(INFO, "Scene loaded: meshes=", scene->mNumMeshes, " materials=", scene->mNumMaterials, " textures=", scene->mNumTextures);

    Model model;
    model.materials.resize(scene->mNumMaterials);

    // Texture 
    for(uint32_t i = 0; i < scene->mNumMaterials; i++) {
        aiMaterial* mat = scene->mMaterials[i];

        aiColor3D color(1, 1, 1);
        mat->Get(AI_MATKEY_COLOR_DIFFUSE, color);
        model.materials[i].diffuse = glm::vec3(color.r, color.g, color.b);   
        
        LOG(INFO, "Material[", i, "] diffuse=(", color.r, ", ", color.g, ", ", color.b, ")", " diffuseTexCount=", mat->GetTextureCount(aiTextureType_DIFFUSE));

        aiString texPath;
        std::string directory = std::string(path);
        directory = directory.substr(0, directory.find_last_of("/\\"));

        if (mat->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
            mat->GetTexture(aiTextureType_DIFFUSE, 0, &texPath);

            std::string fullPath = directory + "/" + std::string(texPath.C_Str());
                
            LOG(INFO, "Material[", i, "] texture path: ", fullPath);
    
            model.materials[i].diffuseTex = load_texture(fullPath.c_str());
        }
    }

    // Mesh
    for (uint32_t k = 0; k < scene->mNumMeshes; k++) {
        aiMesh* m = scene->mMeshes[k]; 

        Mesh mesh;
        mesh.materialIndex = m->mMaterialIndex; 

        // Vertices
        for (uint32_t i = 0; i < m->mNumVertices; i++) {
            Vertex v{};

            v.position = glm::vec3(m->mVertices[i].x, m->mVertices[i].y, m->mVertices[i].z);

            if (m->mTextureCoords[0]) {
                v.texCoord = glm::vec2(m->mTextureCoords[0][i].x, m->mTextureCoords[0][i].y);
            } else {
                v.texCoord = glm::vec2(0.0f, 0.0f);
            }

            mesh.vertices.push_back(v);
        }

        // Faces  
        for (uint32_t i = 0; i < m->mNumFaces; i++) {
            aiFace face = m->mFaces[i];
            for (uint32_t j = 0; j < face.mNumIndices; j++) {
                mesh.indices.push_back(face.mIndices[j]);
            }
        }  

        LOG(INFO, "Parsed mesh[", k, "]: vertices=", mesh.vertices.size(), " indices=", mesh.indices.size(), " materialIndex=", mesh.materialIndex);
        
        model.meshes.push_back(mesh);    
    }

    if (!model.meshes.empty()) {
        model.valid = true;
    }

    return model;
}


