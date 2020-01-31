//
// Created by Zoe on 12/01/2020.
//

#include "SceneManager.h"
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Mouse.h>
#include <iostream>

/**
 *   @brief   Destructor
 *   @details Free the cursor memory
 */
SceneManager::~SceneManager()
{
  delete cursor;
  cursor = nullptr;
}

/**
 *   @brief   Sets up the callback functions for the mouse and click handler
 *   @param   input The ASGE input class
 */
void SceneManager::enableInputs(ASGE::Input* input)
{
  if (input)
  {
    mouse_handler_idx = input->addCallbackFnc(
      ASGE::E_MOUSE_MOVE, &SceneManager::mouseHandler, this);

    mouse_click_handle = input->addCallbackFnc(
      ASGE::E_MOUSE_CLICK, &SceneManager::clickHandler, this);

    input->setCursorMode(ASGE::MOUSE::CursorMode::HIDDEN);
  }
}

/**
 *   @brief   Unregisters the callback functions for the mouse and click handler
 *   @param   input The ASGE input class
 */
void SceneManager::disableInputs(ASGE::Input* input)
{
  if (input)
  {
    input->unregisterCallback(mouse_handler_idx);
    input->unregisterCallback(mouse_click_handle);
    input->setCursorMode(ASGE::MOUSE::CursorMode::NORMAL);
  }
}

/**
 *   @brief   Sets up the scene manager
 *   @details Enables input and sets up the scenes
 *   @param   input The ASGE input class
 *            renderer The ASGE renderer
 *            game_width The width of the game screen
 *            game_height The height of the game screen
 *   @return  True if setup correctly
 */
bool SceneManager::init(ASGE::Input* input,
                        ASGE::Renderer* renderer,
                        float game_width,
                        float game_height)
{
  if (input->getGamePad(0).is_connected)
  {
    controller_connected = true;
  }

  enableInputs(input);

  cursor = renderer->createRawSprite();
  if (!cursor->loadTexture("data/Projectile.png"))
  {
    return false;
  }
  cursor->xPos(game_width / 2 - 5);
  cursor->yPos(151.5);
  cursor->width(10);
  cursor->height(10);

  cursor_pos = { cursor->xPos(), cursor->yPos() };

  if (!main_menu.init(renderer, game_width, game_height))
  {
    return false;
  }

  if (!game_scene.init(renderer, game_width, game_height))
  {
    return false;
  }

  if (!shop_menu.init(renderer, game_width, game_height))
  {
    return false;
  }

  return game_over_menu.init(renderer, game_width);
}

/**
 *   @brief   Updates the main menu
 *   @details Updates the ui elements and determines which button has been
 * pressed
 *   @return  A value for the game to determine what to do next
 */
SceneManager::ReturnValue SceneManager::updateMainMenu(float delta_time)
{
  ReturnValue return_value = ReturnValue::NONE;
  MainMenu::MenuItem main_menu_item = main_menu.update(delta_time, cursor_pos);

  if (selected_pressed && !main_menu.inSplashScreen())
  {
    switch (main_menu_item)
    {
      case MainMenu::MenuItem::START_GAME:
        main_menu.setSplashScreen(true);
        break;
      case MainMenu::MenuItem::OPEN_SHOP:
        screen_open = ScreenOpen::SHOP;
        break;
      case MainMenu::MenuItem::EXIT_GAME:
        return_value = ReturnValue::EXIT_GAME;
        break;
      default:
        break;
    }
    selected_pressed = false;
  }
  else if (main_menu_item == MainMenu::MenuItem::SPLASH_SCREEN_ENDED)
  {
    screen_open = ScreenOpen::GAME;
    main_menu.setSplashScreen(false);
    return_value = ReturnValue::START_GAME;
  }

  return return_value;
}

/**
 *   @brief   Updates the shop
 *   @details Updates the ui elements and determines which button has been
 * pressed
 *   @return  A value for the game to determine what to do next
 */
