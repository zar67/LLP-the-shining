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
  ~AxePsycho();

  bool setup(ASGE::Renderer* renderer,
             float x_pos,
             float y_pos,
             float width,
             float height,
             float game_width,
             float game_height);
  void update(double delta_time, float player_x, float player_y) override;

  bool inRoom();
  void inRoom(bool value);

  static bool
  spawnTimerEnd(double delta_time, float timer_aim, float& current_time);
  void setSpawnedLocation(float x_pos, float y_pos);

  FlashComponent* flashComponent();
  void addFlashComponent(ASGE::Renderer* renderer,
                         ASGE::Colour colour,
                         float game_width,
                         float game_height);

  bool isKilled();
  void isKilled(bool value);

  float flashAimTime();
  float* currentFlashTime();
  bool isPaused();
  void isPaused(bool value);

 private:
  bool is_killed = false;
  bool in_room = false;
  const float TIMER_AIM_FLASH = 1.5f;
  float current_time_flash = 0.0f;

  const int START_HP = 500;
  const float PAUSE_TIME = 1.5f;
  float current_pause_time = 0.0f;
  bool is_paused = false;

  float spawned_x = 0.0f;
  float spawned_y = 0.0f;

  float quick_speed = 250.0f;

  FlashComponent* screen_warning = nullptr;
};

#endif // THE_SHINING_GAME_GROUP_3_AXEPSYCHO_H
