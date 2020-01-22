//
// Created by Zoe on 08/01/2020.
//

#ifndef THE_SHINING_GAME_GROUP_3_DEMON_H
#define THE_SHINING_GAME_GROUP_3_DEMON_H

#include "../InteractableObjects.h"
#include "../Player.h"
#include "Enemy.h"
#include <vector>

class Demon : public Enemy
{
 public:
  Demon() = default;
  ~Demon();

  bool setup(ASGE::Renderer* renderer, float x_pos, float y_pos) override;
  void update(ASGE::Renderer* renderer,
              double delta_time,
              Player* player,
              std::vector<InteractableObjects*> scene_objects);
  void render(ASGE::Renderer* renderer) override;

  bool addWeaponComponent();
  ShootingComponent* weaponComponent();

 private:
  float distance_to_keep = 100;

  double shoot_timer = 0;
  float shoot_delay = 2;

  ShootingComponent* weapon_component = nullptr;
};

#endif // THE_SHINING_GAME_GROUP_3_DEMON_H
