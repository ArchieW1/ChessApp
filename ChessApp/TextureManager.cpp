#include "TextureManager.h"

#include "SDL_image.h"

SDL_Texture* TextureManager::LoadTexture(const char* filePath)
{
  IMG_Init(IMG_INIT_PNG);
  SDL_Surface* tempSurface = IMG_Load(filePath);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::Renderer, tempSurface);

  SDL_FreeSurface(tempSurface);

  return texture;
}

void TextureManager::Draw(SDL_Texture*texture, SDL_Rect src, SDL_Rect dest)
{
  SDL_RenderCopy(Game::Renderer, texture, &src, &dest);
}
