//
// Created by Zoe on 08/01/2020.
//

#ifndef THE_SHINING_GAME_GROUP_3_ENEMY_H
#define THE_SHINING_GAME_GROUP_3_ENEMY_H

#include "../GameObject.h"
#include "../Player.h"

class Enemy : public GameObject
{
 public:
  Enemy() = default;
  ~Enemy() = default;

  int health();
  int attackDamage();
  int moveSpeed();
  bool isAlive();
  void isAlive(bool value);

  virtual void update(double delta_time, float player_x, float player_y){};
  virtual bool setup(ASGE::Renderer* renderer, float x_pos, float y_pos){};
  virtual void render(ASGE::Renderer* renderer);
  bool takeDamage(int hit);

 protected:
  bool is_alive = true;
  int hp = 0;
  int damage = 0;
  float speed = 0;
};

#endif // THE_SHINING_GAME_GROUP_3_ENEMY_H
