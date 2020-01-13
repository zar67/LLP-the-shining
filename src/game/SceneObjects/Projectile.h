//
// Created by Zoe on 09/01/2020.
//

#ifndef THE_SHINING_GAME_GROUP_3_PROJECTILE_H
#define THE_SHINING_GAME_GROUP_3_PROJECTILE_H

#include "GameObject.h"
#include <Engine/Renderer.h>
#include <vector>

class Projectile : public GameObject
{
 public:
  Projectile() = default;
  ~Projectile() = default;

  void update(double delta_time);
  bool setup(ASGE::Renderer* renderer,
             float move_speed,
             float x_pos,
             float y_pos,
             float x_dir,
             float y_dir);

 private:
  int speed = 0;
  float target[2] = { 0.0f, 0.0f };
};

#endif // THE_SHINING_GAME_GROUP_3_PROJECTILE_H
