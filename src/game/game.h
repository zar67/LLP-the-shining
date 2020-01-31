#pragma once
#include "../map/Map.h"
#include "Components/AudioManager.h"
#include "SceneObjects/Enemies/AxePsycho.h"
#include "SceneObjects/Enemies/Demon.h"
#include "SceneObjects/Player.h"
#include "UIHandler/SceneManager.h"

#include <Engine/OGLGame.h>
#include <string>
#include <vector>

/**
 *  An OpenGL Game based on ASGE.
 */
class MyASGEGame : public ASGE::OGLGame
{
 public:
  MyASGEGame();
  ~MyASGEGame() final;
  bool init() override;

 private:
  void keyHandler(const ASGE::SharedEventData& data);
  void playerMovement(const ASGE::SharedEventData& data);
  void playerShooting(const ASGE::SharedEventData& data);
  void playerControllerInput(ASGE::Input* input);
  void setupResolution();

  void resetGame();
  void update(const ASGE::GameTime&) override;
  void render(const ASGE::GameTime&) override;

  SceneManager scene_handler;
  AudioManager audio_manager;
  Map map = Map();
  Player player = Player();

  int floor = 3;

  float last_shoot_dir[2] = { 0, 0 };
  bool controller_connected = false;
  bool shoot_pressed = true;

  int key_callback_id = -1; /**< Key Input Callback ID. */
};