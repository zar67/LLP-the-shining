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
  if (getDistanceToPlayer(player_x, player_y) > distance_to_keep)
  {
    std::vector<float> dir = getDirectionToPlayer(player_x, player_y);
    std::cout << dir[0] << ", " << dir[1] << std::endl;
    move(delta_time, dir[0], dir[1]);
  }

  // Shoot Player
}

std::vector<float> Demon::getDirectionToPlayer(float player_x, float player_y)
{
  float length = getDistanceToPlayer(player_x, player_y);

  std::vector<float> dir = { player_x - spriteComponent()->getSprite()->xPos(),
                             player_y -
                               spriteComponent()->getSprite()->yPos() };

  dir[0] /= length;
  dir[1] /= length;

  return dir;
}

float Demon::getDistanceToPlayer(float player_x, float player_y)
{
  float x_dir = player_x - spriteComponent()->getSprite()->xPos();
  float y_dir = player_y - spriteComponent()->getSprite()->yPos();

  return sqrt((x_dir * x_dir) + (y_dir * y_dir));
}
