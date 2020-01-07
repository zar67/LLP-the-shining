//
// Created by Ryan on 07/01/2020.
//

#ifndef THE_SHINING_GAME_GROUP_3_ITEMS_H
#define THE_SHINING_GAME_GROUP_3_ITEMS_H

#include "string"

class Items
{
 public:
  bool hasCollidedWithPlayer();
  void hasPickedUpItem();
  float itemEffect();

 private:
  bool visibility = true;
  std::string item_Name = "";
};

#endif // THE_SHINING_GAME_GROUP_3_ITEMS_H
