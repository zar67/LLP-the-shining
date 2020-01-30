//
// Created by l4-neale on 28/01/2020.
//

#ifndef THE_SHINING_GAME_GROUP_3_FLASHCOMPONENT_H
#define THE_SHINING_GAME_GROUP_3_FLASHCOMPONENT_H

#include "../SceneObjects/GameObject.h"
#include "SpriteComponent.h"

class FlashComponent : public GameObject
{
 public:
  FlashComponent(ASGE::Renderer* renderer,
                 ASGE::Colour colour,
                 float game_width,
                 float game_height);

  bool isVisible();
  void reverseIsVisible();

  bool isFlashing();
  void isFlashing(bool value);

  bool flash(float delta_time);

 private:
  const static int WARNING_COUNT = 10;
  int current_count = 0;
  bool is_visible = false;

  const float WAIT_TIME = 0.2f;
  float current_wait = 0.0f;

  bool is_flashing = false;
};

#endif // THE_SHINING_GAME_GROUP_3_FLASHCOMPONENT_H
