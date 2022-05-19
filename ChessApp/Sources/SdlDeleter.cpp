#include "SdlDeleter.h"

void SdlDeleter::operator()(SDL_Window* window) const
{
  SDL_DestroyWindow(window);
}

void SdlDeleter::operator()(SDL_Renderer* renderer) const
{
  SDL_DestroyRenderer(renderer);
}

void SdlDeleter::operator()(SDL_Texture* texture) const
{
  SDL_DestroyTexture(texture);
}

void SdlDeleter::operator()(SDL_Surface* surface) const
{
  SDL_FreeSurface(surface);
}
