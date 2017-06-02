#pragma once

#include <map>
#include <string>

#include "shader.h"
#include "texture.h"

class ResourceManager
{
public:

    // Resource Storage.
    static std::map<std::string, Shader> Shaders;
    static std::map<std::string, Texture2D> Textures;

    // Loads and generates a shader program from files.
    static Shader LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile,const GLchar *gShaderFile, std::string name);

    // Retrieves a stored shader.
    static Shader& GetShader(std::string name);

    // Loads and generates a texture from file.
    static Texture2D LoadTexture(const GLchar *file, GLboolean alpha, std::string name);

    // Retrives a stored texture.
    static Texture2D& GetTexture(std::string name);

    // Deallocates all resources.
    static void Clear();

private:    

    ResourceManager() {}
    static Shader loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile,const GLchar *gShaderFile = nullptr);
    static Texture2D loadTextureFromFile(const GLchar *file, GLboolean alpha);
};

#include "resource_manager.cpp"
