//
// Created by Zoe on 09/01/2020.
//

#include "Projectile.h"

bool Projectile::update(double delta_time)
{
  float distanceTraveld =
    getDistanceBetween(startPosition[0],
                       startPosition[1],
                       spriteComponent()->getSprite()->xPos(),
                       spriteComponent()->getSprite()->yPos());
  if (distanceTraveld >= range)
  {
    return true;
  }
  move(delta_time, target[0], target[1], speed);
  return false;
}

bool Projectile::setup(ASGE::Renderer* renderer,
                       float move_speed,
                       float range,
                       float x_pos,
                       float y_pos,
                       float target_x,
                       float target_y)
{
  speed = move_speed;
  this->range = range;

  target[0] = target_x;
  target[1] = target_y;
  startPosition[0] = x_pos;
  startPosition[1] = y_pos;

  addCollisionComponent();
  if (addSpriteComponent(renderer, "/data/Projectile.png"))
  {
    spriteComponent()->getSprite()->xPos(x_pos);
    spriteComponent()->getSprite()->yPos(y_pos);
    return true;
  }

  return false;
}
