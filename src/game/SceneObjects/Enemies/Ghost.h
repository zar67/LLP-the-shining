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
  ~Ghost() = default;

  bool setup(ASGE::Renderer* renderer, float x_pos, float y_pos) override;
  void update(double delta_time,
              std::vector<InteractableObjects*>& objects,
              bool doors[4]);

  GameObject* grabClosestObject(std::vector<InteractableObjects*> objects);
  void getMoveToDoor(const bool doors[4], float (&out_pos)[2]);

 private:
  GameObject* obj_grabbed = nullptr;
  float door_pos[2] = { 0.0f, 0.0f }; // door object grabbed moving to
  std::vector<float> direction;       // direction for object to door
  int jedi_force_speed = 70;          // speed of moving object
};

#endif // THE_SHINING_GAME_GROUP_3_GHOST_H
