//
// Created by Zoe on 12/01/2020.
//

#include "ShopMenu.h"
#include <iostream>

ShopMenu::~ShopMenu()
{
  delete shop_title;
  shop_title = nullptr;

  delete damage_powerup;
  damage_powerup = nullptr;

  delete health_powerup;
  health_powerup = nullptr;

  delete move_speed_powerup;
  move_speed_powerup = nullptr;

  delete shot_size_powerup;
  shot_size_powerup = nullptr;

  delete shot_speed_powerup;
  shot_speed_powerup = nullptr;

  delete open_main_menu;
  open_main_menu = nullptr;
}

bool ShopMenu::init(ASGE::Renderer* renderer,
                    float game_width,
                    float game_height)
{
  shop_title = renderer->createRawSprite();
  if (!setupSprite(*shop_title,
                   "data/UI/ShopTitle.png",
                   game_width / 2 - 200,
                   38,
                   400,
                   100))
  {
    return false;
  }

  damage_powerup = renderer->createRawSprite();
  if (!setupSprite(*damage_powerup,
                   "data/UI/Shop/DamagePowerup.png",
                   42,
                   game_height / 2 - 50,
                   100,
                   130))
  {
    return false;
  }

  health_powerup = renderer->createRawSprite();
  if (!setupSprite(*health_powerup,
                   "data/UI/Shop/HealthPowerup.png",
                   172,
                   game_height / 2 - 50,
                   100,
                   130))
  {
    return false;
  }

  move_speed_powerup = renderer->createRawSprite();
  if (!setupSprite(*move_speed_powerup,
                   "data/UI/Shop/MoveSpeedPowerup.png",
                   302,
                   game_height / 2 - 50,
                   100,
                   130))
  {
    return false;
  }

  shot_size_powerup = renderer->createRawSprite();
  if (!setupSprite(*shot_size_powerup,
                   "data/UI/Shop/ShotSizePowerup.png",
                   432,
                   game_height / 2 - 50,
                   100,
                   130))
  {
    return false;
  }

  shot_speed_powerup = renderer->createRawSprite();
  if (!setupSprite(*shot_speed_powerup,
                   "data/UI/Shop/ShotSpeedPowerup.png",
                   562,
                   game_height / 2 - 50,
                   100,
                   130))
  {
    return false;
  }

  open_main_menu = renderer->createRawSprite();
  return setupSprite(*open_main_menu,
                     "data/UI/MenuButtons/MenuButton.png",
                     game_width / 2 - 60,
                     game_height - 50,
                     120,
                     30);
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
    default:
      break;
  }

  return mouse_over;
}

void ShopMenu::render(ASGE::Renderer* renderer)
{
  renderer->renderSprite(*shop_title);

  if (render_damage)
  {
    renderer->renderSprite(*damage_powerup);
  }
  if (render_health)
  {
    renderer->renderSprite(*health_powerup);
  }
  if (render_move_speed)
  {
    renderer->renderSprite(*move_speed_powerup);
  }
  if (render_shot_size)
  {
    renderer->renderSprite(*shot_size_powerup);
  }
  if (render_shot_speed)
  {
    renderer->renderSprite(*shot_speed_powerup);
  }

  renderer->renderSprite(*open_main_menu);
}

void ShopMenu::disableDamage()
{
  render_damage = false;
}

void ShopMenu::disableHealth()
{
  render_health = false;
}

void ShopMenu::disableMoveSpeed()
{
  render_move_speed = false;
}

void ShopMenu::disableShotSize()
{
  render_shot_size = false;
}

void ShopMenu::disableShotSpeed()
{
  render_shot_speed = false;
}

ShopMenu::MenuItem ShopMenu::menuItem(Point2D point)
{
  if (isInside(open_main_menu, point))
  {
    return MenuItem::OPEN_MAIN_MENU;
  }
  else if (isInside(damage_powerup, point) && render_damage)
  {
    return MenuItem::DAMAGE_POWERUP;
  }
  else if (isInside(health_powerup, point) && render_health)
  {
    return MenuItem::HEALTH_POWERUP;
  }
  else if (isInside(move_speed_powerup, point) && render_move_speed)
  {
    return MenuItem::MOVE_SPEED_POWERUP;
  }
  else if (isInside(shot_size_powerup, point) && render_shot_size)
  {
    return MenuItem::SHOT_SIZE_POWERUP;
  }
  else if (isInside(shot_speed_powerup, point) && render_shot_speed)
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