SceneManager::ReturnValue SceneManager::updateShop()
{
  ReturnValue return_value = ReturnValue::NONE;
  ShopMenu::MenuItem shop_menu_item = shop_menu.update(cursor_pos);

  if (!selected_pressed)
  {
    return return_value;
  }

  switch (shop_menu_item)
  {
    case ShopMenu::MenuItem::OPEN_MAIN_MENU:
      screen_open = ScreenOpen::MAIN_MENU;
      break;
    case ShopMenu::MenuItem::DAMAGE_POWERUP:
      return_value = ReturnValue::BUY_DAMAGE_POWERUP;
      break;
    case ShopMenu::MenuItem::HEALTH_POWERUP:
      return_value = ReturnValue::BUY_HEALTH_POWERUP;
      break;
    case ShopMenu::MenuItem::MOVE_SPEED_POWERUP:
      return_value = ReturnValue::BUY_MOVE_SPEED_POWERUP;
      break;
    case ShopMenu::MenuItem::SHOT_SIZE_POWERUP:
      return_value = ReturnValue::BUY_SHOT_SIZE_POWERUP;
      break;
    case ShopMenu::MenuItem::SHOT_SPEED_POWERUP:
      return_value = ReturnValue::BUY_SHOT_SPEED_POWERUP;
      break;
    default:
      break;
  }
  selected_pressed = false;

  return return_value;
}

/**
 *   @brief   Updates the game over screen
 *   @details Updates the ui elements and determines which button has been
 * pressed
 *   @return  A value for the game to determine what to do next
 */
SceneManager::ReturnValue SceneManager::updateGameOver()
{
  ReturnValue return_value = ReturnValue::NONE;
  GameOverMenu::MenuItem game_over_item = game_over_menu.update(cursor_pos);

  if (!selected_pressed)
  {
    return return_value;
  }

  switch (game_over_item)
  {
    case GameOverMenu::MenuItem::START_GAME:
      screen_open = ScreenOpen::GAME;
      return_value = ReturnValue::START_GAME;
      break;
    case GameOverMenu::MenuItem::OPEN_SHOP:
      screen_open = ScreenOpen::SHOP;
      break;
    case GameOverMenu::MenuItem::MAIN_MENU:
      screen_open = ScreenOpen::MAIN_MENU;
      break;
    case GameOverMenu::MenuItem::EXIT_GAME:
      return_value = ReturnValue::EXIT_GAME;
      break;
    default:
      break;
  }
  selected_pressed = false;

  return return_value;
}

/**
 *   @brief   Updates the open scene
 *   @return  A value for the game to determine what to do next
 */
SceneManager::ReturnValue
SceneManager::update(double delta_time, ASGE::Input* input)
{
  ReturnValue return_value = ReturnValue::NONE;
  controllerHandler(delta_time, input);

  if (screen_open == ScreenOpen::MAIN_MENU)
  {
    return_value = updateMainMenu(delta_time);
  }

  if (screen_open == ScreenOpen::SHOP)
  {
    return_value = updateShop();
  }

  if (screen_open == ScreenOpen::GAME_OVER ||
      screen_open == ScreenOpen::GAME_WON)
  {
    return_value = updateGameOver();
  }

  return return_value;
}

/**
 *   @brief   Updates the splash screen on the game
 *   @return  True if game splash screen is over
 */
bool SceneManager::updateGameSplashScreen(float delta_time)
{
  return game_scene.update(delta_time);
}

/**
 *   @brief   Renders the open scene
 *   @param   renderer The ASGE renderer
 *            floor The current floor the player is on
 *            coins The number of coins the player has
 *            health The players health
 *            abilities The abilities of the player
 */
