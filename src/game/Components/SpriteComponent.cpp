//
// Created by Owner on 17/12/2019.
//

#include "SpriteComponent.h"
#include <iostream>

SpriteComponent::~SpriteComponent()
{
  if (sprite)
  {
    delete (sprite);
    sprite = nullptr;
  }
}

bool SpriteComponent::loadSpriteComponent(ASGE::Renderer* renderer,
                                          std::string texture_location)
{
  if (sprite)
  {
    delete (sprite);
  }

  sprite = renderer->createRawSprite();

  if (sprite->loadTexture(texture_location))
  {
    return true;
  }

  delete (sprite);
  sprite = nullptr;
  return false;
}

ASGE::Sprite* SpriteComponent::getSprite()
{
  return sprite;
}
