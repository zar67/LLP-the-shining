//
// Created by Zoe on 09/01/2020.
//

#include "Ghost.h"

bool Ghost::setup(ASGE::Renderer* renderer, float x_pos, float y_pos)
{
  hp = 50;
  damage = 5;
  speed = 150;

  addCollisionComponent();
  if (addSpriteComponent(renderer, "data/Characters/Ghost.png"))
  {
    spriteComponent()->getSprite()->xPos(x_pos);
    spriteComponent()->getSprite()->yPos(y_pos);
    return true;
  }

  return false;
}

void Ghost::update(double delta_time,
                   std::vector<InteractableObjects*>& objects,
                   bool doors[4])
{
  // Random update
  // Move Object Randomly
  if (!obj_grabbed)
  {
    obj_grabbed = grabClosestObject(objects);
    getMoveToDoor(doors, door_pos);
  }
  // move object to block door
  else
  {
    if (getDistanceBetween(obj_grabbed->spriteComponent()->getSprite()->xPos(),
                           obj_grabbed->spriteComponent()->getSprite()->yPos(),
                           door_pos[0],
                           door_pos[1]) > 5.0f)
    {
      direction =
        getDirectionFromTo(obj_grabbed->spriteComponent()->getSprite()->xPos(),
                           obj_grabbed->spriteComponent()->getSprite()->yPos(),
                           door_pos[0],
                           door_pos[1]);
      obj_grabbed->move(
        delta_time, direction[0], direction[1], jedi_force_speed);
    }
    else
    {
      obj_grabbed = nullptr;
    }
  }
}

GameObject* Ghost::grabClosestObject(std::vector<InteractableObjects*> objects)
{
  ASGE::Sprite* ghost_sprite = spriteComponent()->getSprite();
  InteractableObjects* closest_obj = nullptr;
  float distance = -1.0f;
  for (auto& obj : objects)
  {
    if (obj->isGrabbed())
    {
      continue;
    }
    ASGE::Sprite* obj_sprite = obj->spriteComponent()->getSprite();
    float next_distance = getDistanceBetween(ghost_sprite->xPos(),
                                             ghost_sprite->yPos(),
                                             obj_sprite->xPos(),
                                             obj_sprite->yPos());
    if (distance == -1.0f || distance > next_distance)
    {
      distance = next_distance;
      closest_obj = obj;
    }
  }
  if (closest_obj)
  {
    closest_obj->setIsGrabbed(true);
  }
  return closest_obj;
}

void Ghost::getMoveToDoor(const bool doors[4], float (&out_pos)[2])
{
  int choice = 0;
  do
  {
    choice = rand() % 3;
  } while (!doors[choice]);

  float x_pos = 0.0f;
  float y_pos = 0.0f;

  if (choice == 0)
  {
    x_pos = 320.0f;
    y_pos = 100.0f;
  }
  else if (choice == 1)
  {
    x_pos = 540.0f;
    y_pos = 240.0f;
  }
  else if (choice == 2)
  {
    x_pos = 320.0f;
    y_pos = 380.0f;
  }
  else
  {
    x_pos = 100.0f;
    y_pos = 240.0f;
  }

  out_pos[0] = x_pos;
  out_pos[1] = y_pos;
}
