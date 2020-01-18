//
// Created by Owner on 13/01/2020.
//

#include "ShootingComponent.h"
#include "../SceneObjects/Enemies/Enemy.h"

ShootingComponent::ShootingComponent()
{
  move_direction.reserve(2);
  setMoveDirection(0, -1);
}

void ShootingComponent::Fire(ASGE::Renderer* renderer,
                             float start_x,
                             float start_y)
{
  auto bullet = new Projectile();
  bullet->setup(renderer,
                speed,
                range,
                start_x,
                start_y,
                move_direction[0],
                move_direction[1]);
  projectiles.push_back(bullet);
}

// detect collision for game objects
void ShootingComponent::maintainProjectiles(double delta_time,
                                            std::vector<GameObject*> colliders)
{
  auto itr = projectiles.begin();
  for (auto& bullet : projectiles)
  {
    bullet->updateCollisionComponent();
    if (bullet->update(delta_time))
    {
      delete (bullet);
      bullet = nullptr;
      projectiles.erase(itr);
      continue;
    }
    for (auto& col : colliders)
    {
      col->updateCollisionComponent();
      if (bullet->collisionComponent()->hasCollided(*col->collisionComponent()))
      {
        // collision
        delete (bullet);
        bullet = nullptr;
        projectiles.erase(itr);
        try
        {
          Enemy* enemy = static_cast<Enemy*>(col);
          enemy->takeDamage(25);
        }
        catch (const std::exception&)
        {
          break;
        }
        break;
      }
    }
    itr++;
  }
}

bool ShootingComponent::hitPlayer(double delta_time, GameObject* collider)
{
  auto itr = projectiles.begin();
  for (auto& bullet : projectiles)
  {
    bullet->updateCollisionComponent();
    if (bullet->update(delta_time))
    {
      delete (bullet);
      bullet = nullptr;
      projectiles.erase(itr);
      continue;
    }

    collider->updateCollisionComponent();
    if (bullet->collisionComponent()->hasCollided(
          *collider->collisionComponent()))
    {
      // collision
      delete (bullet);
      bullet = nullptr;
      projectiles.erase(itr);
      return true;
    }

    itr++;
  }

  return false;
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

void ShootingComponent::setMoveDirection(float x, float y)
{
  move_direction.clear();
  move_direction.push_back(x);
  move_direction.push_back(y);
}
