//
// Created by Ryan on 07/01/2020.
//

#include "Item.h"
#include "../Components/CollisionComponent.h"
#include <Engine/OGLGame.h>

#include <utility>

bool Item::hasCollidedWithPlayer(Player* player)
{
  updateCollisionComponent();
  return (player->collisionComponent()->hasCollided(*collisionComponent()) ||
          collisionComponent()->hasCollided(*player->collisionComponent())) &&
         visibility;
}
void Item::hasPickedUpItem()
{
  visibility = false;
}

Item::GameItems Item::itemType()
{
  return item;
}

bool Item::setUpItem(ASGE::Renderer* renderer,
                     std::string filename,
                     GameItems item_type,
                     float x_pos,
                     float y_pos)
{
  item = item_type;

  addSpriteComponent(renderer, std::move(filename));
  sprite_component->getSprite()->xPos(x_pos);
  sprite_component->getSprite()->yPos(y_pos);

  addCollisionComponent();
  updateCollisionComponent();

  return true;
}

void Item::renderItem(ASGE::Renderer* renderer)
{
  if (visibility)
  {
    renderer->renderSprite(*spriteComponent()->getSprite());
  }
}