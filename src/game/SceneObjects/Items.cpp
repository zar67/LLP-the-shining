//
// Created by Ryan on 07/01/2020.
//

#include "Items.h"
#include "../Components/CollisionComponent.h"
#include <Engine/OGLGame.h>

bool Items::hasCollidedWithPlayer()
{
  return false;
}
void Items::hasPickedUpItem()
{
  visibility = false;
}
float Items::itemEffect()
{
  // check if the item has been picked up
  // if it has then apply the items effect eg damage up or health up etc
  return 0;
}
bool Items::setUpItems(ASGE::Renderer* renderer)
{
  // set up all the items
  Item.addSpriteComponent(renderer, "data/Items/Item1.PNG");
  Item.spriteComponent()->getSprite()->width(32);
  Item.spriteComponent()->getSprite()->height(32);

  return true;
}
void Items::renderItem(ASGE::Renderer* renderer)
{
  renderer->renderSprite(*Item.spriteComponent()->getSprite());
}