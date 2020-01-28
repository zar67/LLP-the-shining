//
// Created by Zoe on 12/01/2020.
//

#include "MainMenu.h"

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
}

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
  return setupSprite(*exit_game,
                     "data/UI/MenuButtons/ExitButton.png",
                     game_width / 2 - 90,
                     412,
                     180,
                     45);
}

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

void MainMenu::render(ASGE::Renderer* renderer)
{
  renderer->renderSprite(*menu_title);
  renderer->renderSprite(*start_game);
  renderer->renderSprite(*open_shop);
  renderer->renderSprite(*exit_game);
}

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

void MainMenu::resetOpacity()
{
  start_game->opacity(0.5f);
  open_shop->opacity(0.5f);
  exit_game->opacity(0.5f);
}
