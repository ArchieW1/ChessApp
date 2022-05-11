#include <memory>

#include "Game.h"

#undef main

int main(int argc, const char* argv[])
{
  auto game = std::make_unique<Game>("Chess", 800, 800);

  while (game->GetIsRunning())
  {
    game->HandleEvents();
    game->Update();
    game->Render();
  }

  return 0;
}
