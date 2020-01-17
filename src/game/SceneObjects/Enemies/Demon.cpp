//
// Created by Zoe on 08/01/2020.
//

#include "Demon.h"
#include <iostream>
#include <math.h>

bool Demon::setup(ASGE::Renderer* renderer, float x_pos, float y_pos)
{
  hp = 100;
  damage = 10;
  speed = 80;

  addCollisionComponent();
  if (addSpriteComponent(renderer, "data/Characters/Demon.png"))
  {
    spriteComponent()->getSprite()->xPos(x_pos);
    spriteComponent()->getSprite()->yPos(y_pos);
    return true;
  }

  return false;
}

void Demon::update(double delta_time, float player_x, float player_y)
{
  // Move Towards Player
  float distance_to_player =
    getDistanceBetween(spriteComponent()->getSprite()->xPos(),
                       spriteComponent()->getSprite()->yPos(),
                       player_x,
                       player_y);
  std::vector<float> direction_to_player =
    getDirectionFromTo(spriteComponent()->getSprite()->xPos(),
                       spriteComponent()->getSprite()->yPos(),
                       player_x,
                       player_y);
  if (distance_to_player > distance_to_keep)
  {
    move(delta_time, direction_to_player[0], direction_to_player[1], speed);
  }
  else if (distance_to_player < distance_to_keep)
  {
    move(delta_time, -direction_to_player[0], -direction_to_player[1], speed);
  }

  // Shoot Player
}