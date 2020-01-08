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
  if (spriteComponent()->getSprite() == nullptr)
  {
    std::cout << "SPRITE NULL" << std::endl;
  }
  else
  {
    renderer->renderSprite(*spriteComponent()->getSprite());
  }
}

void Enemy::move(double delta_time, float x_dir, float y_dir)
{
  if (spriteComponent())
  {
    spriteComponent()->getSprite()->xPos(
      spriteComponent()->getSprite()->xPos() + (x_dir * speed * delta_time));
    spriteComponent()->getSprite()->yPos(
      spriteComponent()->getSprite()->yPos() + (y_dir * speed * delta_time));
  }

  updateCollisionComponent();
}

void Enemy::takeDamage(int hit)
{
  hp -= hit;

  if (hp <= 0)
  {
    die();
  }
}

void Enemy::die()
{
  delete this;
}
