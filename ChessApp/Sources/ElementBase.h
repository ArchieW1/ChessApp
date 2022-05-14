#pragma once

#include <memory>

#include "SDL.h"

#include "Vector2d.h"

class ElementBase
{
public:
  explicit ElementBase(std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<SDL_Texture> texture,
                       Vector2D sourceWidthHeight, Vector2D destinationXY, Vector2D destinationWidthHeight)
    : _renderer{std::move(renderer)}, _texture{ std::move(texture) },
      _sourceRect{ 0, 0, sourceWidthHeight.x, sourceWidthHeight.y },
      _destinationRect { destinationXY.x, destinationXY.y, destinationWidthHeight.x, destinationWidthHeight.y } {}

  explicit ElementBase(std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<SDL_Texture> texture, 
    Vector2D sourceWidthHeight)
    : _renderer{ std::move(renderer) }, _texture{ std::move(texture) },
      _sourceRect{ 0, 0, sourceWidthHeight.x, sourceWidthHeight.y } {}

  virtual ~ElementBase() = default;

  virtual void Render()
  {
    SDL_RenderCopy(_renderer.get(), _texture.get(), &_sourceRect, &_destinationRect);
  }

protected:
  std::shared_ptr<SDL_Renderer> _renderer;
  std::shared_ptr<SDL_Texture> _texture;
  SDL_Rect _sourceRect = {0, 0, 0, 0};
  SDL_Rect _destinationRect = { 0, 0, 0, 0 };
};

