//
// Created by Zoe on 13/01/2020.
//

#include "GameWonMenu.h"

GameWonMenu::~GameWonMenu()
{
  delete game_won_title;
  game_won_title = nullptr;

  delete start_game;
  start_game = nullptr;

  delete open_shop;
  open_shop = nullptr;

  delete open_menu;
  open_menu = nullptr;

  delete exit_game;
  exit_game = nullptr;
}

bool GameWonMenu::init(ASGE::Renderer* renderer,
                       float game_width,
                       float game_height)
{
  game_won_title = renderer->createRawSprite();
  if (!setupSprite(*game_won_title,
                   "data/UI/GameWonTitle.png",
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

  open_menu = renderer->createRawSprite();
  if (!setupSprite(*open_menu,
                   "data/UI/MenuButtons/MenuButton.png",
                   game_width / 2 - 60,
                   275,
                   120,
                   30))
  {
    return false;
  }

  exit_game = renderer->createRawSprite();
  return setupSprite(*exit_game,
                     "data/UI/MenuButtons/ExitButton.png",
                     game_width / 2 - 60,
                     325,
                     120,
                     30);
}

GameWonMenu::MenuItem GameWonMenu::update(Point2D point)
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
    case MenuItem::MAIN_MENU:
      open_menu->opacity(1.0f);
      break;
    case MenuItem::EXIT_GAME:
      exit_game->opacity(1.0f);
      break;
    default:
      break;
  }

  return mouse_over;
}

void GameWonMenu::render(ASGE::Renderer* renderer)
{
  renderer->renderSprite(*game_won_title);
  renderer->renderSprite(*start_game);
  renderer->renderSprite(*open_shop);
  renderer->renderSprite(*open_menu);
  renderer->renderSprite(*exit_game);
}

GameWonMenu::MenuItem GameWonMenu::menuItem(Point2D point)
{
  if (isInside(start_game, point))
  {
    return MenuItem::START_GAME;
  }
  else if (isInside(open_shop, point))
  {
    return MenuItem::OPEN_SHOP;
  }
  else if (isInside(open_menu, point))
  {
    return MenuItem::MAIN_MENU;
  }
  else if (isInside(exit_game, point))
  {
    return MenuItem::EXIT_GAME;
  }

  return MenuItem::NONE;
}

void GameWonMenu::resetOpacity()
{
  start_game->opacity(0.5f);
  open_shop->opacity(0.5f);
  open_menu->opacity(0.5f);
  exit_game->opacity(0.5f);
}