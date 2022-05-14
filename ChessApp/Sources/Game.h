#pragma once

#include <memory>

#include "SDL.h"

#include "Board.h"

class Game
{
public:
  Game();
  ~Game();
  void MainLoop();

private:
  std::shared_ptr<Board> _board;
  std::shared_ptr<SDL_Renderer> _renderer;
  std::shared_ptr<SDL_Window> _window;
  bool _isRunning = true;
};