void SceneManager::render(
  ASGE::Renderer* renderer, int floor, int coins, int health, bool* abilities)
{
  if (screen_open == ScreenOpen::MAIN_MENU)
  {
    main_menu.render(renderer);
  }
  else if (screen_open == ScreenOpen::SHOP)
  {
    shop_menu.render(renderer, coins);
  }
  else if (screen_open == ScreenOpen::GAME)
  {
    game_scene.render(renderer, floor, coins, health, abilities);
  }
  else if (screen_open == ScreenOpen::GAME_OVER ||
           screen_open == ScreenOpen::GAME_WON)
  {
    game_over_menu.render(renderer, screen_open == ScreenOpen::GAME_WON);
  }

  if (screen_open != ScreenOpen::GAME)
  {
    renderer->renderSprite(*cursor);
  }
}

/**
 *   @brief   Sets what screen is currently open
 *   @param   screen The new screen to open
 */
void SceneManager::screenOpen(SceneManager::ScreenOpen screen)
{
  screen_open = screen;
}

/**
 *   @brief   Determines if in a menu
 *   @return  True if in menu
 *            False if in game
 */
bool SceneManager::inMenu()
{
  return screen_open != ScreenOpen::GAME;
}

/**
 *   @brief   Hides the damage power up from the shop
 */
void SceneManager::hideDamagePowerup()
{
  shop_menu.disableDamage();
}

/**
 *   @brief   Hides the health power up from the shop
 */
void SceneManager::hideHealthPowerup()
{
  shop_menu.disableHealth();
}

/**
 *   @brief   Hides the move speed power up from the shop
 */
void SceneManager::hideMoveSpeedPowerup()
{
  shop_menu.disableMoveSpeed();
}

/**
 *   @brief   Hides the shot size power up from the shop
 */
void SceneManager::hideShotSizePowerup()
{
  shop_menu.disableShotSize();
}

/**
 *   @brief   Hides the shot speed power up from the shop
 */
void SceneManager::hideShotSpeedPowerup()
{
  shop_menu.disableShotSpeed();
}

/**
 *   @brief   Opens the screen splash screen
 */
void SceneManager::openGameSplashScreen()
{
  game_scene.setSplashScreen(true);
}

/**
 *   @brief   Handles movement of the mouse
 *   @details Updates the cursor position when the mouse is moved. Only works if
 * a controller is not connected
 *   @param   data The event data relating to mouse input.
 */
void SceneManager::mouseHandler(const ASGE::SharedEventData& data)
{
  if (!controller_connected)
  {
    auto event = static_cast<const ASGE::MoveEvent*>(data.get());
    cursor_pos = { float(event->xpos), float(event->ypos) };

    cursor->xPos(cursor_pos.x - cursor->width() / 2);
    cursor->yPos(cursor_pos.y - cursor->height() / 2);
  }
}

/**
 *   @brief   Handles any mouse clicks
 *   @details Updates the cursor position and updates the selected_pressed when
 * the left mouse button is clicked. Only works if a controller is not connected
 *   @param   data The event data relating to mouse input.
 */
void SceneManager::clickHandler(const ASGE::SharedEventData& data)
{
  if (!controller_connected)
  {
    auto event = static_cast<const ASGE::ClickEvent*>(data.get());
    cursor_pos = { float(event->xpos), float(event->ypos) };

    if (event->action == ASGE::MOUSE::BUTTON_RELEASED)
    {
      selected_pressed = true;
    }
  }
}

/**
 *   @brief   Handles any inputs from the controller
 *   @details Gets the input from the left analog stick and A button and updates
 * the cursor and selected_pressed variables
 *   @param   input The ASGE inputs
 */
void SceneManager::controllerHandler(double delta_time, ASGE::Input* input)
{
  if (input->getGamePad(0).is_connected)
  {
    controller_connected = true;
    ASGE::GamePadData data = input->getGamePad(0);

    cursor_pos.x += data.axis[0] * delta_time * 300;
    cursor_pos.y -= data.axis[1] * delta_time * 300;

    cursor->xPos(cursor_pos.x);
    cursor->yPos(cursor_pos.y);

    if (!already_pressed && data.buttons[0])
    {
      selected_pressed = true;
      already_pressed = true;
    }

    if (!data.buttons[0])
    {
      selected_pressed = false;
      already_pressed = false;
    }
  }
  else
  {
    controller_connected = false;
  }
}