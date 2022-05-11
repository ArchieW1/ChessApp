#pragma once

#include "Components.h"

class PositionComponent : public Component
{
public:
  int GetX()
  {
    return _xPos;
  }

  int GetY()
  {
    return _yPos;
  }

  void SetPos(int x, int y)
  {
    _xPos = x;
    _yPos = y;
  }

private:
  int _xPos = 0;
  int _yPos = 0;
};
