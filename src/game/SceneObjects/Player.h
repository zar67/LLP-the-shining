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
  void Movement(float x, float y);
  void takeDamage(int hit_damage); // maybe pass enemie as different enemies do
                                   // different damages

 private:
  int speed = 0;
  int health = 100;
  int damage = 20;

  std::vector<int> abilities;
};

#endif // PROJECT_PLAYER_H
