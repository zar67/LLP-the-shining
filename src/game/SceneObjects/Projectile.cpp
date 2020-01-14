//
// Created by Zoe on 09/01/2020.
//

#include "Projectile.h"

void Projectile::update(double delta_time)
{
  move(delta_time, target[0], target[1], speed);
}

bool Projectile::setup(ASGE::Renderer* renderer,
                       float move_speed,
                       float x_pos,
                       float y_pos,
                       float target_x,
                       float target_y)
{
  speed = move_speed;

  std::vector<float> dir = getDirectionFromTo(x_pos, y_pos, target_x, target_y);
  target[0] = dir[0];
  target[1] = dir[1];

  if (addSpriteComponent(renderer, "data/Projectile.png"))
  {
    spriteComponent()->getSprite()->xPos(x_pos);
    spriteComponent()->getSprite()->yPos(y_pos);
    return true;
  }

  return false;
}
