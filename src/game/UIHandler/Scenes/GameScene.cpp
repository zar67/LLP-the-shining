//
// Created by Zoe on 13/01/2020.
//

#include "GameScene.h"
#include <iostream>

GameScene::~GameScene()
{
  delete health_bar;
  health_bar = nullptr;

  delete health_bar_background;
  health_bar_background = nullptr;

  delete damage_powerup_icon;
  damage_powerup_icon = nullptr;

  delete health_powerup_icon;
  health_powerup_icon = nullptr;

  delete move_speed_powerup_icon;
  move_speed_powerup_icon = nullptr;

  delete shot_size_powerup_icon;
  shot_size_powerup_icon = nullptr;

  delete shot_speed_powerup_icon;
  shot_speed_powerup_icon = nullptr;
}

bool GameScene::init(ASGE::Renderer* renderer,
                     float game_width,
                     float game_height)
{
  health_bar = renderer->createRawSprite();
  if (!setupSprite(
        *health_bar, "data/UI/HealthBar.png", 10, game_height - 80, 100, 20))
  {
    return false;
  }

  health_bar_background = renderer->createRawSprite();
  if (!setupSprite(*health_bar_background,
                   "data/UI/HealthBarBackground.png",
                   10,
                   game_height - 80,
                   100,
                   20))
  {
    return false;
  }

  damage_powerup_icon = renderer->createRawSprite();
  if (!setupSprite(*damage_powerup_icon,
                   "data/UI/Power Up Icons/DamageIcon.png",
                   10,
                   game_height - 50,
                   40,
                   40))
  {
    return false;
  }

  health_powerup_icon = renderer->createRawSprite();
  if (!setupSprite(*health_powerup_icon,
                   "data/UI/Power Up Icons/HealthIcon.png",
                   60,
                   game_height - 50,
                   40,
                   40))
  {
    return false;
  }

  move_speed_powerup_icon = renderer->createRawSprite();
  if (!setupSprite(*move_speed_powerup_icon,
                   "data/UI/Power Up Icons/MoveSpeedIcon.png",
                   110,
                   game_height - 50,
                   40,
                   40))
  {
    return false;
  }

  shot_size_powerup_icon = renderer->createRawSprite();
  if (!setupSprite(*shot_size_powerup_icon,
                   "data/UI/Power Up Icons/ShotSizeIcon.png",
                   160,
                   game_height - 50,
                   40,
                   40))
  {
    return false;
  }

  shot_speed_powerup_icon = renderer->createRawSprite();
  return setupSprite(*shot_speed_powerup_icon,
                     "data/UI/Power Up Icons/ShotSpeedIcon.png",
                     210,
                     game_height - 50,
                     40,
                     40);
}

void GameScene::render(ASGE::Renderer* renderer,
                       int floor,
                       int coins,
                       int health,
                       bool (&abilities)[5])
{
  renderer->renderText("Floor " + std::to_string(floor), 10, 20);
  renderer->renderText("$" + std::to_string(coins), 10, 50);

  renderer->renderSprite(*health_bar_background);
  health_bar->width(health);
  renderer->renderSprite(*health_bar);

  // Abilities
  if (abilities[0])
  {
    renderer->renderSprite(*damage_powerup_icon);
  }
  if (abilities[1])
  {
    renderer->renderSprite(*health_powerup_icon);
  }
  if (abilities[2])
  {
    renderer->renderSprite(*move_speed_powerup_icon);
  }
  if (abilities[3])
  {
    renderer->renderSprite(*shot_size_powerup_icon);
  }
  if (abilities[4])
  {
    renderer->renderSprite(*shot_speed_powerup_icon);
  }
}
