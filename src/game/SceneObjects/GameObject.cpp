//
// Created by Owner on 17/12/2019.
//

#include "GameObject.h"
#include <math.h>

GameObject::~GameObject()
{
  if (sprite_component)
  {
    delete (sprite_component);
    sprite_component = nullptr;
  }
  if (collision_component)
  {
    delete (collision_component);
    collision_component = nullptr;
  }
}

/*
 * initialise sprite component with a directory to a image
 * if fails deletes sprite component
 * catch boolean value when called to prevent crash
 */
bool GameObject::addSpriteComponent(ASGE::Renderer* renderer,
                                    std::string texture_location)
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

SpriteComponent* GameObject::spriteComponent()
{
  return sprite_component;
}

void GameObject::addCollisionComponent()
{
  if (collision_component)
  {
    delete (collision_component);
  }
  collision_component = new CollisionComponent();
}

CollisionComponent* GameObject::collisionComponent()
{
  return collision_component;
}

/*
 * get the xpos, ypos, width and height of the sprite and send it to collision
 * component when detecting if collision took place
 */
void GameObject::updateCollisionComponent()
{
  if (!collision_component)
  {
    return;
  }

  if (sprite_component)
  {
    ASGE::Sprite* sprite = sprite_component->getSprite();
    float bounding_box[4] = {
      sprite->xPos(), sprite->yPos(), sprite->width(), sprite->height()
    };
    collision_component->updateBoundingBox(bounding_box);
  }
}

void GameObject::move(float delta_time, float x_dir, float y_dir, float speed)
{
  if (sprite_component)
  {
    sprite_component->getSprite()->xPos(sprite_component->getSprite()->xPos() +
                                        (x_dir * speed * delta_time));
    sprite_component->getSprite()->yPos(sprite_component->getSprite()->yPos() +
                                        (y_dir * speed * delta_time));
  }

  updateCollisionComponent();
}

std::vector<float> GameObject::getDirectionFromTo(float from_x,
                                                  float from_y,
                                                  float to_x,
                                                  float to_y)
{
  float length = getDistanceBetween(from_x, from_y, to_x, to_y);
  std::vector<float> dir = { to_x - from_x, to_y - from_y };

  dir[0] /= length;
  dir[1] /= length;

  return dir;
}

float GameObject::getDistanceBetween(float from_x,
                                     float from_y,
                                     float to_x,
                                     float to_y)
{
  float x_dir = to_x - from_x;
  float y_dir = to_y - from_y;

  return sqrt((x_dir * x_dir) + (y_dir * y_dir));
}
