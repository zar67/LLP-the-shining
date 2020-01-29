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
        *health_bar, "data/UI/HealthBar.png", 10, game_height - 120, 150, 30))
  {
    return false;
  }

  health_bar_background = renderer->createRawSprite();
  if (!setupSprite(*health_bar_background,
                   "data/UI/HealthBarBackground.png",
                   10,
                   game_height - 120,
                   150,
                   30))
  {
    return false;
  }

  damage_powerup_icon = renderer->createRawSprite();
  if (!setupSprite(*damage_powerup_icon,
                   "data/UI/Power Up Icons/DamageIcon.png",
                   10,
                   game_height - 75,
                   60,
                   60))
  {
    return false;
  }

  health_powerup_icon = renderer->createRawSprite();
  if (!setupSprite(*health_powerup_icon,
                   "data/UI/Power Up Icons/HealthIcon.png",
                   80,
                   game_height - 75,
                   60,
                   60))
  {
    return false;
  }

  move_speed_powerup_icon = renderer->createRawSprite();
  if (!setupSprite(*move_speed_powerup_icon,
                   "data/UI/Power Up Icons/MoveSpeedIcon.png",
                   150,
                   game_height - 75,
                   60,
                   60))
  {
    return false;
  }

  shot_size_powerup_icon = renderer->createRawSprite();
  if (!setupSprite(*shot_size_powerup_icon,
                   "data/UI/Power Up Icons/ShotSizeIcon.png",
                   220,
                   game_height - 75,
                   60,
                   60))
  {
    return false;
  }

  shot_speed_powerup_icon = renderer->createRawSprite();
  return setupSprite(*shot_speed_powerup_icon,
                     "data/UI/Power Up Icons/ShotSpeedIcon.png",
                     290,
                     game_height - 75,
                     60,
                     60);
}

void GameScene::render(
  ASGE::Renderer* renderer, int floor, int coins, int health, bool* abilities)
{
  renderer->renderText("Floor " + std::to_string(floor), 10, 20);
  renderer->renderText("$" + std::to_string(coins), 10, 50);

  if (abilities[1])
  {
    health_bar_background->width(300);
  }

  renderer->renderSprite(*health_bar_background);
  health_bar->width(health * 1.5f);
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
