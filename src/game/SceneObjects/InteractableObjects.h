//
// Created by Owner on 22/01/2020.
//

#ifndef PROJECT_INTERACTABLEOBJECTS_H
#define PROJECT_INTERACTABLEOBJECTS_H

#include "Enemies/Enemy.h"
#include "GameObject.h"
class InteractableObjects : public Enemy // inherit from enemy
{
 public:
  InteractableObjects() = default;

  bool checkHealth(ASGE::Renderer* renderer);
  bool setup(ASGE::Renderer* renderer, float x_pos, float y_pos) override;

  void setIsGrabbed(bool value);
  bool isGrabbed();

 private:
  std::string secondary_texture = "data/Objects/crate3.png";
  float pos_x = 0.0f;
  float pos_y = 0.0f;
  bool is_grabbed = false;
};

#endif // PROJECT_INTERACTABLEOBJECTS_H
