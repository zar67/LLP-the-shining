#pragma once
#include "../map/Map.h"
#include "SceneObjects/Enemies/Demon.h"
#include "UIHandler/SceneManager.h"

#include <Engine/OGLGame.h>
#include <string>
#include <vector>

const int MAX_FLOOR = 3;

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
  void keyHandler(ASGE::SharedEventData data);
  void clickHandler(ASGE::SharedEventData data);
  void setupResolution();

  void update(const ASGE::GameTime&) override;
  void render(const ASGE::GameTime&) override;

  SceneManager scene_handler;
  Map map = Map();

  int floor = 0;

  float player_x = 500;
  float player_y = 300;

  int key_callback_id = -1;   /**< Key Input Callback ID. */
  int mouse_callback_id = -1; /**< Mouse Input Callback ID. */
};