//
// Created by Zoe on 13/01/2020.
//

#ifndef THE_SHINING_GAME_GROUP_3_GAMEOVER_H
#  define THE_SHINING_GAME_GROUP_3_GAMEOVERMENU_H

#  include "Scene.h"

class GameOverMenu : public Scene
{
 public:
  enum class MenuItem
  {
    NONE = -1,
    START_GAME = 1,
    OPEN_SHOP = 2,
    MAIN_MENU = 3,
    EXIT_GAME = 4
  };

 public:
  GameOverMenu() = default;
  ~GameOverMenu();

  bool
  init(ASGE::Renderer* renderer, float game_width, float game_height) override;
  MenuItem update(Point2D point);
  void render(ASGE::Renderer* renderer) override;

 private:
  MenuItem menuItem(Point2D point);
  void resetOpacity() override;

  // Sprites
  ASGE::Sprite* game_over_title = nullptr;
  ASGE::Sprite* start_game = nullptr;
  ASGE::Sprite* open_shop = nullptr;
  ASGE::Sprite* open_menu = nullptr;
  ASGE::Sprite* exit_game = nullptr;
};

#endif // THE_SHINING_GAME_GROUP_3_GAMEOVER_H
