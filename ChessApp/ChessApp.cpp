#include <iostream>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"

#undef main

SDL_Window* Window;
SDL_Renderer* Renderer;
SDL_Event Event;
bool IsRunning = true;

SDL_Texture* LoadPng(const char* pngPath)
{
  IMG_Init(IMG_INIT_PNG);
  SDL_Surface* tempSurface = IMG_Load(pngPath);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer, tempSurface);
  SDL_FreeSurface(tempSurface);

  return texture;
}

struct Piece
{
  int x, y;
  bool isWhite;
  bool isEmpty = false;
  SDL_Texture* texture = nullptr;
  SDL_Rect srcRect;

  Piece(int x, int y) : x(x), y(y)
  {
    isEmpty = true;
    srcRect.x = srcRect.y = 0;
    srcRect.w = srcRect.h = 20;
  }

  Piece(const char* pngPath, int x, int y, bool isWhite) : x(x), y(y), isWhite(isWhite)
  {
    texture = LoadPng(pngPath);
    srcRect.x = srcRect.y = 0;
    srcRect.w = srcRect.h = 20;
  }
};

struct Board
{
  std::vector<Piece> pieces;
  SDL_Texture* texture;
  SDL_Rect srcRect;
  SDL_Rect dstRect;

  void Init()
  {
    texture = LoadPng("board.png");

    pieces.emplace_back("white_rook.png", 0, 0, true);
    pieces.emplace_back("white_knight.png", 80, 0, true);
    pieces.emplace_back("white_bishop.png", 80 * 2, 0, true);
    pieces.emplace_back("white_king.png", 80 * 3, 0, true);
    pieces.emplace_back("white_queen.png", 80 * 4, 0, true);
    pieces.emplace_back("white_bishop.png", 80 * 5, 0, true);
    pieces.emplace_back("white_knight.png", 80 * 6, 0, true);
    pieces.emplace_back("white_rook.png", 80 * 7, 0, true);

    for (int i = 0; i <= 80 * 7; i += 80)
    {
      pieces.emplace_back("white_pawn.png", i, 80, true);
    }
    
    for (int i = 0; i <= 80 * 7; i += 80)
    {
      pieces.emplace_back(i, 80 * 2);
    }

    for (int i = 0; i <= 80 * 7; i += 80)
    {
      pieces.emplace_back(i, 80 * 3);
    }

    for (int i = 0; i <= 80 * 7; i += 80)
    {
      pieces.emplace_back(i, 80 * 4);
    }

    for (int i = 0; i <= 80 * 7; i += 80)
    {
      pieces.emplace_back(i, 80 * 5);
    }

    for (int i = 0; i <= 80 * 7; i += 80)
    {
      pieces.emplace_back("black_pawn.png", i, 80 * 6, false);
    }

    pieces.emplace_back("black_rook.png", 0, 80 * 7, false);
    pieces.emplace_back("black_knight.png", 80, 80 * 7, false);
    pieces.emplace_back("black_bishop.png", 80 * 2, 80 * 7, false);
    pieces.emplace_back("black_king.png", 80 * 3, 80 * 7, false);
    pieces.emplace_back("black_queen.png", 80 * 4, 80 * 7, false);
    pieces.emplace_back("black_bishop.png", 80 * 5, 80 * 7, false);
    pieces.emplace_back("black_knight.png", 80 * 6, 80 * 7, false);
    pieces.emplace_back("black_rook.png", 80 * 7, 80 * 7, false);

    srcRect.x = srcRect.y = 0;
    srcRect.w = srcRect.h = 180;
    dstRect.x = dstRect.y = 0;
    dstRect.w = dstRect.h = 640;
  }
};

Board TheBoard;
Piece* PieceBeingDragged;



void Clean()
{
  SDL_DestroyWindow(Window);
  SDL_DestroyRenderer(Renderer);
  SDL_Quit();
}

void Render()
{
  SDL_RenderClear(Renderer);
  SDL_RenderCopy(Renderer, TheBoard.texture, &TheBoard.srcRect, &TheBoard.dstRect);
  for (auto piece : TheBoard.pieces)
  {
    if (piece.isEmpty)
    {
      continue;
    }
    SDL_Rect dstRect;
    dstRect.x = piece.x;
    dstRect.y = piece.y;
    dstRect.w = dstRect.h = 80;
    SDL_RenderCopy(Renderer, piece.texture, &piece.srcRect, &dstRect);
  }
  SDL_RenderPresent(Renderer);
}

void OnClick()
{
  int x = Event.motion.x;
  int y = Event.motion.y;

  int indexClicked = (x / 80) + ((y / 80) * 8);

  if (!TheBoard.pieces[indexClicked].isEmpty)
  {
    PieceBeingDragged = &TheBoard.pieces[indexClicked];
  }
}

void OnRelease()
{
  if (PieceBeingDragged == nullptr)
  {
    return;
  }

  int x = Event.motion.x;
  int y = Event.motion.y;
  
  int indexClicked = (x / 80) + ((y / 80) * 8);

  if (PieceBeingDragged == &TheBoard.pieces[indexClicked])
  {
    return;
  }

  TheBoard.pieces[indexClicked].texture = PieceBeingDragged->texture;
  TheBoard.pieces[indexClicked].isWhite = PieceBeingDragged->isWhite;
  TheBoard.pieces[indexClicked].isEmpty = PieceBeingDragged->isEmpty;

  PieceBeingDragged->isEmpty = true;

  PieceBeingDragged = nullptr;

  Render();
}

void HandleEvents()
{
  while (SDL_PollEvent(&Event))
  {
    switch (Event.type)
    {
    case SDL_QUIT:
      IsRunning = false;
      break;

    case SDL_MOUSEBUTTONDOWN:
      OnClick();
      break;

    case SDL_MOUSEBUTTONUP:
      OnRelease();
      break;

    default:
      break;
    }
  }
}

void Update()
{
  HandleEvents();
}

void Init()
{
  SDL_Init(SDL_INIT_EVERYTHING);
  Window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 640,
    SDL_WINDOW_SHOWN);
  Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);

  TheBoard.Init();
  Render();
}

int main(int argc, const char* argv[])
{
  Init();

  while (IsRunning)
  {
    Update();
  }

  Clean();
  return 0;
}
