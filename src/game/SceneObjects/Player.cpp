//
// Created by Owner on 17/12/2019.
//

#include "Player.h"
#include <iostream>

Player::~Player()
{
  delete weapon_component;
  weapon_component = nullptr;
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

void Player::reset(float game_width, float game_height)
{
  sprite_component->getSprite()->xPos(game_width / 2 - 17);
  sprite_component->getSprite()->yPos(game_height / 2 - 24.5f);

  health = powerups[health_powerup_index] ? starting_health * 2
                                          : starting_health;
  damage = powerups[damage_powerup_index] ? starting_damage * 2
                                          : starting_damage;
  speed = powerups[move_speed_powerup_index] ? starting_speed * 2
                                             : starting_speed;

  weapon_component->setSpeed(powerups[shot_speed_powerup_index]
                               ? starting_shot_speed * 2
                               : starting_shot_speed);
  weapon_component->setSize(powerups[shot_size_powerup_index]
                              ? starting_shot_size * 2
                              : starting_shot_size);
}

/*
 * move the player depending on which keys are pressed
 */

bool Player::update(double delta_time, std::vector<GameObject*> enemies)
{
  if (sprite_component)
  {
    move(delta_time, vector_movement[0], vector_movement[1], speed);
  }

  // bullet movement
  if (weapon_component)
  {
    weaponComponent()->maintainProjectiles(delta_time, enemies, damage);
  }

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
  if (addPowerup(damage_powerup_index))
  {
    damage = starting_damage * 2;
    return true;
  }

  return false;
}

bool Player::addHealthPowerup()
{
  if (addPowerup(health_powerup_index))
  {
    health = starting_health * 2;
    return true;
  }

  return false;
}

bool Player::addMoveSpeedPowerup()
{
  if (addPowerup(move_speed_powerup_index))
  {
    speed = starting_speed * 2;
    return true;
  }

  return false;
}

bool Player::addShotSizePowerup()
{
  if (addPowerup(shot_size_powerup_index))
  {
    weapon_component->setSize(starting_shot_size * 2);
    return true;
  }

  return false;
}

bool Player::addShotSpeedPowerup()
{
  if (addPowerup(shot_speed_powerup_index))
  {
    weapon_component->setSpeed(starting_shot_speed * 2);
    return true;
  }

  return false;
}

bool* Player::getPowerups()
{
  return powerups;
}

void Player::addCoins(int amount)
{
  coins += amount;
}

int Player::getCoins()
{
  return coins;
}

int Player::getHealth()
{
  return health;
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
