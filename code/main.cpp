#include <stdio.h>

#include "../third_party/SDL2/include/SDL.h"
#include "../third_party/SDL2/include/SDL_opengl.h"

#include "gl_init.h"
#include "game.h"
#include "shader.h"
#include "texture.h"
#include "resource_manager.h"

typedef int32_t b32;

typedef int32_t s32;
typedef uint32_t u32;

typedef float r32;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

static inline r32 GetElapsedSeconds(u32 Start, u32 End)
{
    u32 TicksElapsed = End - Start;
    r32 Seconds = (r32)TicksElapsed / 1000.0f;
    return Seconds;
}

Game Breakout(SCREEN_WIDTH, SCREEN_HEIGHT);

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
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          WindowFlags);
    if (!Window)
    {
        printf("Unable to Window: %s\n", SDL_GetError());
        return 1;
    }
    
    SDL_GLContext GLContext = SDL_GL_CreateContext(Window);

    assert(InitGL());

    Breakout.Init();

    r32 Delta = 0;
    u32 LastFrame = 0;

    b32 Running = true;
    while (Running)
    {
        // Calculate the frame delta time (in seconds).
        u32 CurrentFrame = SDL_GetTicks();
        Delta = GetElapsedSeconds(LastFrame, CurrentFrame);
        LastFrame = CurrentFrame;

        // Grab the input.
        SDL_Event Event;
        while (SDL_PollEvent(&Event))
        {
            if (Event.type == SDL_QUIT)
            {
                Running = false;
            }
        }

        Breakout.ProcessInput(Delta);
        Breakout.Update(Delta);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        Breakout.Render();
        SDL_GL_SwapWindow(Window);
    }

    ResourceManager::Clear();

    SDL_GL_DeleteContext(GLContext);
    SDL_DestroyWindow(Window);
    SDL_GL_UnloadLibrary();
    SDL_Quit();

    return 0;
}
