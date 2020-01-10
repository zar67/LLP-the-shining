//
// Created by Zoe on 10/01/2020.
//

#include "SceneManager.h"
#include <Engine/DebugPrinter.h>
#include <Engine/FileIO.h>
#include <Engine/Font.h>
#include <Engine/Renderer.h>
#include <Engine/Sprite.h>

#include <iostream>

SceneManager::~SceneManager()
{
  if (menu_title)
  {
    delete menu_title;
    menu_title = nullptr;
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

  if (cursor)
  {
    delete cursor;
    cursor = nullptr;
  }
}

bool SceneManager::initialise(ASGE::Renderer* renderer, int game_width)
{
  menu_title = renderer->createRawSprite();
  if (!setupUIElement(*menu_title,
                      "data/UI/MenuTitle.png",
                      game_width / 2 - 200,
                      38,
                      400,
                      100))
  {
    return false;
  }

  start_game = renderer->createRawSprite();
  if (!setupUIElement(*start_game,
                      "data/UI/StartButton.png",
                      game_width / 2 - 60,
                      175,
                      120,
                      30))
  {
    return false;
  }
  open_shop = renderer->createRawSprite();
  if (!setupUIElement(
        *open_shop, "data/UI/ShopButton.png", game_width / 2 - 60, 225, 120, 30))
  {
    return false;
  }
  exit_game = renderer->createRawSprite();
  if (!setupUIElement(
        *exit_game, "data/UI/ExitButton.png", game_width / 2 - 60, 275, 120, 30))
  {
    return false;
  }
  open_main_menu = renderer->createRawSprite();
  if (!setupUIElement(*open_main_menu,
                      "data/UI/MenuButton.png",
                      game_width / 2 - 60,
                      200,
                      120,
                      30))
  {
    return false;
  }
  cursor = renderer->createRawSprite();
  if (!setupUIElement(*cursor, "data/Projectile.png", 0, 0, 10, 10))
  {
    return false;
  }

  // loadFonts(renderer);

  return true;
}

void SceneManager::enableInput(ASGE::Input* input)
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

void SceneManager::disableInput(ASGE::Input* input)
{
  if (input)
  {
    input->unregisterCallback(mouse_handler_idx);
    input->unregisterCallback(mouse_click_handle);
    input->setCursorMode(ASGE::MOUSE::CursorMode::NORMAL);
  }
}

SceneManager::MenuItem SceneManager::update(const ASGE::GameTime&)
{
  if (mouse_over == MenuItem::START_GAME)
  {
    setOpacity(1.0f, 0.5f, 0.5f, 0.5f);
  }
  else if (mouse_over == MenuItem::OPEN_SHOP)
  {
    setOpacity(0.5f, 1.0f, 0.5f, 0.5f);
  }
  else if (mouse_over == MenuItem::EXIT_GAME)
  {
    setOpacity(0.5f, 0.5f, 1.0f, 0.5f);
  }
  else if (mouse_over == MenuItem::OPEN_MAIN_MENU)
  {
    setOpacity(0.5f, 0.5f, 0.5f, 1.0f);
  }
  else
  {
    setOpacity(0.5f, 0.5f, 0.5f, 0.5f);
  }

  if (mouse_click == MenuItem::START_GAME)
  {
    screen_open = GAME;
  }
  else if (mouse_click == MenuItem::OPEN_SHOP)
  {
    screen_open = SHOP;
  }
  else if (mouse_click == MenuItem::OPEN_MAIN_MENU)
  {
    screen_open = MAIN_MENU;
  }

  return mouse_click;
}

void SceneManager::render(ASGE::Renderer* renderer)
{
  // renderer->setFont(menu_font_index);
  renderer->renderSprite(*cursor);

  if (screen_open == MAIN_MENU || screen_open == GAME_OVER)
  {
    renderer->renderSprite(*start_game);
    renderer->renderSprite(*open_shop);
    renderer->renderSprite(*exit_game);

    if (screen_open == MAIN_MENU)
    {
      renderer->renderSprite(*menu_title);
    }
    else
    {
      renderer->renderText("GAME OVER", 205, 150);
    }
  }
  else if (screen_open == SHOP)
  {
    renderer->renderText("SHOP", 205, 150);
    renderer->renderSprite(*open_main_menu);
  }
}

SceneManager::ScreenOpen SceneManager::screenOpen()
{
  return screen_open;
}

bool SceneManager::isInside(ASGE::Sprite* btn, Point2D point) const
{
  auto bbox = btn->getGlobalBounds();

  return (point.x >= bbox.v1.x && point.x <= bbox.v2.x &&
          point.y >= bbox.v1.y && point.y <= bbox.v3.y);
}

bool SceneManager::loadFonts(ASGE::Renderer* renderer)
{
  // start by creating a file handle and attempting to open the font
  using File = ASGE::FILEIO::File;
  File file = File();
  if (file.open("/data/fonts/kenvector_future.ttf",
                ASGE::FILEIO::File::IOMode::READ))
  {
    // the file is open, but we need to read the contents of it into memory
    // we will use an IOBuffer for this, it will store the binary data read
    using Buffer = ASGE::FILEIO::IOBuffer;
    Buffer buffer = file.read();

    // if we have data, load the font
    if (buffer.length)
    {
      menu_font_index =
        renderer->loadFontFromMem("kenvector",
                                  buffer.as_unsigned_char(),
                                  static_cast<unsigned int>(buffer.length),
                                  128);
    }

    file.close();
    return true;
  }
  return false;
}

void SceneManager::mouseHandler(ASGE::SharedEventData data)
{
  auto event = static_cast<const ASGE::MoveEvent*>(data.get());
  Point2D mouse_pos{ float(event->xpos), float(event->ypos) };
  mouse_over = menuItem(mouse_pos);

  cursor->xPos(mouse_pos.x - cursor->width() / 2);
  cursor->yPos(mouse_pos.y - cursor->height() / 2);
}

void SceneManager::clickHandler(ASGE::SharedEventData data)
{
  auto event = static_cast<const ASGE::ClickEvent*>(data.get());
  Point2D mouse_pos{ float(event->xpos), float(event->ypos) };
  mouse_click = menuItem(mouse_pos);
}

SceneManager::MenuItem SceneManager::menuItem(const Point2D& mouse_pos)
{
  if (isInside(start_game, mouse_pos) &&
      (screen_open == MAIN_MENU || screen_open == GAME_OVER))
  {
    return MenuItem::START_GAME;
  }
  else if (isInside(open_shop, mouse_pos) &&
           (screen_open == MAIN_MENU || screen_open == GAME_OVER))
  {
    return MenuItem::OPEN_SHOP;
  }
  else if (isInside(exit_game, mouse_pos) &&
           (screen_open == MAIN_MENU || screen_open == GAME_OVER))
  {
    return MenuItem::EXIT_GAME;
  }
  else if (isInside(open_main_menu, mouse_pos) && screen_open == SHOP)
  {
    return MenuItem::OPEN_MAIN_MENU;
  }
  return MenuItem::NONE;
}

bool SceneManager::setupUIElement(ASGE::Sprite& sprite,
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
  sprite.opacity(0.5f);

  return true;
}

void SceneManager::setOpacity(float start, float shop, float exit, float menu)
{
  start_game->opacity(start);
  open_shop->opacity(shop);
  exit_game->opacity(exit);
  open_main_menu->opacity(menu);
}
