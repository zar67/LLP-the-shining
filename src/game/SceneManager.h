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
    OPEN_MAIN_MENU = 4,
    DAMAGE_POWERUP = 5,
    HEALTH_POWERUP = 6,
    MOVE_SPEED_POWERUP = 7,
    SHOT_SIZE_POWERUP = 8,
    SHOT_SPEED_POWERUP = 9
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

  bool
  initSprites(ASGE::Renderer* renderer, float game_width, float game_height);
  bool
  initButtons(ASGE::Renderer* renderer, float game_width, float game_height);
  bool initShop(ASGE::Renderer* renderer, float game_height);
  bool
  initialise(ASGE::Renderer* renderer, float game_width, float game_height);
  void enableInput(ASGE::Input* input);
  void disableInput(ASGE::Input* input);
  MenuItem update(const ASGE::GameTime&);
  void render(ASGE::Renderer* renderer, int floor, int coins, int health);
  ScreenOpen screenOpen();
  void screenOpen(ScreenOpen screen);

 private:
  bool isInside(ASGE::Sprite* btn, Point2D point) const;
  bool loadFonts(ASGE::Renderer* renderer);
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
  ASGE::Sprite* menu_title = nullptr;
  ASGE::Sprite* game_over_title = nullptr;
  ASGE::Sprite* shop_title = nullptr;
  ASGE::Sprite* health_bar = nullptr;
  ASGE::Sprite* health_bar_background = nullptr;

  // Power Up Icons
  ASGE::Sprite* damage_icon = nullptr;
  ASGE::Sprite* health_icon = nullptr;
  ASGE::Sprite* move_speed_icon = nullptr;
  ASGE::Sprite* shot_size_icon = nullptr;
  ASGE::Sprite* shot_speed_icon = nullptr;

  // Shop Power Ups
  ASGE::Sprite* damage_powerup = nullptr;
  ASGE::Sprite* health_powerup = nullptr;
  ASGE::Sprite* move_speed_powerup = nullptr;
  ASGE::Sprite* shot_size_powerup = nullptr;
  ASGE::Sprite* shot_speed_powerup = nullptr;

  // Buttons
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
