//
// Created by Zoe on 10/01/2020.
//

#include "AxePsycho.h"

#include <iostream>

/**
 *   @brief   Destructor
 *   @details Frees the flash component
 */
AxePsycho::~AxePsycho()
{
  if (screen_warning)
  {
    delete (screen_warning);
    screen_warning = nullptr;
  }
}

/**
 *   @brief   Sets up the axe psycho
 *   @details Sets the default values and adds the relevant components
 *   @param   renderer The ASGE Renderer
 *            x_pos The starting x position
 *            y_pos The starting y position
 *            width The width to set to the sprite
 *            height The height to set to the sprite
 *            game_width The width of the game screen
 *            game_height The height of the game screen
 *   @return  True if setup correctly
 */
bool AxePsycho::setup(ASGE::Renderer* renderer,
                      float x_pos,
                      float y_pos,
                      float width,
                      float height,
                      float game_width,
                      float game_height)
{
  hp = START_HP;
  damage = 25;
  speed = 110;
  in_room = false;

  addFlashComponent(renderer, ASGE::COLOURS::RED, game_width, game_height);
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

/**
 *   @brief   Updates the axe psycho
 *   @details Moves towards the player and tries to attack, if health is low
 * retreats and dissappears
 *   @param   player_x The x position of the player
 *            player_y The y position of the player
 */
void AxePsycho::update(double delta_time, float player_x, float player_y)
{
  // Move Towards Player if not killed
  if (in_room)
  {
    if (is_paused)
    {
      is_paused = !spawnTimerEnd(delta_time, PAUSE_TIME, current_pause_time);
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

/**
 *   @brief   Gets if the psycho is in the current room
 *   @return  in_room
 */
bool AxePsycho::inRoom()
{
  return in_room;
}

/**
 *   @brief   Sets if the psycho is in the current room
 *   @param   value The new value to set to in_room
 */
void AxePsycho::inRoom(bool value)
{
  in_room = value;
}

/**
 *   @brief   Determines if the spawn timer has ended
 *   @param   timer_aim The time when the timer runs out
 *            current_time The time elapsed so far
 *   @return  True if timer has ran out
 */
bool AxePsycho::spawnTimerEnd(double delta_time,
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

/**
 *   @brief   Sets the location the psycho was spawned at
 *   @param   x_pos The x position
 *            y_pos The y position
 */
void AxePsycho::setSpawnedLocation(float x_pos, float y_pos)
{
  spawned_x = x_pos;
  spawned_y = y_pos;
}

/**
 *   @brief   Gets the flash component
 *   @return  screen_warning
 */
FlashComponent* AxePsycho::flashComponent()
{
  return screen_warning;
}

/**
 *   @brief   Gets if the axe psycho is dead
 *   @return  is_killed
 */
bool AxePsycho::isKilled()
{
  return is_killed;
}

/**
 *   @brief   Sets if the axe psycho is dead
 *   @param   value The new value
 */
void AxePsycho::isKilled(bool value)
{
  is_killed = value;
}

/**
 *   @brief   Adds a flash component
 *   @param   renderer The ASGE renderer
 *            colour The colour to flash
 *            game_width The width of the game screen
 *            game_height The height of the game screen
 */
void AxePsycho::addFlashComponent(ASGE::Renderer* renderer,
                                  ASGE::Colour colour,
                                  float game_width,
                                  float game_height)
{
  if (flashComponent())
  {
    delete (flashComponent());
  }
  screen_warning =
    new FlashComponent(renderer, colour, game_width, game_height);
}

/**
 *   @brief   Gets the amount of time to flash for
 *   @return  TIMER_AIM_FLASH
 */
float AxePsycho::flashAimTime()
{
  return TIMER_AIM_FLASH;
}

/**
 *   @brief   Gets a pointer to the current elapsed time
 *   @return  current_time_flash
 */
float* AxePsycho::currentFlashTime()
{
  return &current_time_flash;
}

/**
 *   @brief   Gets if the spawning for axe psycho is paused
 *   @return  is_paused
 */
bool AxePsycho::isPaused()
{
  return is_paused;
}

/**
 *   @brief   Setrs if the spawning for the axe psycho is paused
 *   @param   value The new value
 */
void AxePsycho::isPaused(bool value)
{
  is_paused = value;
}
