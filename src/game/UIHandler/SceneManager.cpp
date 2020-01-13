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
  enableInputs(input);

  cursor = renderer->createRawSprite();
  if (!cursor->loadTexture("data/Projectile.png"))
  {
    return false;
  }
  cursor->xPos(0);
  cursor->yPos(0);
  cursor->width(10);
  cursor->height(10);

  if (!main_menu.init(renderer, game_width, game_height))
  {
    return false;
  }

  if (!shop_menu.init(renderer, game_width, game_height))
  {
    return false;
  }

  return true;
}

SceneManager::ReturnValue SceneManager::update(const ASGE::GameTime& game_time)
{
  ReturnValue return_value = ReturnValue::NONE;

  if (screen_open == ScreenOpen::MAIN_MENU)
  {
    MainMenu::MenuItem main_menu_item = main_menu.update(mouse_pos);
    if (mouse_click)
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
      mouse_click = false;
    }
  }

  if (screen_open == ScreenOpen::SHOP)
  {
    ShopMenu::MenuItem shop_menu_item = shop_menu.update(mouse_pos);
    if (mouse_click)
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
      mouse_click = false;
    }
  }

  return return_value;
}

void SceneManager::render(ASGE::Renderer* renderer)
{
  if (screen_open == ScreenOpen::MAIN_MENU)
  {
    main_menu.render(renderer);
  }
  else if (screen_open == ScreenOpen::SHOP)
  {
    shop_menu.render(renderer);
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

void SceneManager::mouseHandler(ASGE::SharedEventData data)
{
  auto event = static_cast<const ASGE::MoveEvent*>(data.get());
  mouse_pos = { float(event->xpos), float(event->ypos) };

  cursor->xPos(mouse_pos.x - cursor->width() / 2);
  cursor->yPos(mouse_pos.y - cursor->height() / 2);
}

void SceneManager::clickHandler(ASGE::SharedEventData data)
{
  auto event = static_cast<const ASGE::ClickEvent*>(data.get());
  mouse_pos = { float(event->xpos), float(event->ypos) };

  if (event->action == ASGE::MOUSE::BUTTON_RELEASED)
  {
    mouse_click = true;
  }
}
