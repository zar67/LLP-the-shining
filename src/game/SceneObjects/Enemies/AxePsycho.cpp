//
// Created by Zoe on 10/01/2020.
//

#include "AxePsycho.h"

#include <iostream>

bool AxePsycho::setup(
  ASGE::Renderer* renderer, float x_pos, float y_pos, float width, float height)
{
  hp = START_HP;
  damage = 25;
  speed = 100;
  in_room = false;

  screen_warning = new FlashComponent(renderer, ASGE::COLOURS::RED);

  addCollisionComponent();
  if (addSpriteComponent(renderer, "data/Characters/axe-man.png"))
  {
    spriteComponent()->getSprite()->xPos(x_pos);
    spriteComponent()->getSprite()->yPos(y_pos);
    spriteComponent()->getSprite()->width(width);
    spriteComponent()->getSprite()->height(height);
    return true;
  }

  return false;
}

void AxePsycho::update(double delta_time, float player_x, float player_y)
{
  // If Colliding With Player Attack and Don't Move

  // Move Towards Player if not killed
  if (in_room)
  {
    if (hp > 0)
    {
      std::vector<float> direction =
        getDirectionFromTo(spriteComponent()->getSprite()->xPos(),
                           spriteComponent()->getSprite()->yPos(),
                           player_x,
                           player_y);
      move(delta_time, direction[0], direction[1], speed);
    }
    else
    {
      std::vector<float> direction =
        getDirectionFromTo(spriteComponent()->getSprite()->xPos(),
                           spriteComponent()->getSprite()->yPos(),
                           spawned_x,
                           spawned_y);
      float distance =
        getDistanceBetween(spriteComponent()->getSprite()->xPos(),
                           spriteComponent()->getSprite()->yPos(),
                           spawned_x,
                           spawned_y);
      move(delta_time, direction[0], direction[1], speed);
      if (distance < 30.0f)
      {
        in_room = false;
        hp = START_HP;
      }
    }
  }
}

bool AxePsycho::inRoom()
{
  return in_room;
}

void AxePsycho::inRoom(bool value)
{
  in_room = value;
}

bool AxePsycho::spawnTimerEnd(float delta_time)
{
  current_time += delta_time;
  if (current_time >= timer_aim)
  {
    current_time = 0.0f;
    return true;
  }
  return false;
}

void AxePsycho::setSpawnedLocation(float x, float y)
{
  spawned_x = x;
  spawned_y = y;
}

FlashComponent* AxePsycho::flashComponent()
{
  return screen_warning;
}

bool AxePsycho::isKilled()
{
  return is_killed;
}

void AxePsycho::isKilled(bool value)
{
  is_killed = value;
}
