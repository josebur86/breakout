#pragma once

#include "../third_party/SDL2/include/SDL_opengl.h"

enum GameState
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN,
};

class Game
{
public:
    GameState State;
    GLboolean Keys[1024];
    GLuint    Width;
    GLuint    Height;

    Game(GLuint Width, GLuint Height);
    ~Game();

    void Init();

    void ProcessInput(GLfloat dt);
    void Update(GLfloat dt);
    void Render();
};

#include "game.cpp"
