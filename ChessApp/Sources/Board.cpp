#include "Board.h"

#include "TextureLoader.h"

Board::Board(const std::shared_ptr<SDL_Renderer>& renderer) :
  ElementBase(renderer, LoadTexture(renderer, "Resources/board.png"), Vector2D(178, 178),
              Vector2D(0, 0),Vector2D(BOARD_SIZE, BOARD_SIZE))
{
  _pieces.emplace_back(renderer, "Resources/white_rook.png", Vector2D(0, 0));
  _pieces.emplace_back(renderer, "Resources/white_knight.png", Vector2D(BOARD_TILE_SIZE, 0));
  _pieces.emplace_back(renderer, "Resources/white_bishop.png", Vector2D(BOARD_TILE_SIZE * 2, 0));
  _pieces.emplace_back(renderer, "Resources/white_queen.png", Vector2D(BOARD_TILE_SIZE * 3, 0));
  _pieces.emplace_back(renderer, "Resources/white_king.png", Vector2D(BOARD_TILE_SIZE * 4, 0));
  _pieces.emplace_back(renderer, "Resources/white_bishop.png", Vector2D(BOARD_TILE_SIZE * 5, 0));
  _pieces.emplace_back(renderer, "Resources/white_knight.png", Vector2D(BOARD_TILE_SIZE * 6, 0));
  _pieces.emplace_back(renderer, "Resources/white_rook.png", Vector2D(BOARD_TILE_SIZE * 7, 0));

  for (int i = 0; i <= BOARD_TILE_SIZE * 7; i += BOARD_TILE_SIZE)
  {
    _pieces.emplace_back(renderer, "Resources/white_pawn.png", Vector2D(i, BOARD_TILE_SIZE));
  }

  for (int i = 0; i <= 80 * 7; i += 80)
  {
    _pieces.emplace_back(Vector2D(i, BOARD_TILE_SIZE * 2));
  }

  for (int i = 0; i <= 80 * 7; i += 80)
  {
    _pieces.emplace_back(Vector2D(i, BOARD_TILE_SIZE * 3));
  }

  for (int i = 0; i <= 80 * 7; i += 80)
  {
    _pieces.emplace_back(Vector2D(i, BOARD_TILE_SIZE * 4));
  }

  for (int i = 0; i <= 80 * 7; i += 80)
  {
    _pieces.emplace_back(Vector2D(i, BOARD_TILE_SIZE * 5));
  }

  for (int i = 0; i <= BOARD_TILE_SIZE * 7; i += BOARD_TILE_SIZE)
  {
    _pieces.emplace_back(renderer, "Resources/black_pawn.png", Vector2D(i, BOARD_TILE_SIZE * 6));
  }

  _pieces.emplace_back(renderer, "Resources/black_rook.png",
    Vector2D(0, BOARD_TILE_SIZE * 7));
  _pieces.emplace_back(renderer, "Resources/black_knight.png",
    Vector2D(BOARD_TILE_SIZE, BOARD_TILE_SIZE * 7));
  _pieces.emplace_back(renderer, "Resources/black_bishop.png",
    Vector2D(BOARD_TILE_SIZE * 2, BOARD_TILE_SIZE * 7));
  _pieces.emplace_back(renderer, "Resources/black_queen.png",
    Vector2D(BOARD_TILE_SIZE * 3, BOARD_TILE_SIZE * 7));
  _pieces.emplace_back(renderer, "Resources/black_king.png",
    Vector2D(BOARD_TILE_SIZE * 4, BOARD_TILE_SIZE * 7));
  _pieces.emplace_back(renderer, "Resources/black_bishop.png",
    Vector2D(BOARD_TILE_SIZE * 5, BOARD_TILE_SIZE * 7));
  _pieces.emplace_back(renderer, "Resources/black_knight.png",
    Vector2D(BOARD_TILE_SIZE * 6, BOARD_TILE_SIZE * 7));
  _pieces.emplace_back(renderer, "Resources/black_rook.png",
    Vector2D(BOARD_TILE_SIZE * 7, BOARD_TILE_SIZE * 7));

  Render();
}

void Board::OnClick(SDL_Event event)
{
  int x = event.motion.x;
  int y = event.motion.y;

  _pieceDraggingIndex = x / BOARD_TILE_SIZE + y / BOARD_TILE_SIZE * 8;
  _pieceDragging = _pieces[_pieceDraggingIndex];
  _pieces[_pieceDraggingIndex].SetIsEmpty(true);
}

void Board::OnMove(SDL_Event event)
{
  if (_pieceDragging.GetIsEmpty())
  {
    return;
  }

  Vector2D destinationRectXY = Vector2D(event.motion.x - BOARD_TILE_SIZE / 2, event.motion.y - BOARD_TILE_SIZE / 2);
  _pieceDragging.SetDestinationRect(destinationRectXY);

  Render();
}

void Board::OnRelease(SDL_Event event)
{
  if (_pieceDragging.GetIsEmpty())
  {
    return;
  }

  int x = event.motion.x;
  int y = event.motion.y;

  if (x < 0 || y < 0 || x > BOARD_SIZE || y > BOARD_SIZE)
  {
    _pieceDragging.SetIsEmpty(true);
    _pieces[_pieceDraggingIndex].SetIsEmpty(false);
    return;
  }

  int indexReleasedOn = x / BOARD_TILE_SIZE + y / BOARD_TILE_SIZE * 8;

  if (&_pieceDragging == &_pieces[indexReleasedOn])
  {
    _pieceDragging.SetIsEmpty(true);
    _pieces[_pieceDraggingIndex].SetIsEmpty(false);
  }
  else
  {
    _pieceDragging.SetDestinationRect(_pieces[indexReleasedOn].GetDestinationRect());
    _pieces[indexReleasedOn] = _pieceDragging;
    _pieceDragging.SetIsEmpty(true);
    _pieces[indexReleasedOn].SetIsEmpty(false);
  }

  Render();
}

void Board::Render()
{
  SDL_RenderClear(_renderer.get());
  ElementBase::Render();
   
  for (Piece piece : _pieces)
  {
    if (!piece.GetIsEmpty())
    {
      piece.Render();
    }
  }

  if (!_pieceDragging.GetIsEmpty())
  {
    _pieceDragging.Render();
  }

  SDL_RenderPresent(_renderer.get());
}
