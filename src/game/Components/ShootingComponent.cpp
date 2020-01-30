//
// Created by Owner on 13/01/2020.
//

#include "ShootingComponent.h"
#include "../SceneObjects/Enemies/Enemy.h"

/**
 *   @brief   Constructor
 */
ShootingComponent::ShootingComponent()
{
  move_direction.reserve(2);
  setMoveDirection(0, -1);
}

/**
 *   @brief   Fires a projectile
 *   @details Creates a new projectile and sets it up
 */
void ShootingComponent::Fire(ASGE::Renderer* renderer,
                             float start_x,
                             float start_y,
                             float x_dir,
                             float y_dir)
{
  auto bullet = new Projectile();
  bullet->setup(renderer, speed, range, start_x, start_y, x_dir, y_dir);
  bullet->spriteComponent()->getSprite()->width(size);
  bullet->spriteComponent()->getSprite()->height(size);
  projectiles.push_back(bullet);
}

/**
 *   @brief   Updates projectiles
 *   @details Calculates collision for the projectiles in the component and
 * damages enemy if hit
 */
void ShootingComponent::maintainProjectiles(AudioManager* audio,
                                            double delta_time,
                                            std::vector<GameObject*> colliders,
                                            int damage)
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
    else
    {
      for (auto& col : colliders)
      {
        col->updateCollisionComponent();
        if (bullet->collisionComponent()->hasCollided(
              *col->collisionComponent()))
        {
          // collision
          delete (bullet);
          bullet = nullptr;
          projectiles.erase(itr);
          auto* enemy = static_cast<Enemy*>(col);
          enemy->takeDamage(audio, damage);
          break;
        }
      }
    }
    itr++;
  }
}

/**
 *   @brief   Updates projectiles
 *   @details Caclaulates collision for projectiles on the component and damages
 * player if hit
 */
bool ShootingComponent::hitPlayer(
  double delta_time,
  GameObject* collider,
  std::vector<InteractableObjects*> scene_objects)
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
    for (auto& obj : scene_objects)
    {
      if (bullet->collisionComponent()->hasCollided(*obj->collisionComponent()))
      {
        delete (bullet);
        bullet = nullptr;
        projectiles.erase(itr);
        return false;
      }
    }

    itr++;
  }

  return false;
}

/**
 *   @brief   Sets the projectile speed
 */
void ShootingComponent::setSpeed(float value)
{
  speed = value;
}

/**
 *   @brief   Renders all projectiles
 */
void ShootingComponent::render(ASGE::Renderer* renderer)
{
  for (auto& bullet : projectiles)
  {
    ASGE::Sprite* sprite = bullet->spriteComponent()->getSprite();
    renderer->renderSprite(*sprite);
  }
}

/**
 *   @brief   Sets the move direction of the projectiles
 */
void ShootingComponent::setMoveDirection(float x_dir, float y_dir)
{
  move_direction.clear();
  move_direction.push_back(x_dir);
  move_direction.push_back(y_dir);
}

/**
 *   @brief   Set the size of the projectile sprite
 */
void ShootingComponent::setSize(float value)
{
  size = value;
}
