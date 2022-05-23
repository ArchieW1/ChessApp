#include "Game.h"
#include "SdlDeleter.h"

Game::Game()
{
  SDL_Init(SDL_INIT_EVERYTHING);
  _window = std::shared_ptr<SDL_Window>(SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, 640, 640, SDL_WINDOW_SHOWN), SdlDeleter());
  _renderer = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(_window.get(), -1,
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC), SdlDeleter());
  SDL_SetRenderDrawColor(_renderer.get(), 255, 255, 255, 255);
  _board = std::make_shared<Board>(_renderer);
}

Game::~Game()
{
  SDL_Quit();
}

void Game::HandleEvents()
{
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
    case SDL_QUIT:
      SDL_Quit();
      _isRunning = false;
      break;

    case SDL_MOUSEBUTTONDOWN:
      _board->OnClick(event);
      break;

    case SDL_MOUSEMOTION:
      _board->OnMove(event);
      break;

    case SDL_MOUSEBUTTONUP:
      _board->OnRelease(event);
      break;

    default:
      break;
    }
  }
}

void Game::MainLoop()
{
  while (_isRunning)
  {
    HandleEvents();
  }
}
