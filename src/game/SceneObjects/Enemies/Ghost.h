//
// Created by Zoe on 09/01/2020.
//

#ifndef THE_SHINING_GAME_GROUP_3_GHOST_H
#define THE_SHINING_GAME_GROUP_3_GHOST_H

#include "../InteractableObjects.h"
#include "../Player.h"
#include "Enemy.h"

class Ghost : public Enemy
{
 public:
  Ghost() = default;
  ~Ghost();

  bool setup(ASGE::Renderer* renderer, float x_pos, float y_pos) override;
  void update(double delta_time,
              std::vector<InteractableObjects*>& objects,
              bool doors[4],
              int game_width,
              int game_height);

  InteractableObjects*
  grabClosestObject(std::vector<InteractableObjects*> objects);
  static void getMoveToDoor(const bool doors[4],
                            float (&out_pos)[2],
                            float game_width,
                            float game_height);

 private:
  InteractableObjects* obj_grabbed = nullptr;
  float door_pos[2] = { 0.0f, 0.0f }; // door object grabbed moving to
  std::vector<float> direction;       // direction for object to door

  float jedi_force_speed = 180; // speed of moving object
                                // speed of moving object

  float ghost_teleports_x[12] = { 100, 120, 240, 300, 360, 420,
                                  480, 560, 610, 700, 790, 890 };
  float ghost_teleports_y[12] = { 100, 140, 250, 210, 290, 320,
                                  350, 380, 410, 440, 500, 540 };
  double teleport_timer = 0;
};

#endif // THE_SHINING_GAME_GROUP_3_GHOST_H
