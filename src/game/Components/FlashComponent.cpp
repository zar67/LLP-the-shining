//
// Created by l4-neale on 28/01/2020.
//

#include "FlashComponent.h"

FlashComponent::FlashComponent(ASGE::Renderer* renderer, ASGE::Colour colour)
{
  addSpriteComponent(renderer, "/data/white.png");
  spriteComponent()->getSprite()->colour(colour);
  spriteComponent()->getSprite()->xPos(0);
  spriteComponent()->getSprite()->yPos(0);
  spriteComponent()->getSprite()->width(800);
  spriteComponent()->getSprite()->height(1200);
}

void FlashComponent::incrementCount()
{
  current_count++;
}

void FlashComponent::resetCount()
{
  current_count = 0;
}

bool FlashComponent::checkCount()
{
  return current_count == WARNING_COUNT;
}

bool FlashComponent::isVisible()
{
  return is_visible;
}

void FlashComponent::reverseIsVisible()
{
  is_visible = !is_visible;
}

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

bool FlashComponent::isFlashing()
{
  return is_flashing;
}

void FlashComponent::isFlashing(bool value)
{
  is_flashing = value;
}
