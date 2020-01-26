//
// Created by Zoe on 10/01/2020.
//

#ifndef THE_SHINING_GAME_GROUP_3_AXEPSYCHO_H
#define THE_SHINING_GAME_GROUP_3_AXEPSYCHO_H

#include "Enemy.h"

class AxePsycho : public Enemy
{
 public:
  AxePsycho() = default;
  ~AxePsycho() = default;

  bool setup(ASGE::Renderer* renderer,
             float x_pos,
             float y_pos,
             float width,
             float height);
  void update(double delta_time, float player_x, float player_y) override;

  bool inRoom();
  void inRoom(bool value);

 private:
  bool in_room = false;
};

#endif // THE_SHINING_GAME_GROUP_3_AXEPSYCHO_H
