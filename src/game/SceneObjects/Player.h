//
// Created by Owner on 17/12/2019.
//

#ifndef PROJECT_PLAYER_H
#define PROJECT_PLAYER_H

#include <vector>

#include "GameObject.h"

class Player : public GameObject
{
 public:
  void init(ASGE::Renderer* renderer,
            std::string tex_directory,
            float x_pos,
            float y_pos,
            float width,
            float height);
  void Movement(float x, float y);
  void Movement(float delta_time);
  void takeDamage(int hit_damage); // maybe pass enemie as different demons do
                                   // different damage

  void setMovementVec(float vec[2]);

 private:
  int speed = 50;
  int health = 100;
  int damage = 20;
  float vector_movement[2] = { 0.0f, 0.0f };

  std::vector<int> abilities;
};

#endif // PROJECT_PLAYER_H
