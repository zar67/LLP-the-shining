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

  bool
  init(ASGE::Renderer* renderer, float game_width, float game_height) override;
  void render(ASGE::Renderer* renderer,
              int floor,
              int coins,
              int health,
              bool* abilities);

 private:
  ASGE::Sprite* health_bar = nullptr;
  ASGE::Sprite* health_bar_background = nullptr;
  ASGE::Sprite* damage_powerup_icon = nullptr;
  ASGE::Sprite* health_powerup_icon = nullptr;
  ASGE::Sprite* move_speed_powerup_icon = nullptr;
  ASGE::Sprite* shot_size_powerup_icon = nullptr;
  ASGE::Sprite* shot_speed_powerup_icon = nullptr;
};

#endif // THE_SHINING_GAME_GROUP_3_GAMESCENE_H
