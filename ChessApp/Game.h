#pragma once

#include "SDL.h"

#include "Components.h"

class Game
{
public:
  Game(const char* title, int width, int height, int xPosition = SDL_WINDOWPOS_CENTERED,
                                                 int yPosition = SDL_WINDOWPOS_CENTERED);

  ~Game();

  bool GetIsRunning() const
  {
    return _isRunning;
  }

  static SDL_Renderer* Renderer;
  static SDL_Event Event;
  static Manager Manager;

  void HandleEvents();
  void Update();
  void Render();

private:
  bool _isRunning = true;
  SDL_Window* _window;
  
};

