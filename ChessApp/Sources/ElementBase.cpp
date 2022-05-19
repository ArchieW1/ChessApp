#include "ElementBase.h"

ElementBase::ElementBase(std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<SDL_Texture> texture,
                          Vector2D sourceWidthHeight, Vector2D destinationXY, Vector2D destinationWidthHeight) :
                            _renderer{ std::move(renderer) }, _texture{ std::move(texture) },
                            _sourceRect{ 0, 0, sourceWidthHeight.x, sourceWidthHeight.y },
                            _destinationRect{ destinationXY.x, destinationXY.y, destinationWidthHeight.x, destinationWidthHeight.y } {}

ElementBase::ElementBase(std::shared_ptr<SDL_Renderer> renderer, std::shared_ptr<SDL_Texture> texture,
                         Vector2D sourceWidthHeight) :
                           _renderer{ std::move(renderer) }, _texture{ std::move(texture) },
                           _sourceRect{ 0, 0, sourceWidthHeight.x, sourceWidthHeight.y } {}

void ElementBase::Render()
{
  SDL_RenderCopy(_renderer.get(), _texture.get(), &_sourceRect, &_destinationRect);
}