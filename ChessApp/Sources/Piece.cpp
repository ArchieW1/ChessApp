#include "Piece.h"

#include "TextureLoader.h"
#include "Board.h"

constexpr int PIECE_PNG_SIZE = 20;

Piece::Piece() :
               RenderableBase(nullptr, nullptr,
                           Vector2D(PIECE_PNG_SIZE, PIECE_PNG_SIZE), Vector2D(0, 0),
                           Vector2D(BOARD_TILE_SIZE, BOARD_TILE_SIZE)),
                           _isEmpty(true), _colour(NONE) {}

Piece::Piece(Vector2D destinationXY) :
               RenderableBase(nullptr, nullptr,
                           Vector2D(PIECE_PNG_SIZE, PIECE_PNG_SIZE), destinationXY, 
                           Vector2D(BOARD_TILE_SIZE, BOARD_TILE_SIZE)), _isEmpty(true),
                           _colour(NONE) {}

Piece::Piece(const std::shared_ptr<SDL_Renderer>& renderer, const std::string& pngPath, Vector2D destinationXY,
             PieceColour colour) :
               RenderableBase(renderer, LoadTexture(renderer, pngPath),
                           Vector2D(PIECE_PNG_SIZE, PIECE_PNG_SIZE), destinationXY,
                           Vector2D(BOARD_TILE_SIZE, BOARD_TILE_SIZE)), _isEmpty(false),
                           _colour(colour) {}

bool Piece::GetIsEmpty() const
{
  return _isEmpty;
}

void Piece::SetIsEmpty(bool isEmpty)
{
  _isEmpty = isEmpty;
}

Piece::PieceColour Piece::GetColour() const
{
  return _colour;
}

void Piece::SetColour(PieceColour colour)
{
  _colour = colour;
}
