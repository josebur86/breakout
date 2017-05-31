#pragma once

#include "../third_party/SDL2/include/SDL_opengl.h"

class Texture2D
{
public:
    GLuint ID;

    GLuint Width;
    GLuint Height;

    GLuint Internal_Format;
    GLuint Image_Format;

    GLuint Wrap_S;
    GLuint Wrap_T;
    GLuint Filter_Min;
    GLuint Filter_Max;

    Texture2D();
    void Generate(GLuint width, GLuint height, unsigned char *data);
    void Bind() const;
};

#include "texture.cpp"
