//
// Created by Zoe on 08/01/2020.
//

#include "Enemy.h"
#include <iostream>

int Enemy::health()
{
  return hp;
}

int Enemy::attackDamage()
{
  return damage;
}

int Enemy::moveSpeed()
{
  return speed;
}

void Enemy::render(ASGE::Renderer* renderer)
{
  renderer->renderSprite(*spriteComponent()->getSprite());
}

bool Enemy::takeDamage(int hit)
{
  hp -= hit;

  return hp <= 0;
}

bool Enemy::isAlive()
{
  return is_alive;
}

void Enemy::isAlive(bool value)
{
  is_alive = value;
}
