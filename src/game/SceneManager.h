//
// Created by Zoe on 10/01/2020.
//

#ifndef THE_SHINING_GAME_GROUP_3_SCENEMANAGER_H
#define THE_SHINING_GAME_GROUP_3_SCENEMANAGER_H

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

class SceneManager
{
 public:
  enum class MenuItem
  {
    NONE = -1,
    START_GAME = 1,
    OPEN_SHOP = 2,
    EXIT_GAME = 3,
    OPEN_MAIN_MENU = 4
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

  bool initialise(ASGE::Renderer* renderer, int game_width);
  void enableInput(ASGE::Input* input);
  void disableInput(ASGE::Input* input);
  MenuItem update(const ASGE::GameTime&);
  void render(ASGE::Renderer* renderer);
  ScreenOpen screenOpen();
  void screenOpen(ScreenOpen screen);

 private:
  bool isInside(ASGE::Sprite* btn, Point2D point) const;
  bool loadFonts(ASGE::Renderer* renderer);
  void mouseHandler(ASGE::SharedEventData data);
  void clickHandler(ASGE::SharedEventData data);

  MenuItem menuItem(const Point2D& mouse_pos);
  bool setupUIElement(ASGE::Sprite& sprite,
                      std::string texture,
                      float x_pos,
                      float y_pos,
                      float width,
                      float height);

  void setOpacity(float start, float shop, float exit, float menu);

  std::atomic<MenuItem> mouse_over{ MenuItem::NONE };
  std::atomic<MenuItem> mouse_click{ MenuItem::NONE };

  ASGE::Sprite* menu_title = nullptr;
  ASGE::Sprite* game_over_title = nullptr;
  ASGE::Sprite* start_game = nullptr;
  ASGE::Sprite* open_shop = nullptr;
  ASGE::Sprite* exit_game = nullptr;
  ASGE::Sprite* open_main_menu = nullptr;
  ASGE::Sprite* cursor = nullptr;

  ScreenOpen screen_open = MAIN_MENU;
  int menu_font_index = -1;
  int mouse_handler_idx = -1;
  int mouse_click_handle = -1;
};

#endif // THE_SHINING_GAME_GROUP_3_SCENEMANAGER_H
