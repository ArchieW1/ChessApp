#include "Game.h"

#include <iostream>
#include <stdexcept>

Game::Game(const char* title, int xPosition, int yPosition, int width, int height)
{
  if (!SDL_Init(SDL_INIT_EVERYTHING))
  {
    throw std::runtime_error("SDL failed to initialise");
  }
    
  _window = SDL_CreateWindow(title, xPosition, yPosition, width, height, 0);
  if (!_window)
  {
    throw std::runtime_error("Window failed to create");
  }

  _renderer = SDL_CreateRenderer(_window, -1, 0);
  if (!_renderer)
  {
    throw std::runtime_error("Renderer failed to create");
  }
}

Game::~Game()
{
  SDL_DestroyWindow(_window);
  SDL_DestroyRenderer(_renderer);
  SDL_Quit();
}

void Game::HandleEvents()
{
}

void Game::Update()
{
}

void Game::Render()
{
}

void Game::Clean()
{
}
