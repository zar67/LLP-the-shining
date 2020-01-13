//
// Created by Owner on 17/12/2019.
//

#include "Player.h"

void Player::init(ASGE::Renderer* renderer,
                  std::string tex_directory,
                  float x_pos,
                  float y_pos,
                  float width,
                  float height)
{
  if (!spriteComponent())
  {
    addSpriteComponent(renderer, tex_directory);
  }
  sprite_component->getSprite()->xPos(x_pos);
  sprite_component->getSprite()->yPos(y_pos);
  sprite_component->getSprite()->width(width);
  sprite_component->getSprite()->height(height);
}

/*
 * move the player depending on which keys are pressed
 */

void Player::Movement(float delta_time)
{
  if (!spriteComponent())
  {
    // show error
    return;
  }

  ASGE::Sprite* sprite = spriteComponent()->getSprite();

  //             currnt pos         direction        speed   stop frame rate
  //             dependent
  float new_x = sprite->xPos() + vector_movement[0] * speed * delta_time;
  float new_y = sprite->yPos() + vector_movement[1] * speed * delta_time;

  sprite->xPos(new_x);
  sprite->yPos(new_y);
}

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

void Player::setMovementVec(float* vec)
{
  for (int i = 0; i < 2; ++i)
  {
    vector_movement[i] = vec[i];
  }
}
