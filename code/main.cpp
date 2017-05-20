#include <stdio.h>

#include "../third_party/SDL2/include/SDL.h"
#include "../third_party/SDL2/include/SDL_opengl.h"

//
// OpenGL Function Pointers
//

typedef void gl_use_program(GLuint program);
gl_use_program *glUseProgram = 0;

typedef GLint gl_get_uniform_location(GLuint program, const GLchar *name);
gl_get_uniform_location *glGetUniformLocation;


typedef void gl_uniform_1f(GLint location, GLfloat v0);
gl_uniform_1f *glUniform1f;

#include "game.h"
#include "shader.h"

typedef int32_t b32;

typedef int32_t s32;
typedef uint32_t u32;

static void InitGL()
{
    glUseProgram = (gl_use_program *)SDL_GL_GetProcAddress("glUseProgram");
    glGetUniformLocation = (gl_get_uniform_location *)SDL_GL_GetProcAddress("glGetUniformLocation");
    glUniform1f = (gl_uniform_1f *)SDL_GL_GetProcAddress("glUniform1f");
}

int main(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    if(SDL_GL_LoadLibrary(0) == -1)
    {
        printf("Unable to load OpenGL library: %s\n", SDL_GetError());
        return 1;

    }

    u32 WindowFlags = SDL_WINDOW_OPENGL;
    SDL_Window *Window = SDL_CreateWindow("Breakout", 
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          800, 600,
                                          WindowFlags);
    if (!Window)
    {
        printf("Unable to Window: %s\n", SDL_GetError());
        return 1;
    }
    
    SDL_GLContext GLContext = SDL_GL_CreateContext(Window);

    InitGL();

    b32 Running = true;
    while (Running)
    {
        SDL_Event Event;
        while (SDL_PollEvent(&Event))
        {
            if (Event.type == SDL_QUIT)
            {
                Running = false;
            }
        }
    }

    SDL_GL_DeleteContext(GLContext);
    SDL_DestroyWindow(Window);
    SDL_GL_UnloadLibrary();
    SDL_Quit();

    return 0;
}
