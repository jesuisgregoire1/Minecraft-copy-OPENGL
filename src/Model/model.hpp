#ifndef __MODEL_H__
#define __MODEL_H__
#include <vector>
#include <string>
#include "../Shaders/shaders.hpp"
#include "../Mesh/mesh.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
namespace ModelNamespace{
    class Model{
        public:
            Model(const char* path){
                loadModel(path);
            }
            void Draw(ShaderNamespace::Shader &shader);
        private:
            std::vector<MeshNamespace::Texture> textures_loaded; 
            // model data
            std::vector<MeshNamespace::Mesh> meshes;
            std::string directory;
            void loadModel(std::string path);
            void processNode(aiNode* node, const aiScene* scene);
            MeshNamespace::Mesh processMesh(aiMesh* mesh, const aiScene* scene);
            std::vector<MeshNamespace::Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
    };  
}
#endif