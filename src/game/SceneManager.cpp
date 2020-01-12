//
// Created by Zoe on 10/01/2020.
//

#include "SceneManager.h"
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

  if (game_over_title)
  {
    delete game_over_title;
    game_over_title = nullptr;
  }

  if (shop_title)
  {
    delete shop_title;
    shop_title = nullptr;
  }

  if (health_bar)
  {
    delete health_bar;
    health_bar = nullptr;
  }

  if (health_bar_background)
  {
    delete health_bar_background;
    health_bar_background = nullptr;
  }

  if (damage_icon)
  {
    delete damage_icon;
    damage_icon = nullptr;
  }
  if (health_icon)
  {
    delete health_icon;
    health_icon = nullptr;
  }
  if (move_speed_icon)
  {
    delete move_speed_icon;
    move_speed_icon = nullptr;
  }
  if (shot_size_icon)
  {
    delete shot_size_icon;
    shot_size_icon = nullptr;
  }
  if (shot_speed_icon)
  {
    delete shot_speed_icon;
    shot_speed_icon = nullptr;
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

bool SceneManager::initSprites(ASGE::Renderer* renderer,
                               float game_width,
                               float game_height)
{
  menu_title = renderer->createRawSprite();
  if (!setupSprite(*menu_title,
                   "data/UI/MenuTitle.png",
                   game_width / 2 - 200,
                   38,
                   400,
                   100))
  {
    return false;
  }

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

  health_bar = renderer->createRawSprite();
  if (!setupSprite(
        *health_bar, "data/UI/HealthBar.png", 20, game_height - 100, 100, 20))
  {
    return false;
  }

  health_bar_background = renderer->createRawSprite();
  if (!setupSprite(*health_bar_background,
                   "data/UI/HealthBarBackground.png",
                   20,
                   game_height - 100,
                   100,
                   20))
  {
    return false;
  }

  damage_icon = renderer->createRawSprite();
  if (!setupSprite(*damage_icon,
                   "data/UI/Power Up Icons/DamageIcon.png",
                   20,
                   game_height - 65,
                   40,
                   40))
  {
    return false;
  }

  health_icon = renderer->createRawSprite();
  if (!setupSprite(*health_icon,
                   "data/UI/Power Up Icons/HealthIcon.png",
                   80,
                   game_height - 65,
                   40,
                   40))
  {
    return false;
  }

  move_speed_icon = renderer->createRawSprite();
  if (!setupSprite(*move_speed_icon,
                   "data/UI/Power Up Icons/MoveSpeedIcon.png",
                   140,
                   game_height - 65,
                   40,
                   40))
  {
    return false;
  }

  shot_size_icon = renderer->createRawSprite();
  if (!setupSprite(*shot_size_icon,
                   "data/UI/Power Up Icons/ShotSizeIcon.png",
                   200,
                   game_height - 65,
                   40,
                   40))
  {
    return false;
  }

  shot_speed_icon = renderer->createRawSprite();
  if (!setupSprite(*shot_speed_icon,
                   "data/UI/Power Up Icons/ShotSpeedIcon.png",
                   260,
                   game_height - 65,
                   40,
                   40))
  {
    return false;
  }

  return true;
}

bool SceneManager::initButtons(ASGE::Renderer* renderer,
                               float game_width,
                               float game_height)
{
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
  if (!setupSprite(*open_main_menu,
                   "data/UI/MenuButtons/MenuButton.png",
                   game_width / 2 - 60,
                   game_height - 80,
                   120,
                   30))
  {
    return false;
  }

  return true;
}

bool SceneManager::initShop(ASGE::Renderer* renderer, float game_height)
{
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

  return true;
}

bool SceneManager::initialise(ASGE::Renderer* renderer,
                              float game_width,
                              float game_height)
{
  if (!initSprites(renderer, game_width, game_height))
  {
    return false;
  }

  if (!initButtons(renderer, game_width, game_height))
  {
    return false;
  }

  if (!initShop(renderer, game_height))
  {
    return false;
  }

  cursor = renderer->createRawSprite();
  if (!setupSprite(*cursor, "data/Projectile.png", 0, 0, 10, 10))
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

  switch (mouse_click)
  {
    case MenuItem::START_GAME:
      screen_open = GAME;
      break;
    case MenuItem::OPEN_SHOP:
      screen_open = SHOP;
      break;
    case MenuItem::OPEN_MAIN_MENU:
      screen_open = MAIN_MENU;
      break;
  }

  MenuItem temp = mouse_click;
  mouse_click = MenuItem::NONE;
  return temp;
}

void SceneManager::render(ASGE::Renderer* renderer,
                          int floor,
                          int coins,
                          int health)
{
  // renderer->setFont(menu_font_index);

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
      renderer->renderSprite(*game_over_title);
    }
  }
  else if (screen_open == SHOP)
  {
    renderer->renderSprite(*shop_title);
    renderer->renderSprite(*open_main_menu);
    renderer->renderSprite(*damage_powerup);
    renderer->renderSprite(*health_powerup);
    renderer->renderSprite(*move_speed_powerup);
    renderer->renderSprite(*shot_size_powerup);
    renderer->renderSprite(*shot_speed_powerup);
  }
  else if (screen_open == GAME)
  {
    renderer->renderText("Floor " + std::to_string(floor), 5, 20);
    renderer->renderText("$" + std::to_string(coins), 5, 40);

    renderer->renderSprite(*health_bar_background);
    health_bar->width(health);
    renderer->renderSprite(*health_bar);

    // Power Ups = {HEALTH, DAMAGE, MOVE SPEED, SHOT SPEED, SHOT SIZE}
  }

  if (screen_open != GAME)
  {
    renderer->renderSprite(*cursor);
  }
}

SceneManager::ScreenOpen SceneManager::screenOpen()
{
  return screen_open;
}

void SceneManager::screenOpen(ScreenOpen screen)
{
  screen_open = screen;
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

  if (event->action == ASGE::MOUSE::BUTTON_RELEASED)
  {
    mouse_click = menuItem(mouse_pos);
  }
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
  else if (isInside(damage_powerup, mouse_pos) && screen_open == SHOP)
  {
    return MenuItem::DAMAGE_POWERUP;
  }
  else if (isInside(health_powerup, mouse_pos) && screen_open == SHOP)
  {
    return MenuItem::HEALTH_POWERUP;
  }
  else if (isInside(move_speed_powerup, mouse_pos) && screen_open == SHOP)
  {
    return MenuItem::MOVE_SPEED_POWERUP;
  }
  else if (isInside(shot_size_powerup, mouse_pos) && screen_open == SHOP)
  {
    return MenuItem::SHOT_SIZE_POWERUP;
  }
  else if (isInside(shot_speed_powerup, mouse_pos) && screen_open == SHOP)
  {
    return MenuItem::SHOT_SPEED_POWERUP;
  }
  return MenuItem::NONE;
}

bool SceneManager::setupSprite(ASGE::Sprite& sprite,
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

void SceneManager::resetOpacity()
{
  damage_powerup->opacity(0.5f);
  health_powerup->opacity(0.5f);
  move_speed_powerup->opacity(0.5f);
  shot_size_powerup->opacity(0.5f);
  shot_speed_powerup->opacity(0.5f);

  start_game->opacity(0.5f);
  open_shop->opacity(0.5f);
  exit_game->opacity(0.5f);
  open_main_menu->opacity(0.5f);
}
