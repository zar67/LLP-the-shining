//
// Created by Owner on 17/12/2019.
//

#include "SpriteComponent.h"

/**
 *   @brief   Destructor
 *   @details Handles deleting the sprite
 */
SpriteComponent::~SpriteComponent()
{
  if (sprite)
  {
    delete (sprite);
    sprite = nullptr;
  }
}

/**
 *   @brief   Sets up the class
 *   @details Creates a raw sprite and gives it a texture
 *   @param   renderer The ASGE renderer
 *            texture_location The texture to load
 *   @return  True if initialised correctly
 */
bool SpriteComponent::loadSpriteComponent(ASGE::Renderer* renderer,
                                          const std::string& texture_location)
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

/**
 *   @brief   Gets the sprite
 *   @return  sprite
 */
ASGE::Sprite* SpriteComponent::getSprite()
{
  return sprite;
}
