#pragma once

#include <string>

#include "ElementBase.h"

class Piece : public ElementBase
{
public:
  Piece();
  Piece(const std::shared_ptr<SDL_Renderer>& renderer, const std::string& pngPath, Vector2D destinationXY);
  Piece(Vector2D destinationXY);

  Vector2D GetDestinationRect();
  void SetDestinationRect(Vector2D destinationRectXY);
  bool GetIsEmpty() const;
  void SetIsEmpty(bool isEmpty);

private:
  bool _isEmpty = true;
};

