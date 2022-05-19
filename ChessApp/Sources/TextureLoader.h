#pragma once

#include <string>
#include <memory>

#include "SDL.h"

std::shared_ptr<SDL_Texture> LoadTexture(const std::shared_ptr<SDL_Renderer>& renderer, const std::string& pngPath);
