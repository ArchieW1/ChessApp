#include "RenderableBase.h"

RenderableBase::RenderableBase(std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<SDL_Texture> texture,
                               Vector2D sourceWidthHeight, Vector2D destinationXY, Vector2D destinationWidthHeight) :
                            _renderer{ std::move(renderer) }, _texture{ std::move(texture) },
                            _sourceRect{ 0, 0, sourceWidthHeight.x, sourceWidthHeight.y },
                            _destinationRect{ destinationXY.x, destinationXY.y, destinationWidthHeight.x, destinationWidthHeight.y } {}

RenderableBase::RenderableBase(std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<SDL_Texture> texture,
                         Vector2D sourceWidthHeight) :
                           _renderer{ std::move(renderer) }, _texture{ std::move(texture) },
                           _sourceRect{ 0, 0, sourceWidthHeight.x, sourceWidthHeight.y } {}

void RenderableBase::SetDestinationRect(Vector2D destinationRectXY)
{
  _destinationRect.x = destinationRectXY.x;
  _destinationRect.y = destinationRectXY.y;
}

Vector2D RenderableBase::GetDestinationRect()
{
  return { _destinationRect.x, _destinationRect.y };
}

void RenderableBase::Render()
{
  SDL_RenderCopy(_renderer.get(), _texture.get(), &_sourceRect, &_destinationRect);
}