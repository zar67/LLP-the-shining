//
// Created by Zoe on 12/01/2020.
//

#include "GameOverMenu.h"

#include <Engine/Font.h>
#include <Engine/Renderer.h>
#include <Engine/Sprite.h>

#include <iostream>

GameOverMenu::~GameOverMenu()
{
  if (game_over_title)
  {
    delete game_over_title;
    game_over_title = nullptr;
  }

  if (start_game)
  {
    delete start_game;
    start_game = nullptr;
  }

  if (open_shop)
  {
    delete open_shop;
    open_shop = nullptr;
  }

  if (exit_game)
  {
    delete exit_game;
    exit_game = nullptr;
  }

  if (open_main_menu)
  {
    delete open_main_menu;
    open_main_menu = nullptr;
  }
}

bool GameOverMenu::initialise(ASGE::Input* input,
                              ASGE::Renderer* renderer,
                              float game_width,
                              float game_height)
{
  enableInput(input);

  game_over_title = renderer->createRawSprite();
  if (!setupSprite(*game_over_title,
                   "data/UI/GameOverTitle.png",
                   game_width / 2 - 200,
                   38,
                   400,
                   100))
  {
    return false;
  }

  start_game = renderer->createRawSprite();
  if (!setupSprite(*start_game,
                   "data/UI/MenuButtons/StartButton.png",
                   game_width / 2 - 60,
                   175,
                   120,
                   30))
  {
    return false;
  }

  open_shop = renderer->createRawSprite();
  if (!setupSprite(*open_shop,
                   "data/UI/MenuButtons/ShopButton.png",
                   game_width / 2 - 60,
                   225,
                   120,
                   30))
  {
    return false;
  }

  exit_game = renderer->createRawSprite();
  if (!setupSprite(*exit_game,
                   "data/UI/MenuButtons/ExitButton.png",
                   game_width / 2 - 60,
                   275,
                   120,
                   30))
  {
    return false;
  }

  open_main_menu = renderer->createRawSprite();
  return setupSprite(*open_main_menu,
                     "data/UI/MenuButtons/MenuButton.png",
                     game_width / 2 - 60,
                     game_height - 80,
                     120,
                     30);
}

void GameOverMenu::enableInput(ASGE::Input* input)
{
  if (input)
  {
    mouse_handler_idx = input->addCallbackFnc(
      ASGE::E_MOUSE_MOVE, &GameOverMenu::mouseHandler, this);

    mouse_click_handle = input->addCallbackFnc(
      ASGE::E_MOUSE_CLICK, &GameOverMenu::clickHandler, this);

    input->setCursorMode(ASGE::MOUSE::CursorMode::HIDDEN);
  }
}

void GameOverMenu::disableInput(ASGE::Input* input)
{
  if (input)
  {
    input->unregisterCallback(mouse_handler_idx);
    input->unregisterCallback(mouse_click_handle);
    input->setCursorMode(ASGE::MOUSE::CursorMode::NORMAL);
  }
}

GameOverMenu::MenuItem GameOverMenu::update(const ASGE::GameTime&)
{
  resetOpacity();

  switch (mouse_over)
  {
    case MenuItem::START_GAME:
      start_game->opacity(1.0f);
      break;
    case MenuItem::OPEN_SHOP:
      open_shop->opacity(1.0f);
      break;
    case MenuItem::OPEN_MENU:
      open_main_menu->opacity(1.0f);
      break;
    case MenuItem::EXIT_GAME:
      exit_game->opacity(1.0f);
      break;
  }

  MenuItem temp = mouse_click;
  mouse_click = MenuItem::NONE;
  return temp;
}

void GameOverMenu::render(ASGE::Renderer* renderer)
{
  renderer->renderSprite(*game_over_title);
  renderer->renderSprite(*start_game);
  renderer->renderSprite(*open_shop);
  renderer->renderSprite(*exit_game);
}

bool GameOverMenu::isInside(ASGE::Sprite* btn, Point2D point) const
{
  auto bbox = btn->getGlobalBounds();

  return (point.x >= bbox.v1.x && point.x <= bbox.v2.x &&
          point.y >= bbox.v1.y && point.y <= bbox.v3.y);
}

void GameOverMenu::mouseHandler(ASGE::SharedEventData data)
{
  auto event = static_cast<const ASGE::MoveEvent*>(data.get());
  Point2D mouse_pos{ float(event->xpos), float(event->ypos) };
  mouse_over = menuItem(mouse_pos);
}

void GameOverMenu::clickHandler(ASGE::SharedEventData data)
{
  auto event = static_cast<const ASGE::ClickEvent*>(data.get());
  Point2D mouse_pos{ float(event->xpos), float(event->ypos) };

  if (event->action == ASGE::MOUSE::BUTTON_RELEASED)
  {
    mouse_click = menuItem(mouse_pos);
  }
}

GameOverMenu::MenuItem GameOverMenu::menuItem(const Point2D& mouse_pos)
{
  if (isInside(start_game, mouse_pos))
  {
    return MenuItem::START_GAME;
  }
  else if (isInside(open_shop, mouse_pos))
  {
    return MenuItem::OPEN_SHOP;
  }
  else if (isInside(exit_game, mouse_pos))
  {
    return MenuItem::EXIT_GAME;
  }

  return MenuItem::NONE;
}

bool GameOverMenu::setupSprite(ASGE::Sprite& sprite,
                               std::string texture,
                               float x_pos,
                               float y_pos,
                               float width,
                               float height)
{
  if (!sprite.loadTexture(texture))
  {
    return false;
  }

  sprite.xPos(x_pos);
  sprite.yPos(y_pos);
  sprite.width(width);
  sprite.height(height);

  return true;
}

void GameOverMenu::resetOpacity()
{
  start_game->opacity(0.5f);
  open_shop->opacity(0.5f);
  exit_game->opacity(0.5f);
  open_main_menu->opacity(0.5f);
}