//
// Created by Owner on 17/12/2019.
//

#include "GameObject.h"

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

void GameObject::addCollisionComponenet()
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

  ASGE::Sprite* sprite = sprite_component->getSprite();
  float bounding_box[4] = {
    sprite->xPos(), sprite->yPos(), sprite->width(), sprite->height()
  };
  collision_component->updateBoundingBox(bounding_box);
}
