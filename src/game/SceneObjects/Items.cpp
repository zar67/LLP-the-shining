//
// Created by Ryan on 07/01/2020.
//

#include "Items.h"
bool Items::hasCollidedWithPlayer()
{
  // has the player collided with the item
  // if yes return true

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