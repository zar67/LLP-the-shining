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
  auto bullet = new Projectile();
  bullet->setup(renderer,
                speed,
                range,
                player_x,
                player_y,
                last_direction[0],
                last_direction[1]);
  projectiles.push_back(bullet);
}

void ShootingComponent::maintainProjectiles(float delta_time)
{
  auto itr = projectiles.begin();
  for (auto& bullet : projectiles)
  {
    if (bullet->update(delta_time))
    {
      delete (bullet);
      bullet = nullptr;
      projectiles.erase(itr);
    }
    itr++;
  }
}

void ShootingComponent::setSpeed(int value)
{
  speed = value;
}

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
