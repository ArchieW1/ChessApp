#pragma once

#include <string>
#include <memory>

#include "SDL.h"
#include "SDL_image.h"

#include "SdlDeleter.h"

inline std::shared_ptr<SDL_Texture> LoadTexture(const std::shared_ptr<SDL_Renderer>& renderer, const std::string& pngPath)
{
  IMG_Init(IMG_INIT_PNG);
  std::shared_ptr<SDL_Surface> tempSurface = std::shared_ptr<SDL_Surface>(IMG_Load(pngPath.c_str()),
    SdlDeleter());
  return {SDL_CreateTextureFromSurface(renderer.get(), tempSurface.get()), SdlDeleter() };
}
