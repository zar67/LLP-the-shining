//
// Created by Zoe on 10/01/2020.
//

#include "AxePsycho.h"

#include <iostream>

AxePsycho::~AxePsycho()
{
  if (screen_warning)
  {
    delete (screen_warning);
    screen_warning = nullptr;
  }
}

bool AxePsycho::setup(
  ASGE::Renderer* renderer, float x_pos, float y_pos, float width, float height)
{
  hp = START_HP;
  damage = 25;
  speed = 60;
  in_room = false;

  addFlashComponent(renderer, ASGE::COLOURS::RED);
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
    if (is_paused)
    {
      is_paused = !spawnTimerEnd(delta_time, PASUE_TIME, current_pause_time);
    }
    if (hp > 0 && !isPaused())
    {
      std::vector<float> direction =
        getDirectionFromTo(spriteComponent()->getSprite()->xPos(),
                           spriteComponent()->getSprite()->yPos(),
                           player_x,
                           player_y);
      if (direction[0] < 0)
      {
        spriteComponent()->getSprite()->setFlipFlags(ASGE::Sprite::FLIP_X);
      }
      else if (direction[0] > 0)
      {
        spriteComponent()->getSprite()->setFlipFlags(ASGE::Sprite::NORMAL);
      }
      move(delta_time, direction[0], direction[1], speed);
    }
    else if (hp <= 0)
    {
      speed = quick_speed;
      std::vector<float> direction =
        getDirectionFromTo(spriteComponent()->getSprite()->xPos(),
                           spriteComponent()->getSprite()->yPos(),
                           spawned_x,
                           spawned_y);
      float distance =
        getDistanceBetween(spriteComponent()->getSprite()->xPos(),
                           spriteComponent()->getSprite()->yPos(),
                           spawned_x,
                           spawned_y) -
        spriteComponent()->getSprite()->width() / 2.0f;
      move(delta_time, direction[0], direction[1], speed);
      if (distance < 40.0f)
      {
        in_room = false;
        hp = START_HP;
        speed = 60;
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

bool AxePsycho::spawnTimerEnd(float delta_time,
                              float timer_aim,
                              float& current_time)
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

void AxePsycho::addFlashComponent(ASGE::Renderer* renderer, ASGE::Colour colour)
{
  if (flashComponent())
  {
    delete (flashComponent());
  }
  screen_warning = new FlashComponent(renderer, colour);
}

float AxePsycho::flashAimTime()
{
  return TIMER_AIM_FLASH;
}

float* AxePsycho::currentFlashTime()
{
  return &current_time_flash;
}

bool AxePsycho::isPaused()
{
  return is_paused;
}

void AxePsycho::isPaused(bool value)
{
  is_paused = value;
}
