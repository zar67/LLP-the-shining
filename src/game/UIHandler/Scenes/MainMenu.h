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
    EXIT_GAME = 3
  };

 public:
  MainMenu() = default;
  ~MainMenu();

  bool init(ASGE::Renderer* renderer, float game_width);
  MenuItem update(Point2D point);
  void render(ASGE::Renderer* renderer) override;

 private:
  MenuItem menuItem(Point2D point);
  void resetOpacity() override;

  // Sprites
  ASGE::Sprite* menu_title = nullptr;
  ASGE::Sprite* start_game = nullptr;
  ASGE::Sprite* open_shop = nullptr;
  ASGE::Sprite* exit_game = nullptr;
};

#endif // THE_SHINING_GAME_GROUP_3_MAINMENU_H
