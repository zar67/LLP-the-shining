//
// Created by Zoe on 12/01/2020.
//

#include "Scene.h"

bool Scene::setupSprite(ASGE::Sprite& sprite,
                        std::string texture,
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

bool Scene::isInside(ASGE::Sprite* btn, Point2D point)
{
  auto bbox = btn->getGlobalBounds();

  return point.x >= bbox.v1.x && point.x <= bbox.v2.x && point.y >= bbox.v1.y &&
         point.y <= bbox.v3.y;
}
