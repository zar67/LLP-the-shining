//
// Created by Owner on 22/01/2020.
//

#include "InteractableObjects.h"

bool InteractableObjects::checkHealth(ASGE::Renderer* renderer)
{
  if (hp <= 0)
  {
    return true;
  }
  else if (hp <= 50 && !secondary_texture.empty())
  {
    pos_x = spriteComponent()->getSprite()->xPos();
    pos_y = spriteComponent()->getSprite()->yPos();

    addSpriteComponent(renderer, secondary_texture);
    spriteComponent()->getSprite()->xPos(pos_x);
    spriteComponent()->getSprite()->yPos(pos_y);
    updateCollisionComponent();
  }
  return false;
}

bool InteractableObjects::setup(ASGE::Renderer* renderer,
                                float x_pos,
                                float y_pos)
{
  hp = 100;
  speed = 7;
  pos_x = x_pos;
  pos_y = y_pos;

  addCollisionComponent();
  if (addSpriteComponent(renderer, "data/Objects/crate2.png"))
  {
    spriteComponent()->getSprite()->xPos(x_pos);
    spriteComponent()->getSprite()->yPos(y_pos);
    updateCollisionComponent();
    return true;
  }

  return true;
}

void InteractableObjects::setIsGrabbed(bool value)
{
  is_grabbed = value;
}

bool InteractableObjects::isGrabbed()
{
  return is_grabbed;
}

int InteractableObjects::damage()
{
  return movement_damage;
}

void InteractableObjects::canDamage(bool value)
{
  can_damage = value;
}

bool InteractableObjects::canDamage()
{
  return can_damage;
}

void InteractableObjects::tickDamage(float delta_time)
{
  current_time += delta_time;
  if (current_time >= WAIT)
  {
    can_damage = true;
    current_time = 0.0f;
  }
}
