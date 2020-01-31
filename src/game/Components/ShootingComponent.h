//
// Created by Owner on 13/01/2020.
//

#ifndef PROJECT_SHOOTINGCOMPONENT_H
#define PROJECT_SHOOTINGCOMPONENT_H

#include "../SceneObjects/InteractableObjects.h"
#include "../SceneObjects/Projectile.h"
#include "AudioManager.h"

#include <math.h>
#include <vector>

class ShootingComponent
{
 public:
  ShootingComponent(ASGE::Renderer* renderer, bool use_arrow = false);

  void Fire(ASGE::Renderer* renderer,
            float start_x,
            float start_y,
            float x_dir,
            float y_dir);
  void maintainProjectiles(AudioManager* audio,
                           double delta_time,
                           std::vector<GameObject*> colliders,
                           int damage);
  bool hitPlayer(double delta_time,
                 GameObject* collider,
                 std::vector<InteractableObjects*> scene_objects);
  void render(ASGE::Renderer* renderer);
  void reset();

  void setMoveDirection(float x_dir, float y_dir);
  void setSpeed(float value);
  void setSize(float value);

  bool addSpriteComponent(ASGE::Renderer* renderer,
                          const std::string& texture_location);
  SpriteComponent* spriteComponent();

  void arrow_control(float x_pos, float y_pos);

 private:
  float calcAngle(float x, float y);
  float speed = 350.0f;
  float range = 300.0f;
  float size = 8;
  std::vector<Projectile*> projectiles;
  std::vector<float> move_direction;

  float x_shoot = 0.0f;
  float y_shoot = 0.0f;
  float offset = 15.0f;

  SpriteComponent* sprite_component = nullptr;
};

#endif // PROJECT_SHOOTINGCOMPONENT_H
