//
// Created by Zoe on 09/01/2020.
//

#ifndef THE_SHINING_GAME_GROUP_3_GHOST_H
#define THE_SHINING_GAME_GROUP_3_GHOST_H

#include "Enemy.h"

class Ghost : public Enemy
{
 public:
  Ghost() = default;
  ~Ghost() = default;

  bool setup(ASGE::Renderer* renderer, float x_pos, float y_pos) override;
  void update(double delta_time, float player_x, float player_y) override;

 private:
};

#endif // THE_SHINING_GAME_GROUP_3_GHOST_H
