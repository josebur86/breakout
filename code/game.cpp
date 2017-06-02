#include "sprite_renderer.h"
#include "resource_manager.h"

Game::Game(GLuint Width, GLuint Height)
: Width(Width),
  Height(Height)
{
}

Game::~Game()
{
}

SpriteRenderer *Renderer = 0;

void Game::Init()
{
    // Load the shaders
    ResourceManager::LoadShader("data/sprite.vert", "data/sprite.frag", nullptr, "sprite");

    // Configure the shader
    glm::mat4 projection = glm::ortho(0.0f, (float)this->Width, 
                                       (float)this->Height, 0.0f,
                                       -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

    // Set Render specific controls.
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

    // Load Textures
    ResourceManager::LoadTexture("data/awesomeface.png", GL_TRUE, "face");
}

void Game::ProcessInput(GLfloat dt)
{
}

void Game::Update(GLfloat dt)
{
}

void Game::Render()
{
    Renderer->DrawSprite(ResourceManager::GetTexture("face"),
                         glm::vec2(200, 200),
                         glm::vec2(300, 400),
                         45.0f, glm::vec3(0.0f, 1.0f, 0.0));
}

