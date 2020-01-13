//
// Created by Zoe on 12/01/2020.
//

#ifndef THE_SHINING_GAME_GROUP_3_SHOPMENU_H
#define THE_SHINING_GAME_GROUP_3_SHOPMENU_H

#include "Scene.h"

class ShopMenu : public Scene
{
 public:
  enum class MenuItem
  {
    NONE = -1,
    OPEN_MAIN_MENU = 4,
    DAMAGE_POWERUP = 5,
    HEALTH_POWERUP = 6,
    MOVE_SPEED_POWERUP = 7,
    SHOT_SIZE_POWERUP = 8,
    SHOT_SPEED_POWERUP = 9
  };

 public:
  ShopMenu() = default;
  ~ShopMenu();

  bool
  init(ASGE::Renderer* renderer, float game_width, float game_height) override;
  MenuItem update(Point2D point);
  void render(ASGE::Renderer* renderer) override;

  void disableDamage();
  void disableHealth();
  void disableMoveSpeed();
  void disableShotSize();
  void disableShotSpeed();

 private:
  MenuItem menuItem(Point2D point);
  void resetOpacity() override;

  // Sprites
  ASGE::Sprite* shop_title = nullptr;
  ASGE::Sprite* damage_powerup = nullptr;
  ASGE::Sprite* health_powerup = nullptr;
  ASGE::Sprite* move_speed_powerup = nullptr;
  ASGE::Sprite* shot_size_powerup = nullptr;
  ASGE::Sprite* shot_speed_powerup = nullptr;
  ASGE::Sprite* open_main_menu = nullptr;

  bool render_damage = true;
  bool render_health = true;
  bool render_move_speed = true;
  bool render_shot_size = true;
  bool render_shot_speed = true;
};

#endif // THE_SHINING_GAME_GROUP_3_SHOPMENU_H
