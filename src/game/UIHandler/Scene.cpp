//
// Created by Zoe on 12/01/2020.
//

#include "Scene.h"

/**
 *   @brief   Sets up a sprite in the scene
 *   @param   sprite The sprite to setup
 *            texture The location of the texture to load
 *            x_pos The starting y position
 *            y_pos The starting y position
 *            width The width to set
 *            height The height to set
 *   @return  True if setup correctly
 */
bool Scene::setupSprite(ASGE::Sprite& sprite,
                        const std::string& texture,
                        float x_pos,
                        float y_pos,
                        float width,
                        float height)
{
  if (sprite.loadTexture(texture))
  {
    sprite.xPos(x_pos);
    sprite.yPos(y_pos);
    sprite.width(width);
    sprite.height(height);
    return true;
  }

  return false;
}

/**
 *   @brief   Calculates if the position is inside the ui element
 *   @param   btn The button
 *            point The point to check if inside button
 *   @return  True is point is inside button
 */
bool Scene::isInside(ASGE::Sprite* btn, Point2D point)
{
  auto bbox = btn->getGlobalBounds();

  return point.x >= bbox.v1.x && point.x <= bbox.v2.x && point.y >= bbox.v1.y &&
         point.y <= bbox.v3.y;
}
