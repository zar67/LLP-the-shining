//
// Created by Owner on 17/12/2019.
//

#ifndef PROJECT_PLAYER_H
#define PROJECT_PLAYER_H

#include <Engine/InputEvents.h>
#include <vector>

#include "../Components/ShootingComponent.h"
#include "GameObject.h"
class Player : public GameObject
{
 public:
  Player() = default;
  void init(ASGE::Renderer* renderer,
            std::string tex_directory,
            float x_pos,
            float y_pos,
            float width,
            float height);
  void Movement(float x, float y);
  void Movement(float delta_time, std::vector<GameObject*> enemies);
  void takeDamage(int hit_damage); // maybe pass enemie as different demons do
                                   // different damage

  void moveVertical(float move);
  void moveHorizontal(float move);

  void setMovementVec(float vec[2]);
  float* getDirectionVector();

  bool addWeaponCompononet();
  ShootingComponent* weaponComponent();

 private:
  int speed = 100;
  int health = 100;
  int damage = 20;
  float input_vector[2] = { 0.0f, 0.0f };
  float vector_movement[2] = { 0.0f, 0.0f };

  std::vector<int> abilities;
  ShootingComponent* weapon_component = nullptr;
};

#endif // PROJECT_PLAYER_H
