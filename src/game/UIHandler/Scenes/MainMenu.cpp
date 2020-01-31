//
// Created by Zoe on 12/01/2020.
//

#include "MainMenu.h"

/**
 *   @brief   Destructor
 *   @details Frees up the memory of the sprites
 */
MainMenu::~MainMenu()
{
  delete menu_title;
  menu_title = nullptr;

  delete start_game;
  start_game = nullptr;

  delete open_shop;
  open_shop = nullptr;

  delete exit_game;
  exit_game = nullptr;

  delete keyboard_image;
  keyboard_image = nullptr;

  delete controller_image;
  controller_image = nullptr;
}

/**
 *   @brief   Sets up the scene
 *   @details Sets up the sprites in the scene
 *   @param   renderer The ASGE renderer
 *            game_width The width of the game screen
 *   @return  True if setup correctly
 */
bool MainMenu::init(ASGE::Renderer* renderer, float game_width)
{
  menu_title = renderer->createRawSprite();
  if (!setupSprite(*menu_title,
                   "data/UI/MenuTitle.png",
                   game_width / 2 - 300,
                   57,
                   600,
                   150))
  {
    return false;
  }

  start_game = renderer->createRawSprite();
  if (!setupSprite(*start_game,
                   "data/UI/MenuButtons/StartButton.png",
                   game_width / 2 - 90,
                   262,
                   180,
                   45))
  {
    return false;
  }

  open_shop = renderer->createRawSprite();
  if (!setupSprite(*open_shop,
                   "data/UI/MenuButtons/ShopButton.png",
                   game_width / 2 - 90,
                   337,
                   180,
                   45))
  {
    return false;
  }

  exit_game = renderer->createRawSprite();
  if (!setupSprite(*exit_game,
                   "data/UI/MenuButtons/ExitButton.png",
                   game_width / 2 - 90,
                   412,
                   180,
                   45))
  {
    return false;
  }

  keyboard_image = renderer->createRawSprite();
  if (!setupSprite(*keyboard_image,
                   "data/UI/keyboard.png",
                   game_width / 4 - 41.5,
                   262,
                   83,
                   70))
  {
    return false;
  }

  controller_image = renderer->createRawSprite();
  return setupSprite(*controller_image,
                     "data/UI/controller.png",
                     (game_width / 4) * 3 - 48,
                     262,
                     96,
                     70);
}

/**
 *   @brief   Updates the opacity of the buttons in the scene
 *   @param   point The cursor position
 *   @return  The MenuItem the cursor is hovering over
 */
MainMenu::MenuItem MainMenu::update(Point2D point)
{
  MenuItem mouse_over = menuItem(point);

  resetOpacity();
  switch (mouse_over)
  {
    case MenuItem::START_GAME:
      start_game->opacity(1.0f);
      break;
    case MenuItem::OPEN_SHOP:
      open_shop->opacity(1.0f);
      break;
    case MenuItem::EXIT_GAME:
      exit_game->opacity(1.0f);
      break;
    default:
      break;
  }

  return mouse_over;
}

/**
 *   @brief   Renders the scene
 *   @param   renderer The ASGE renderer
 */
void MainMenu::render(ASGE::Renderer* renderer)
{
  renderer->renderSprite(*menu_title);
  renderer->renderSprite(*start_game);
  renderer->renderSprite(*open_shop);
  renderer->renderSprite(*exit_game);
  renderer->renderSprite(*keyboard_image);
  renderer->renderSprite(*controller_image);

  renderer->renderText("Move: Arrow Keys \nShoot: Space",
                       keyboard_image->xPos() - 40,
                       370,
                       1.0f,
                       ASGE::COLOURS::GREY);
  renderer->renderText("Move: Left Analog \nShoot Direction: Right Analog "
                       "\nShoot: Right Bumper",
                       controller_image->xPos() - 60,
                       370,
                       1.0f,
                       ASGE::COLOURS::GREY);
}

/**
 *   @brief   Gets the menu item the cursor is hovering over
 *   @param   point The position of the cursor
 *   @return  The menu item
 */
MainMenu::MenuItem MainMenu::menuItem(Point2D point)
{
  if (isInside(start_game, point))
  {
    return MenuItem::START_GAME;
  }
  else if (isInside(open_shop, point))
  {
    return MenuItem::OPEN_SHOP;
  }
  else if (isInside(exit_game, point))
  {
    return MenuItem::EXIT_GAME;
  }

  return MenuItem::NONE;
}

/**
 *   @brief   Resets the opacity of all the buttons
 */
void MainMenu::resetOpacity()
{
  start_game->opacity(0.5f);
  open_shop->opacity(0.5f);
  exit_game->opacity(0.5f);
}
