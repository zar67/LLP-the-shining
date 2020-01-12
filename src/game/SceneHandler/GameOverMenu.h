//
// Created by Zoe on 12/01/2020.
//

#ifndef THE_SHINING_GAME_GROUP_3_GAMEOVERMENU_H
#define THE_SHINING_GAME_GROUP_3_GAMEOVERMENU_H

#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Point2D.h>
#include <atomic>

namespace ASGE
{
class GameTime;
class Renderer;
class Sprite;
}

class GameOverMenu
{
 public:
  enum class MenuItem
  {
    NONE = -1,
    START_GAME = 1,
    OPEN_SHOP = 2,
    OPEN_MENU = 3,
    EXIT_GAME = 4
  };

 public:
  GameOverMenu() = default;
  ~GameOverMenu();

  bool initialise(ASGE::Input* input,
                  ASGE::Renderer* renderer,
                  float game_width,
                  float game_height);
  void enableInput(ASGE::Input* input);
  void disableInput(ASGE::Input* input);
  MenuItem update(const ASGE::GameTime&);
  void render(ASGE::Renderer* renderer);

 private:
  bool isInside(ASGE::Sprite* btn, Point2D point) const;
  void mouseHandler(ASGE::SharedEventData data);
  void clickHandler(ASGE::SharedEventData data);

  MenuItem menuItem(const Point2D& mouse_pos);
  bool setupSprite(ASGE::Sprite& sprite,
                   std::string texture,
                   float x_pos,
                   float y_pos,
                   float width,
                   float height);

  void resetOpacity();

  std::atomic<MenuItem> mouse_over{ MenuItem::NONE };
  std::atomic<MenuItem> mouse_click{ MenuItem::NONE };

  // Sprites
  ASGE::Sprite* game_over_title = nullptr;
  ASGE::Sprite* start_game = nullptr;
  ASGE::Sprite* open_shop = nullptr;
  ASGE::Sprite* exit_game = nullptr;
  ASGE::Sprite* open_main_menu = nullptr;

  int menu_font_index = -1;
  int mouse_handler_idx = -1;
  int mouse_click_handle = -1;
};

#endif // THE_SHINING_GAME_GROUP_3_GAMEOVERMENU_H
