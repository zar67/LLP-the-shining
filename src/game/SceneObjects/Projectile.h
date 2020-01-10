//
// Created by Zoe on 09/01/2020.
//

#ifndef THE_SHINING_GAME_GROUP_3_PROJECTILE_H
#define THE_SHINING_GAME_GROUP_3_PROJECTILE_H

#include "GameObject.h"

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
  int speed;
  int target[2];
};

#endif // THE_SHINING_GAME_GROUP_3_PROJECTILE_H
