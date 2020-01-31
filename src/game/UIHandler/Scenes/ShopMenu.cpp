//
// Created by Zoe on 12/01/2020.
//

#include "ShopMenu.h"

/**
 *   @brief   Destructor
 *   @details Frees up the memory of the sprites
 */
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

/**
 *   @brief   Sets up the scene
 *   @details Sets up the sprites in the scene
 *   @param   renderer The ASGE renderer
 *            game_width The width of the game screen
 *            game_height The height of the game screen
 *   @return  True if setup correctly
 */
bool ShopMenu::init(ASGE::Renderer* renderer,
                    float game_width,
                    float game_height)
{
  shop_title = renderer->createRawSprite();
  if (!setupSprite(*shop_title,
                   "data/UI/ShopTitle.png",
                   game_width / 2 - 300,
                   57,
                   600,
                   150))
  {
    return false;
  }

  damage_powerup = renderer->createRawSprite();
  if (!setupSprite(*damage_powerup,
                   "data/UI/Shop/DamagePowerup.png",
                   63,
                   game_height / 2 - 75,
                   150,
                   195))
  {
    return false;
  }

  health_powerup = renderer->createRawSprite();
  if (!setupSprite(*health_powerup,
                   "data/UI/Shop/HealthPowerup.png",
                   258,
                   game_height / 2 - 75,
                   150,
                   195))
  {
    return false;
  }

  move_speed_powerup = renderer->createRawSprite();
  if (!setupSprite(*move_speed_powerup,
                   "data/UI/Shop/MoveSpeedPowerup.png",
                   453,
                   game_height / 2 - 75,
                   150,
                   195))
  {
    return false;
  }

  shot_size_powerup = renderer->createRawSprite();
  if (!setupSprite(*shot_size_powerup,
                   "data/UI/Shop/ShotSizePowerup.png",
                   648,
                   game_height / 2 - 75,
                   150,
                   195))
  {
    return false;
  }

  shot_speed_powerup = renderer->createRawSprite();
  if (!setupSprite(*shot_speed_powerup,
                   "data/UI/Shop/ShotSpeedPowerup.png",
                   843,
                   game_height / 2 - 75,
                   150,
                   195))
  {
    return false;
  }

  open_main_menu = renderer->createRawSprite();
  return setupSprite(*open_main_menu,
                     "data/UI/MenuButtons/MenuButton.png",
                     game_width / 2 - 90,
                     game_height - 100,
                     180,
                     45);
}

/**
 *   @brief   Updates the opacity of the buttons in the scene
 *   @param   point The cursor position
 *   @return  The MenuItem the cursor is hovering over
 */
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

/**
 *   @brief   Renders the scene
 *   @details Only renders the power ups if they haven't been bought yet
 *   @param   renderer The ASGE renderer
 *            coins The money the player has
 */
void ShopMenu::render(ASGE::Renderer* renderer, int coins)
{
  renderer->renderSprite(*shop_title);
  renderer->renderText(
    "$" + std::to_string(coins), 10, 35, 1.5f, ASGE::COLOURS::GREY);

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

/**
 *   @brief   Stop damage power up being shown
 */
void ShopMenu::disableDamage()
{
  render_damage = false;
}

/**
 *   @brief   Stop health power up being shown
 */
void ShopMenu::disableHealth()
{
  render_health = false;
}

/**
 *   @brief   Stop move speed power up being shown
 */
void ShopMenu::disableMoveSpeed()
{
  render_move_speed = false;
}

/**
 *   @brief   Stop shot size power up being shown
 */
void ShopMenu::disableShotSize()
{
  render_shot_size = false;
}

/**
 *   @brief   Stop shot speed power up being shown
 */
void ShopMenu::disableShotSpeed()
{
  render_shot_speed = false;
}

/**
 *   @brief   Gets the menu item the cursor is hovering over
 *   @param   point The position of the cursor
 *   @return  The menu item
 */
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

/**
 *   @brief   Resets the opacity of all the buttons
 */
void ShopMenu::resetOpacity()
{
  damage_powerup->opacity(0.5f);
  health_powerup->opacity(0.5f);
  move_speed_powerup->opacity(0.5f);
  shot_size_powerup->opacity(0.5f);
  shot_speed_powerup->opacity(0.5f);
  open_main_menu->opacity(0.5f);
}