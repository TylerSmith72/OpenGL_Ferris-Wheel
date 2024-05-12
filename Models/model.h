#ifndef MODEL_H
#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stb_image.h>

#include <mesh.h>
#include <shader_s.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

class Model {
public:
    vector<Mesh> meshes;
    vector<Texture> textures_loaded;
    string directory;

    glm::vec3 position;
    glm::vec3 rotation;

    Model(string const &path){
        loadModel(path);
    }

    void Draw(Shader &shader){
        for(unsigned int i = 0; i < meshes.size(); i++){
            meshes[i].Draw(shader);
        }
    }

    void setPosition(const glm::vec3& newPosition) {
        position = newPosition;
    }

    glm::vec3 getPosition() const {
        return position;
    }

    void setRotation(const glm::vec3& newRotation) {
        rotation = newRotation;
    }

    glm::vec3 getRotation() const {
        return rotation;
    }

    void rotate(const glm::vec3& deltaRotation) {
        rotation += deltaRotation;
    }

private:
    void loadModel(string const &path){
        Assimp::Importer import;
        //const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
        const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

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
        vector<Vertex> vertices;
        vector<unsigned int> indices;
        vector<Texture> textures;

        for(unsigned int i = 0; i < mesh -> mNumVertices; i++){
            Vertex vertex;

            // Positions
            glm::vec3 vector;
            vector.x = mesh -> mVertices[i].x;
            vector.y = mesh -> mVertices[i].y;
            vector.z = mesh -> mVertices[i].z;
            vertex.Position = vector;

            // Normals
            if (mesh->HasNormals())
            {
                vector.x = mesh->mNormals[i].x;
                vector.y = mesh->mNormals[i].y;
                vector.z = mesh->mNormals[i].z;
                vertex.Normal = vector;
            }

            // Textures
            if(mesh->mTextureCoords[0]) // Does Mesh have Texture Coords?
            {
                glm::vec2 vec;
                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.TexCoords = vec;
            }
            else {
                vertex.TexCoords = glm::vec2(0.0f, 0.0f);
            }

            vertices.push_back(vertex);
        }

        // Process Indices
        for(unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for(unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }

        // Process Material
        if(mesh -> mMaterialIndex >= 0){
            aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

            vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "diffuse");
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

            vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "specular");
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        }

        return Mesh(vertices, indices, textures);
    }

    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName){
        vector<Texture> textures;

        for(unsigned int i = 0; i < mat ->GetTextureCount(type); i++){
            aiString str;
            mat ->GetTexture(type, i, &str);

            bool skip = false;
            for(unsigned int j = 0; j < textures_loaded.size(); j++){
                if(strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0){
                    textures.push_back(textures_loaded[j]);
                    skip = true;
                    break;
                }
            }

            if(!skip){
                Texture texture;
                texture.id = TextureFromFile(str.C_Str(), directory);
                texture.type = typeName;
                texture.path = str.C_Str();

                textures.push_back(texture);
            }
        }

        return textures;
    }
};

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma){
    string filename = string(path);
    filename = directory + '/' + filename;

    // Generate Texture ID
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;

    // Load Image from File
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);

    // Check if Image Loaded Successfully
    if (data)
    {
        // Determine the format of the image based on the number of color components
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        // Wrapping
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Free Memory
        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

#endif