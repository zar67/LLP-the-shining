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

  void Fire(ASGE::Renderer* renderer, float start_x, float start_y);
  void maintainProjectiles(double delta_time,
                           std::vector<GameObject*> colliders,
                           int damage);
  bool hitPlayer(double delta_time, GameObject* collider);
  void render(ASGE::Renderer* renderer);

  void setMoveDirection(float x_dir, float y_dir);
  void setSpeed(float value);
  void setSize(float value);

 private:
  float speed = 250.0f;
  float range = 200.0f;
  float size = 16;
  std::vector<Projectile*> projectiles;
  Projectile* p = nullptr;

  std::vector<float> move_direction;
};

#endif // PROJECT_SHOOTINGCOMPONENT_H
