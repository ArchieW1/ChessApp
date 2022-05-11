#include "Game.h"

#include <iostream>
#include <stdexcept>

// TODO: Find chess piece assets that are 1 png per piece
// TODO: Add board Entity
// TODO: Add piece Entities
// TODO: Add mouse controller
// TODO: Have mouse controller make pieces draggable and place able

SDL_Renderer* Game::Renderer = nullptr;
SDL_Event Game::Event;
Manager Game::Manager;

auto& board(Game::Manager.AddEntity());

Game::Game(const char* title, int width, int height, int xPosition, int yPosition)
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    SDL_GetError();
    throw std::runtime_error("SDL failed to initialise");
  }
    
  _window = SDL_CreateWindow(title, xPosition, yPosition, width, height, SDL_WINDOW_SHOWN);
  if (!_window)
  {
    SDL_GetError();
    throw std::runtime_error("Window failed to create");
  }

  Renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!Renderer)
  {
    SDL_GetError();
    throw std::runtime_error("Renderer failed to create");
  }

  SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
}

Game::~Game()
{
  SDL_DestroyWindow(_window);
  SDL_DestroyRenderer(Renderer);
  SDL_Quit();
}

void Game::HandleEvents()
{
  
  SDL_PollEvent(&Event);
  switch (Event.type)
  {
  case SDL_QUIT:
    _isRunning = false;
    break;

  default:
    break;
  }
}

void Game::Update()
{
  Manager.Update();
}

void Game::Render()
{
  SDL_RenderClear(Renderer);
  SDL_RenderPresent(Renderer);
}

