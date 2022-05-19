#include "Piece.h"

#include "TextureLoader.h"
#include "Board.h"

constexpr int PIECE_PNG_SIZE = 20;

Piece::Piece() :
  ElementBase(nullptr, nullptr,
              Vector2D(PIECE_PNG_SIZE, PIECE_PNG_SIZE), Vector2D(0, 0),
              Vector2D(BOARD_TILE_SIZE, BOARD_TILE_SIZE)) {}

Piece::Piece(Vector2D destinationXY) :
  ElementBase(nullptr, nullptr,
              Vector2D(PIECE_PNG_SIZE, PIECE_PNG_SIZE), destinationXY, 
              Vector2D(BOARD_TILE_SIZE, BOARD_TILE_SIZE)) {}

Piece::Piece(const std::shared_ptr<SDL_Renderer>& renderer, const std::string& pngPath, Vector2D destinationXY) :
  ElementBase(renderer, LoadTexture(renderer, pngPath),
              Vector2D(PIECE_PNG_SIZE, PIECE_PNG_SIZE), destinationXY,
              Vector2D(BOARD_TILE_SIZE, BOARD_TILE_SIZE)), _isEmpty(false) {}

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
