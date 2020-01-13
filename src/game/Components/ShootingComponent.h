//
// Created by Owner on 13/01/2020.
//

#ifndef PROJECT_SHOOTINGCOMPONENT_H
#define PROJECT_SHOOTINGCOMPONENT_H

#include "../SceneObjects/Projectile.h"
#include <vector>

//  Forward declare
// class Projectile;

class ShootingComponent
{
 public:
  ShootingComponent();

  void Fire(ASGE::Renderer* renderer, float player_x, float player_y);
  void maintainProjectiles(float delta_time);
  void render(ASGE::Renderer* renderer);

  void setLastDirection(float x, float y);
  void setSpeed(int value);
  // std::vector<Projectile> getProjectiles();
 private:
  int speed = 500;
  std::vector<Projectile*> projectiles;
  Projectile* p = nullptr;

  std::vector<float> last_direction;
};

#endif // PROJECT_SHOOTINGCOMPONENT_H
