//
// Created by Owner on 17/12/2019.
//
#ifndef PROJECT_GAMEOBJECT_H
#define PROJECT_GAMEOBJECT_H

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

 private:
  SpriteComponent* sprite_component = nullptr;
  CollisionComponent* collision_component = nullptr;
};

#endif // PROJECT_GAMEOBJECT_H
