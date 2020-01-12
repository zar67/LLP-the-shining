//
// Created by Zoe on 12/01/2020.
//

#include "ShopMenu.h"
#include <iostream>

ShopMenu::~ShopMenu()
{
  if (shop_title)
  {
    delete shop_title;
    shop_title = nullptr;
  }

  if (damage_powerup)
  {
    delete damage_powerup;
    damage_powerup = nullptr;
  }

  if (health_powerup)
  {
    delete health_powerup;
    health_powerup = nullptr;
  }

  if (move_speed_powerup)
  {
    delete move_speed_powerup;
    move_speed_powerup = nullptr;
  }

  if (shot_size_powerup)
  {
    delete shot_size_powerup;
    shot_size_powerup = nullptr;
  }

  if (shot_speed_powerup)
  {
    delete shot_speed_powerup;
    shot_speed_powerup = nullptr;
  }

  if (open_main_menu)
  {
    delete open_main_menu;
    open_main_menu = nullptr;
  }
}

bool ShopMenu::init(ASGE::Renderer* renderer,
                    float game_width,
                    float game_height)
{
  shop_title = renderer->createRawSprite();
  if (!setupSprite(renderer,
                   *shop_title,
                   "data/UI/ShopTitle.png",
                   game_width / 2 - 200,
                   38,
                   400,
                   100))
  {
    return false;
  }

  damage_powerup = renderer->createRawSprite();
  if (!setupSprite(renderer,
                   *damage_powerup,
                   "data/UI/Shop/DamagePowerup.png",
                   42,
                   game_height / 2 - 50,
                   100,
                   130))
  {
    return false;
  }

  health_powerup = renderer->createRawSprite();
  if (!setupSprite(renderer,
                   *health_powerup,
                   "data/UI/Shop/HealthPowerup.png",
                   172,
                   game_height / 2 - 50,
                   100,
                   130))
  {
    return false;
  }

  move_speed_powerup = renderer->createRawSprite();
  if (!setupSprite(renderer,
                   *move_speed_powerup,
                   "data/UI/Shop/MoveSpeedPowerup.png",
                   302,
                   game_height / 2 - 50,
                   100,
                   130))
  {
    return false;
  }

  shot_size_powerup = renderer->createRawSprite();
  if (!setupSprite(renderer,
                   *shot_size_powerup,
                   "data/UI/Shop/ShotSizePowerup.png",
                   432,
                   game_height / 2 - 50,
                   100,
                   130))
  {
    return false;
  }

  shot_speed_powerup = renderer->createRawSprite();
  if (!setupSprite(renderer,
                   *shot_speed_powerup,
                   "data/UI/Shop/ShotSpeedPowerup.png",
                   562,
                   game_height / 2 - 50,
                   100,
                   130))
  {
    return false;
  }

  open_main_menu = renderer->createRawSprite();
  if (!setupSprite(renderer,
                   *open_main_menu,
                   "data/UI/MenuButtons/MenuButton.png",
                   game_width / 2 - 60,
                   game_height - 50,
                   120,
                   30))
  {
    return false;
  }

  return true;
}

ShopMenu::MenuItem ShopMenu::update(Point2D point)
{
  MenuItem mouse_over = menuItem(point);

  resetOpacity();
  switch (mouse_over)
  {
    case MenuItem::OPEN_MAIN_MENU:
      open_main_menu->opacity(1.0f);
      break;
    case MenuItem::DAMAGE_POWERUP:
      damage_powerup->opacity(1.0f);
      break;
    case MenuItem::HEALTH_POWERUP:
      health_powerup->opacity(1.0f);
      break;
    case MenuItem::MOVE_SPEED_POWERUP:
      move_speed_powerup->opacity(1.0f);
      break;
    case MenuItem::SHOT_SIZE_POWERUP:
      shot_size_powerup->opacity(1.0f);
      break;
    case MenuItem::SHOT_SPEED_POWERUP:
      shot_speed_powerup->opacity(1.0f);
      break;
  }

  return mouse_over;
}

void ShopMenu::render(ASGE::Renderer* renderer)
{
  renderer->renderSprite(*shop_title);

  renderer->renderSprite(*damage_powerup);
  renderer->renderSprite(*health_powerup);
  renderer->renderSprite(*move_speed_powerup);
  renderer->renderSprite(*shot_size_powerup);
  renderer->renderSprite(*shot_speed_powerup);

  renderer->renderSprite(*open_main_menu);
}

ShopMenu::MenuItem ShopMenu::menuItem(Point2D point)
{
  if (isInside(open_main_menu, point))
  {
    return MenuItem::OPEN_MAIN_MENU;
  }
  else if (isInside(damage_powerup, point) && render_damage_powerup)
  {
    return MenuItem::DAMAGE_POWERUP;
  }
  else if (isInside(health_powerup, point) && render_health_powerup)
  {
    return MenuItem::HEALTH_POWERUP;
  }
  else if (isInside(move_speed_powerup, point) && render_move_speed_powerup)
  {
    return MenuItem::MOVE_SPEED_POWERUP;
  }
  else if (isInside(shot_size_powerup, point) && render_shot_size_powerup)
  {
    return MenuItem::SHOT_SIZE_POWERUP;
  }
  else if (isInside(shot_speed_powerup, point) && render_shot_speed_powerup)
  {
    return MenuItem::SHOT_SPEED_POWERUP;
  }

  return MenuItem::NONE;
}

void ShopMenu::resetOpacity()
{
  damage_powerup->opacity(0.5f);
  health_powerup->opacity(0.5f);
  move_speed_powerup->opacity(0.5f);
  shot_size_powerup->opacity(0.5f);
  shot_speed_powerup->opacity(0.5f);
  open_main_menu->opacity(0.5f);
}