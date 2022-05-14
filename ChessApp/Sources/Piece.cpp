#include "Piece.h"

#include "TextureLoader.h"

Piece::Piece()
  : ElementBase(nullptr, nullptr,
    Vector2D(20, 20), Vector2D(0, 0), Vector2D(80, 80)) {}

Piece::Piece(Vector2D destinationXY)
  : ElementBase(nullptr, nullptr,
    Vector2D(20, 20), destinationXY, Vector2D(80, 80)) {}

Piece::Piece(const std::shared_ptr<SDL_Renderer>& renderer, const std::string& pngPath, Vector2D destinationXY)
  : ElementBase(renderer, LoadTexture(renderer, pngPath),
    Vector2D(20, 20), destinationXY, Vector2D(80, 80)), _isEmpty(false) {}

void Piece::SetDestinationRect(Vector2D destinationRectXY)
{
  _destinationRect.x = destinationRectXY.x;
  _destinationRect.y = destinationRectXY.y;
}

Vector2D Piece::GetDestinationRect()
{
  return {_destinationRect.x, _destinationRect.y};
}

bool Piece::GetIsEmpty() const
{
  return _isEmpty;
}

void Piece::SetIsEmpty(bool isEmpty)
{
  _isEmpty = isEmpty;
}
