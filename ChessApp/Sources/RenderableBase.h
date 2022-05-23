#pragma once

#include <memory>

#include "SDL.h"

#include "Vector2d.h"

class RenderableBase
{
public:
  explicit RenderableBase(std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<SDL_Texture> texture,
                       Vector2D sourceWidthHeight, Vector2D destinationXY, Vector2D destinationWidthHeight);

  explicit RenderableBase(std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<SDL_Texture> texture,
                       Vector2D sourceWidthHeight);

  virtual ~RenderableBase() = default;

  Vector2D GetDestinationRect();
  void SetDestinationRect(Vector2D destinationRectXY);

  virtual void Render();

protected:
  std::shared_ptr<SDL_Renderer> _renderer;
  std::shared_ptr<SDL_Texture> _texture;
  SDL_Rect _sourceRect = {0, 0, 0, 0};
  SDL_Rect _destinationRect = { 0, 0, 0, 0 };
};

