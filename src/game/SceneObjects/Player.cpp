//
// Created by Owner on 17/12/2019.
//

#include "Player.h"

/*
 * move the player depending on which keys are pressed
 */
void Player::Movement(float x, float y)
{
  if (!spriteComponent())
  {
    // show error
    return;
  }

  ASGE::Sprite* sprite = spriteComponent()->getSprite();

  float new_x = x + sprite->xPos() * speed;
  float new_y = y + sprite->yPos() * speed;

  sprite->xPos(new_x);
  sprite->yPos(new_y);
}

void Player::takeDamage(int hit_damage)
{
  damage -= hit_damage;
}
