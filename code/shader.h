#pragma once

#include <string>

#include "../third_party/SDL2/include/SDL_opengl.h"

typedef char GLchar;

namespace glm
{
    class vec2;
    class vec3;
    class vec4;
    class mat4;
}

class Shader
{
public:
    GLuint ID;

    Shader() {};

    Shader & Use();

    void Compile(const GLchar *vertexSource, const GLchar *fragmentSource, const GLchar *geometrySource = 0);

    void SetFloat   (const GLchar* name, GLfloat value, GLboolean useShader = false);
    void SetInteger (const GLchar* name, GLint value, GLboolean useShader = false);
    void SetVector2f(const GLchar* name, GLfloat x, GLfloat y, GLboolean useShader = false);
    void SetVector2f(const GLchar* name, const glm::vec2 &value, GLboolean useShader = false);
    void SetVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
    void SetVector3f(const GLchar* name, const glm::vec3 &value, GLboolean useShader = false);
    void SetVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
    void SetVector4f(const GLchar* name, const glm::vec4 &value, GLboolean useShader = false);
    void SetMatrix3 (const GLchar* name, const glm::mat4 &matrix, GLboolean useShader = false);

private:

    void checkCompileErrors(GLuint object, const std::string &type);
};

#include "shader.cpp"
