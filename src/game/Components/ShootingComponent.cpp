//
// Created by Owner on 13/01/2020.
//

#include "ShootingComponent.h"

ShootingComponent::ShootingComponent()
{
  last_direction.reserve(2);
}

void ShootingComponent::Fire(ASGE::Renderer* renderer,
                             float player_x,
                             float player_y)
{
  Projectile* bullet = new Projectile();
  bullet->setup(
    renderer, speed, player_x, player_y, last_direction[0], last_direction[1]);
  // bullet->addSpriteComponent(renderer, "/data/projectile.png");
  // bullet->spriteComponent()->getSprite()->xPos(300);
  // bullet->spriteComponent()->getSprite()->yPos(300);
  // bullet->spriteComponent()->getSprite()->width(50);
  // bullet->spriteComponent()->getSprite()->height(50);

  projectiles.push_back(bullet);
}

void ShootingComponent::maintainProjectiles(float delta_time)
{
  for (auto& bullet : projectiles)
  {
    bullet->update(delta_time);
  }
}

void ShootingComponent::setSpeed(int value)
{
  speed = value;
}
/*
std::vector<Projectile> ShootingComponent::getProjectiles()
{
    return projectiles;
}*/

void ShootingComponent::render(ASGE::Renderer* renderer)
{
  for (auto& bullet : projectiles)
  {
    ASGE::Sprite* s = bullet->spriteComponent()->getSprite();
    renderer->renderSprite(*s);
  }
}

void ShootingComponent::setLastDirection(float x, float y)
{
  last_direction.clear();
  last_direction.push_back(x);
  last_direction.push_back(y);
}
