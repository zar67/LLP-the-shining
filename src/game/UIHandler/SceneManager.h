//
// Created by Zoe on 12/01/2020.
//

#ifndef THE_SHINING_GAME_GROUP_3_SCENEMANAGER_H
#define THE_SHINING_GAME_GROUP_3_SCENEMANAGER_H

#include "GameOverMenu.h"
#include "GameScene.h"
#include "MainMenu.h"
#include "ShopMenu.h"
#include <Engine/GameTime.h>
#include <Engine/InputEvents.h>

class SceneManager
{
 public:
  enum class ReturnValue
  {
    NONE = -1,
    START_GAME = 1,
    EXIT_GAME = 2,
    BUY_DAMAGE_POWERUP = 3,
    BUY_HEALTH_POWERUP = 4,
    BUY_MOVE_SPEED_POWERUP = 5,
    BUY_SHOT_SIZE_POWERUP = 6,
    BUY_SHOT_SPEED_POWERUP = 7
  };

  enum ScreenOpen
  {
    MAIN_MENU,
    SHOP,
    GAME,
    GAME_OVER
  };

 public:
  SceneManager() = default;
  ~SceneManager();

  void enableInputs(ASGE::Input* input);
  void disableInputs(ASGE::Input* input);
  bool init(ASGE::Input* input,
            ASGE::Renderer* renderer,
            float game_width,
            float game_height);
  ReturnValue update(const ASGE::GameTime& game_time);
  void render(ASGE::Renderer* renderer,
              int floor,
              int coins,
              int health,
              bool (&abilities)[5]);

  ScreenOpen screenOpen();
  void screenOpen(ScreenOpen screen);

  void hideDamagePowerup();
  void hideHealthPowerup();
  void hideMoveSpeedPowerup();
  void hideShotSizePowerup();
  void hideShotSpeedPowerup();

 private:
  void mouseHandler(ASGE::SharedEventData data);
  void clickHandler(ASGE::SharedEventData data);

  MainMenu main_menu;
  GameScene game_scene;
  ShopMenu shop_menu;
  GameOverMenu game_over_menu;

  ASGE::Sprite* cursor = nullptr;

  ScreenOpen screen_open = MAIN_MENU;

  Point2D mouse_pos;
  bool mouse_click = false;
  int mouse_handler_idx = -1;
  int mouse_click_handle = -1;
};

#endif // THE_SHINING_GAME_GROUP_3_SCENEMANAGER_H
