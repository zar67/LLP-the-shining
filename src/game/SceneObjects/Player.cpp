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
  if (!weapon_component)
  {
    addWeaponCompononet();
  }
  if (!collision_component)
  {
    addCollisionComponent();
  }
  sprite_component->getSprite()->xPos(x_pos);
  sprite_component->getSprite()->yPos(y_pos);
  sprite_component->getSprite()->width(width);
  sprite_component->getSprite()->height(height);
}

/*
 * move the player depending on which keys are pressed
 */

void Player::Movement(float delta_time, std::vector<GameObject*> enemies)
{
  if (!spriteComponent())
  {
    // show error
    return;
  }

  move(delta_time, vector_movement[0], vector_movement[1], speed);

  // bullet movement
  if (weapon_component)
  {
    weaponComponent()->maintainProjectiles(delta_time, enemies);
  }
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

void Player::moveVertical(float move)
{
  input_vector[1] = move;
  setMovementVec(input_vector);

  if (move != 0)
  {
    weapon_component->setLastDirection(input_vector[0], move);
  }
}

void Player::moveHorizontal(float move)
{
  input_vector[0] = move;
  setMovementVec(input_vector);

  if (move != 0)
  {
    weapon_component->setLastDirection(move, input_vector[1]);
  }
}

void Player::setMovementVec(float* vec)
{
  for (int i = 0; i < 2; ++i)
  {
    vector_movement[i] = vec[i];
  }
}

float* Player::getDirectionVector()
{
  return vector_movement;
}

bool Player::addWeaponCompononet()
{
  if (weapon_component)
  {
    delete (weapon_component);
  }
  weapon_component = new ShootingComponent();

  return true;
}

ShootingComponent* Player::weaponComponent()
{
  return weapon_component;
}
