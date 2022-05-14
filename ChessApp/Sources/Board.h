#pragma once

#include <vector>

#include "ElementBase.h"
#include "Piece.h"
#include "SdlDeleter.h"

constexpr int BOARD_SIZE = 640;
constexpr int BOARD_TILE_SIZE = 80;

class Board final : public ElementBase
{
public:
  explicit Board(const std::shared_ptr<SDL_Renderer>& renderer);
  void Update();
  void Render() override;

  void OnClick(SDL_Event event);
  void OnMove(SDL_Event event);
  void OnRelease(SDL_Event event);

private:
  std::vector<Piece> _pieces;
  Piece _pieceDragging;
  int _pieceDraggingIndex;
  SDL_Event _event;
};

