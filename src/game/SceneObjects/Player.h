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
  ~Player();
  void init(ASGE::Renderer* renderer,
            std::string& tex_directory,
            float x_pos,
            float y_pos,
            float width,
            float height);
  void reset();
  void Movement(float x, float y);
  bool update(float delta_time, std::vector<GameObject*> enemies);
  void takeDamage(int hit_damage); // maybe pass enemie as different demons do
                                   // different damage

  void moveVertical(float move);
  void moveHorizontal(float move);
  void setMovementVec(float vec[2]);
  float* getDirectionVector();

  bool addWeaponComponent();
  ShootingComponent* weaponComponent();

  bool addDamagePowerup();
  bool addHealthPowerup();
  bool addMoveSpeedPowerup();
  bool addShotSizePowerup();
  bool addShotSpeedPowerup();
  bool* getPowerups();

  void addCoins(int amount);
  int getCoins();
  int getHealth();

 private:
  bool addPowerup(int index);

  int coins = 100;
  float speed = 100;
  int health = 100;
  int damage = 20;
  float input_vector[2] = { 0.0f, 0.0f };
  float vector_movement[2] = { 0.0f, 0.0f };

  bool powerups[5] = { false, false, false, false, false };
  ShootingComponent* weapon_component = nullptr;

  const int damage_powerup_index = 0;
  const int health_powerup_index = 1;
  const int move_speed_powerup_index = 2;
  const int shot_size_powerup_index = 3;
  const int shot_speed_powerup_index = 4;

  const int starting_health = 100;
};

#endif // PROJECT_PLAYER_H
