//
// Created by Owner on 17/12/2019.
//

#include "Player.h"
#include <iostream>

Player::~Player()
{
  if (weapon_component)
  {
    delete weapon_component;
    weapon_component = nullptr;
  }
}

void Player::init(ASGE::Renderer* renderer,
                  std::string& tex_directory,
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
    addWeaponComponent();
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

bool Player::update(float delta_time, std::vector<GameObject*> enemies)
{
  if (sprite_component)
  {
    move(delta_time, vector_movement[0], vector_movement[1], speed);
  }

  // bullet movement
  if (weapon_component)
  {
    weaponComponent()->maintainProjectiles(delta_time, enemies);
  }

  std::cout << health << std::endl;

  return health <= 0;
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
  health -= hit_damage;
}

void Player::moveVertical(float move)
{
  input_vector[1] = move;
  setMovementVec(input_vector);

  if (move != 0)
  {
    weapon_component->setMoveDirection(input_vector[0], move);
  }
}

void Player::moveHorizontal(float move)
{
  input_vector[0] = move;
  setMovementVec(input_vector);

  if (move != 0)
  {
    weapon_component->setMoveDirection(move, input_vector[1]);
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

bool Player::addWeaponComponent()
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

bool Player::addDamagePowerup()
{
  return addPowerup(0);
}

bool Player::addHealthPowerup()
{
  return addPowerup(1);
}

bool Player::addMoveSpeedPowerup()
{
  return addPowerup(2);
}

bool Player::addShotSizePowerup()
{
  return addPowerup(3);
}

bool Player::addShotSpeedPowerup()
{
  return addPowerup(4);
}

bool* Player::getPowerups()
{
  return powerups;
}

bool Player::addPowerup(int index)
{
  if (coins >= 20)
  {
    powerups[index] = true;
    coins -= 20;
    return true;
  }
  return false;
}
