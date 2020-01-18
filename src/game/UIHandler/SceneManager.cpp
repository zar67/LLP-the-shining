//
// Created by Zoe on 12/01/2020.
//

#include "SceneManager.h"
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Mouse.h>

SceneManager::~SceneManager()
{
  delete cursor;
  cursor = nullptr;
}

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

void SceneManager::disableInputs(ASGE::Input* input)
{
  if (input)
  {
    input->unregisterCallback(mouse_handler_idx);
    input->unregisterCallback(mouse_click_handle);
    input->setCursorMode(ASGE::MOUSE::CursorMode::NORMAL);
  }
}

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

  return game_over_menu.init(renderer, game_width, game_height);
}

SceneManager::ReturnValue SceneManager::updateMainMenu()
{
  ReturnValue return_value = ReturnValue::NONE;
  MainMenu::MenuItem main_menu_item = main_menu.update(cursor_pos);
  if (selected_pressed)
  {
    switch (main_menu_item)
    {
      case MainMenu::MenuItem::START_GAME:
        screen_open = ScreenOpen::GAME;
        return_value = ReturnValue::START_GAME;
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

  return return_value;
}

SceneManager::ReturnValue SceneManager::updateShop()
{
  ReturnValue return_value = ReturnValue::NONE;
  ShopMenu::MenuItem shop_menu_item = shop_menu.update(cursor_pos);
  if (selected_pressed)
  {
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
  }

  return return_value;
}

SceneManager::ReturnValue SceneManager::updateGameOver()
{
  ReturnValue return_value = ReturnValue::NONE;
  GameOverMenu::MenuItem game_over_item = game_over_menu.update(cursor_pos);
  if (selected_pressed)
  {
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
  }

  return return_value;
}

SceneManager::ReturnValue
SceneManager::update(double delta_time, ASGE::Input* input)
{
  ReturnValue return_value = ReturnValue::NONE;
  controllerHandler(delta_time, input);

  if (screen_open == ScreenOpen::MAIN_MENU)
  {
    return_value = updateMainMenu();
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

void SceneManager::render(
  ASGE::Renderer* renderer, int floor, int coins, int health, bool* abilities)
{
  if (screen_open == ScreenOpen::MAIN_MENU)
  {
    main_menu.render(renderer);
  }
  else if (screen_open == ScreenOpen::SHOP)
  {
    shop_menu.render(renderer);
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

SceneManager::ScreenOpen SceneManager::screenOpen()
{
  return screen_open;
}

void SceneManager::screenOpen(SceneManager::ScreenOpen screen)
{
  screen_open = screen;
}

bool SceneManager::inMenu()
{
  return screen_open != ScreenOpen::GAME;
}

void SceneManager::hideDamagePowerup()
{
  shop_menu.disableDamage();
}

void SceneManager::hideHealthPowerup()
{
  shop_menu.disableHealth();
}

void SceneManager::hideMoveSpeedPowerup()
{
  shop_menu.disableMoveSpeed();
}

void SceneManager::hideShotSizePowerup()
{
  shop_menu.disableShotSize();
}

void SceneManager::hideShotSpeedPowerup()
{
  shop_menu.disableShotSpeed();
}

void SceneManager::mouseHandler(ASGE::SharedEventData data)
{
  if (!controller_connected)
  {
    auto event = static_cast<const ASGE::MoveEvent*>(data.get());
    cursor_pos = { float(event->xpos), float(event->ypos) };

    cursor->xPos(cursor_pos.x - cursor->width() / 2);
    cursor->yPos(cursor_pos.y - cursor->height() / 2);
  }
}

void SceneManager::clickHandler(ASGE::SharedEventData data)
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