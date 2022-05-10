#pragma once

#include "SDL.h"

class Game
{
public:
  Game(const char* title, int xPosition, int yPosition, int width, int height);

  ~Game();

  inline bool GetIsRunning() const
  {
    return _isRunning;
  }

  void HandleEvents();
  void Update();
  void Render();
  void Clean();

private:
  bool _isRunning = true;
  SDL_Window* _window;
  SDL_Renderer* _renderer;
};

