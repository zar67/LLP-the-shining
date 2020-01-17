//
// Created by Zoe on 09/01/2020.
//

#include "Ghost.h"

bool Ghost::setup(ASGE::Renderer* renderer, float x_pos, float y_pos)
{
  hp = 50;
  damage = 5;
  speed = 150;

  addCollisionComponent();
  if (addSpriteComponent(renderer, "data/Characters/Ghost.png"))
  {
    spriteComponent()->getSprite()->xPos(x_pos);
    spriteComponent()->getSprite()->yPos(y_pos);
    return true;
  }

  return false;
}

void Ghost::update(double delta_time, float player_x, float player_y)
{
  // Random Movement
  // Move Object Randomly
}
