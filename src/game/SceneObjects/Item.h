//
// Created by Ryan on 07/01/2020.
//

#ifndef THE_SHINING_GAME_GROUP_3_ITEM_H
#define THE_SHINING_GAME_GROUP_3_ITEM_H

#include "GameObject.h"
#include "Player.h"
#include "string"
#include <Engine/FileIO.h>
#include <Engine/OGLGame.h>
#include <soloud.h>
#include <soloud_wav.h>

class Item : public GameObject
{
 public:
  enum GameItems
  {
    NONE,
    STAIRCASE,
    COIN,
    HEART
  };

 public:
  Item() = default;
  ~Item() = default;

  bool hasCollidedWithPlayer(Player* player);
  void hasPickedUpItem();
  GameItems itemType();

  bool setUpItem(ASGE::Renderer* renderer,
                 std::string filename,
                 GameItems item_type,
                 float x_pos,
                 float y_pos);
  void renderItem(ASGE::Renderer* renderer);

 private:
  bool visibility = true;
  GameItems item = NONE;
};

#endif // THE_SHINING_GAME_GROUP_3_ITEM_H
