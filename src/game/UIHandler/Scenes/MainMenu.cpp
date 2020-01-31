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

  delete splash_screen;
  splash_screen = nullptr;
}

/**
 *   @brief   Sets up the scene
 *   @details Sets up the sprites in the scene
 *   @param   renderer The ASGE renderer
 *            game_width The width of the game screen
 *   @return  True if setup correctly
 */
bool MainMenu::init(ASGE::Renderer* renderer,
                    float game_width,
                    float game_height)
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

  splash_screen = renderer->createRawSprite();
  return setupSprite(
    *splash_screen, "data/UI/SplashScreen.png", 0, 0, game_width, game_height);
}

/**
 *   @brief   Updates the opacity of the buttons in the scene
 *   @param   point The cursor position
 *   @return  The MenuItem the cursor is hovering over
 */
MainMenu::MenuItem MainMenu::update(float delta_time, Point2D point)
{
  MenuItem mouse_over = MenuItem::NONE;

  if (in_splash_screen)
  {
    splash_screen_timer += delta_time;
    if (splash_screen_timer >= splash_screen_duration)
    {
      in_splash_screen = false;
      mouse_over = MenuItem::SPLASH_SCREEN_ENDED;
      splash_screen_timer = 0;
    }
  }
  else
  {
    mouse_over = menuItem(point);
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
  }

  return mouse_over;
}

/**
 *   @brief   Renders the scene
 *   @param   renderer The ASGE renderer
 */
void MainMenu::render(ASGE::Renderer* renderer)
{
  if (in_splash_screen)
  {
    renderer->renderSprite(*splash_screen);
    std::string start_string =
      "Game Starts In: " +
      std::to_string(
        static_cast<int>(splash_screen_duration - splash_screen_timer) + 1);
    renderer->renderText(start_string, 10, 660, 1.5f, ASGE::COLOURS::GREY);
  }
  else
  {
    renderer->renderSprite(*menu_title);
    renderer->renderSprite(*start_game);
    renderer->renderSprite(*open_shop);
    renderer->renderSprite(*exit_game);
  }
}

/**
 *   @brief   Gets whether the menu is in the splash screen
 *   @return  in_splash_screen
 */
bool MainMenu::inSplashScreen()
{
  return in_splash_screen;
}

/**
 *   @brief   Opens the splash screen
 *   @param   value The new value
 */
void MainMenu::setSplashScreen(bool value)
{
  in_splash_screen = value;
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
