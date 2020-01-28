//
// Created by Zoe on 10/01/2020.
//

#ifndef THE_SHINING_GAME_GROUP_3_AXEPSYCHO_H
#define THE_SHINING_GAME_GROUP_3_AXEPSYCHO_H

#include "../../Components/FlashComponent.h"
#include "Enemy.h"

class AxePsycho : public Enemy
{
 public:
  AxePsycho() = default;
  ~AxePsycho() = default;

  bool setup(ASGE::Renderer* renderer,
             float x_pos,
             float y_pos,
             float width,
             float height);
  void update(double delta_time, float player_x, float player_y) override;

  bool inRoom();
  void inRoom(bool value);

  bool spawnTimerEnd(float delta_time);
  void setSpawnedLocation(float x, float y);

  FlashComponent* flashComponent();

  bool isKilled();
  void isKilled(bool value);

 private:
  bool is_killed = false;
  bool in_room = false;
  float timer_aim = 1.5f;
  float current_time = 0.0f;

  const int START_HP = 500;

  float spawned_x = 0.0f;
  float spawned_y = 0.0f;

  FlashComponent* screen_warning = nullptr;
};

#endif // THE_SHINING_GAME_GROUP_3_AXEPSYCHO_H
