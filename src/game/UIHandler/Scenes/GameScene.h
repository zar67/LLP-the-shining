//
// Created by Zoe on 13/01/2020.
//

#ifndef THE_SHINING_GAME_GROUP_3_GAMESCENE_H
#define THE_SHINING_GAME_GROUP_3_GAMESCENE_H

#include "../Scene.h"

class GameScene : public Scene
{
 public:
  GameScene() = default;
  ~GameScene();

  bool init(ASGE::Renderer* renderer, float game_width, float game_height);
  bool update(float delta_time);
  void render(ASGE::Renderer* renderer,
              int floor,
              int coins,
              int health,
              const bool* abilities);

  void setSplashScreen(bool value);

 private:
  ASGE::Sprite* health_bar = nullptr;
  ASGE::Sprite* health_bar_background = nullptr;
  ASGE::Sprite* damage_powerup_icon = nullptr;
  ASGE::Sprite* health_powerup_icon = nullptr;
  ASGE::Sprite* move_speed_powerup_icon = nullptr;
  ASGE::Sprite* shot_size_powerup_icon = nullptr;
  ASGE::Sprite* shot_speed_powerup_icon = nullptr;

  ASGE::Sprite* splash_screen = nullptr;
  bool in_splash_screen = false;
  float splash_screen_duration = 3;
  float splash_screen_timer = 0;
};

#endif // THE_SHINING_GAME_GROUP_3_GAMESCENE_H
