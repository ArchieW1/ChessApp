#pragma once

#include <SDL.h>

struct SdlDeleter
{
  void operator()(SDL_Window* window) const;

  void operator()(SDL_Renderer* renderer) const;

  void operator()(SDL_Texture* texture) const;

  void operator()(SDL_Surface* surface) const;
};
