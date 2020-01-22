//
// Created by Owner on 17/12/2019.
//
#ifndef PROJECT_GAMEOBJECT_H
#define PROJECT_GAMEOBJECT_H

#include <tuple>
#include <vector>

#include "../Components/CollisionComponent.h"
#include "../Components/SpriteComponent.h"

class GameObject
{
 public:
  GameObject() = default;
  ~GameObject();

  bool
  addSpriteComponent(ASGE::Renderer* renderer, std::string texture_location);
  SpriteComponent* spriteComponent();

  void addCollisionComponent();
  CollisionComponent* collisionComponent();

  void updateCollisionComponent();
  void move(double delta_time, float x_dir, float y_dir, float speed);
  std::vector<float>
  getDirectionFromTo(float from_x, float from_y, float to_x, float to_y);
  float getDistanceBetween(float from_x, float from_y, float to_x, float to_y);

 protected:
  SpriteComponent* sprite_component = nullptr;
  CollisionComponent* collision_component = nullptr;
};

#endif // PROJECT_GAMEOBJECT_H
