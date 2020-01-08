//
// Created by Zoe on 08/01/2020.
//

#ifndef THE_SHINING_GAME_GROUP_3_DEMON_H
#define THE_SHINING_GAME_GROUP_3_DEMON_H

#include "Enemy.h"
#include <vector>

class Demon : public Enemy
{
 public:
  Demon() = default;
  ~Demon() = default;

  bool setup(ASGE::Renderer* renderer, float x_pos, float y_pos) override;
  void update(double delta_time, float player_x, float player_y) override;

  std::vector<float> getDirectionToPlayer(float player_x, float player_y);
  float getDistanceToPlayer(float player_x, float player_y);

 private:
  float distance_to_keep = 200;
};

#endif // THE_SHINING_GAME_GROUP_3_DEMON_H
