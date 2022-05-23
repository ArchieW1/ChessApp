#pragma once

#include <string>

#include "RenderableBase.h"



class Piece : public RenderableBase
{
public:
  enum PieceColour { WHITE, BLACK, NONE };

  Piece();
  Piece(const std::shared_ptr<SDL_Renderer>& renderer, const std::string& pngPath, Vector2D destinationXY,
        PieceColour colour);

  explicit Piece(Vector2D destinationXY);

  bool GetIsEmpty() const;
  void SetIsEmpty(bool isEmpty);
  PieceColour GetColour() const;
  void SetColour(PieceColour colour);

private:
  bool _isEmpty;
  PieceColour _colour;
};

