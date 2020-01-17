//
// Created by Ryan on 07/01/2020.
//

#ifndef THE_SHINING_GAME_GROUP_3_ITEMS_H
#define THE_SHINING_GAME_GROUP_3_ITEMS_H

#include "GameObject.h"
#include "string"
#include <Engine/OGLGame.h>

class Items : GameObject
{
 public:
  bool hasCollidedWithPlayer();
  void hasPickedUpItem();
  float itemEffect();
  bool setUpItems(ASGE::Renderer* renderer);
  void renderItem(ASGE::Renderer* renderer);

 private:
  bool visibility = true;
  GameObject Item;
  std::string item_Name = "";
};

#endif // THE_SHINING_GAME_GROUP_3_ITEMS_H
