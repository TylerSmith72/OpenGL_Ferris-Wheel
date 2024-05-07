#ifndef MODEL_H
#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <mesh.h>
#include <shader_s.h>

#include <string>
#include <vector>

class Model {
public:
    Model(char *path){
        loadModel(path);
    }

    void Draw(Shader &shader){
        for(unsigned int i = 0; i < meshes.size(); i++){
            meshes[i].Draw(shader);
        }
    }

private:
    vector<Mesh> meshes;
    string directory;

    void loadModel(string path){
        Assimp::Importer import;
        const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

        // Check scene is not NULL or incomplete
        if(!scene || scene -> mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene -> mRootNode){
            cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
            return;
        }

        // Process Root Node
        directory = path.substr(0, path.find_last_of('/'));
        processNode(scene -> mRootNode, scene);
    }

    void processNode(aiNode *node, const aiScene *scene){
        // Process all the Node's Meshes
        for(unsigned int i = 0; i < node -> mNumMeshes; i++){
            aiMesh *mesh = scene -> mMeshes[node -> mMeshes[i]];
            meshes.push_back(processMesh(mesh, scene));
        }

        // Process all the Node's Children's Meshes
        for(unsigned int i = 0; i < node -> mNumChildren; i++){
            processNode(node -> mChildren[i], scene);
        }
    }

    Mesh processMesh(aiMesh *mesh, const aiScene *scene){
        // CONTINUE //
    }

    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
};

#endif