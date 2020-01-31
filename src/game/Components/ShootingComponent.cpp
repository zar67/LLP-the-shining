//
// Created by Owner on 13/01/2020.
//

#include "ShootingComponent.h"
#include "../SceneObjects/Enemies/Enemy.h"

#include <iostream>

/**
 *   @brief   Constructor
 */
ShootingComponent::ShootingComponent(ASGE::Renderer* renderer, bool use_arrow)
{
  move_direction.reserve(2);
  setMoveDirection(0, -1);

  if (use_arrow)
  {
    addSpriteComponent(renderer, "/data/aiming_arrow.png");
    sprite_component->getSprite()->xPos(0);
    sprite_component->getSprite()->yPos(0);
    sprite_component->getSprite()->width(150);
    sprite_component->getSprite()->height(10);
  }
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

  x_shoot = x_dir;
  y_shoot = y_dir;
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
    if (sprite)
    {
      renderer->renderSprite(*sprite);
    }
  }
  if (spriteComponent())
  {
    renderer->renderSprite(*spriteComponent()->getSprite());
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

void ShootingComponent::reset()
{
  auto itr = projectiles.begin();
  for (auto& bullet : projectiles)
  {
    delete (bullet);
    itr++;
  }
  projectiles.clear();
}

bool ShootingComponent::addSpriteComponent(ASGE::Renderer* renderer,
                                           const std::string& texture_location)
{
  if (sprite_component)
  {
    delete (sprite_component);
  }
  sprite_component = new SpriteComponent();

  if (sprite_component->loadSpriteComponent(renderer, texture_location))
  {
    return true;
  }

  delete (sprite_component);
  sprite_component = nullptr;
  return false;
}

SpriteComponent* ShootingComponent::spriteComponent()
{
  return sprite_component;
}

void ShootingComponent::arrow_control(const float x_pos, const float y_pos)
{
  sprite_component->getSprite()->xPos(x_pos - 45.0f);
  sprite_component->getSprite()->yPos(y_pos + 30.0f);
  calcAngle(x_shoot, y_shoot);
}

float ShootingComponent::calcAngle(float x, float y)
{
  float value = atan(y / x);
  if (x == -1)
  {
    value = atan(y / x) + 3.1f;
  }

  float radians = value;
  spriteComponent()->getSprite()->rotationInRadians(radians);
  return radians;
}
