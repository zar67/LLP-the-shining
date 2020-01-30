//
// Created by l4-neale on 28/01/2020.
//

#include "FlashComponent.h"

/**
 *   @brief   Constructor
 *   @details Sets up the sprite component for the flashing
 *   @param   renderer The ASGE renderer
 *            colour The colour to flash
 *            game_width The width of the game screen
 *            game_height The height of the game screen
 */
FlashComponent::FlashComponent(ASGE::Renderer* renderer,
                               ASGE::Colour colour,
                               float game_width,
                               float game_height)
{
  addSpriteComponent(renderer, "/data/white.png");
  spriteComponent()->getSprite()->colour(colour);
  spriteComponent()->getSprite()->xPos(0);
  spriteComponent()->getSprite()->yPos(0);
  spriteComponent()->getSprite()->width(game_width);
  spriteComponent()->getSprite()->height(game_height);
}

/**
 *   @brief   Gets visible attribute
 *   @return  is_visible
 */
bool FlashComponent::isVisible()
{
  return is_visible;
}

/**
 *   @brief   Inverts the visible attribute
 */
void FlashComponent::reverseIsVisible()
{
  is_visible = !is_visible;
}

/**
 *   @brief   Flashes the sprite on and off
 *   @details Updates the flashing and turns off if the timer has ran out
 *   @return  True if stopped flashing
 */
bool FlashComponent::flash(float delta_time)
{
  if (current_count < WARNING_COUNT)
  {
    current_wait += delta_time;
    if (current_wait > WAIT_TIME)
    {
      reverseIsVisible();
      current_wait = 0;
      current_count++;
    }
    return false;
  }

  current_count = 0;
  current_wait = 0;
  is_visible = false;
  isFlashing(false);
  return true;
}

/**
 *   @brief   Gets if the sprite is flashing
 *   @return  is_flashing
 */
bool FlashComponent::isFlashing()
{
  return is_flashing;
}

/**
 *   @brief   Sets if the sprite is flashing
 *   @param   value New flashing value
 */
void FlashComponent::isFlashing(bool value)
{
  is_flashing = value;
}
