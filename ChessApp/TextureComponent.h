#pragma once

#include "SDL.h"

#include "Components.h"
#include "TextureManager.h"

class TextureComponent : public Component
{
public:
  TextureComponent() = default;
  TextureComponent(const char* path)
  {
    _texture = TextureManager::LoadTexture(path);
  }

  void Init() override
  {
    _position = &GetEntity()->GetComponent<PositionComponent>();
    _srcRect.x = _srcRect.y = 0;
    _srcRect.w = _srcRect.h = 16;
    _destRect.w = _destRect.h = 80;
  }

  void Update() override
  {
    _destRect.x = _position->GetX();
    _destRect.y = _position->GetY();
  }

  void Draw() override
  {
    TextureManager::Draw(_texture, _srcRect, _destRect);
  }

private:
  PositionComponent* _position;
  SDL_Texture* _texture;
  SDL_Rect _srcRect;
  SDL_Rect _destRect;
};
