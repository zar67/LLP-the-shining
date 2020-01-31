//
// Created by Zoe on 12/01/2020.
//

#ifndef THE_SHINING_GAME_GROUP_3_MAINMENU_H
#define THE_SHINING_GAME_GROUP_3_MAINMENU_H

#include "../Scene.h"

class MainMenu : public Scene
{
 public:
  enum class MenuItem
  {
    NONE = -1,
    START_GAME = 1,
    OPEN_SHOP = 2,
    EXIT_GAME = 3,
    SPLASH_SCREEN_ENDED = 4
  };

 public:
  MainMenu() = default;
  ~MainMenu();

  bool init(ASGE::Renderer* renderer, float game_width, float game_height);
  MenuItem update(float delta_time, Point2D point);
  void render(ASGE::Renderer* renderer) override;

  bool inSplashScreen();
  void setSplashScreen(bool value);

 private:
  MenuItem menuItem(Point2D point);
  void resetOpacity() override;

  // Sprites
  ASGE::Sprite* menu_title = nullptr;
  ASGE::Sprite* start_game = nullptr;
  ASGE::Sprite* open_shop = nullptr;
  ASGE::Sprite* exit_game = nullptr;

  ASGE::Sprite* splash_screen = nullptr;
  bool in_splash_screen = false;
  float splash_screen_duration = 8;
  float splash_screen_timer = 0;
};

#endif // THE_SHINING_GAME_GROUP_3_MAINMENU_H
