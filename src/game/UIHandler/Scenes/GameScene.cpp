//
// Created by Zoe on 13/01/2020.
//

#include "GameScene.h"
#include <iostream>

/**
 *   @brief   Destructor
 *   @details Frees up the memory of the sprites
 */
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

/**
 *   @brief   Sets up the scene
 *   @details Sets up the sprites in the scene
 *   @param   renderer The ASGE renderer
 *            game_height The height of the game screen
 *   @return  True if setup correctly
 */
bool GameScene::init(ASGE::Renderer* renderer, float game_height)
{
  health_bar = renderer->createRawSprite();
  if (!setupSprite(
        *health_bar, "data/UI/HealthBar.png", 10, game_height - 85, 150, 25))
  {
    return false;
  }

  health_bar_background = renderer->createRawSprite();
  if (!setupSprite(*health_bar_background,
                   "data/UI/HealthBarBackground.png",
                   10,
                   game_height - 85,
                   150,
                   25))
  {
    return false;
  }

  damage_powerup_icon = renderer->createRawSprite();
  if (!setupSprite(*damage_powerup_icon,
                   "data/UI/Power Up Icons/DamageIcon.png",
                   10,
                   game_height - 55,
                   45,
                   45))
  {
    return false;
  }

  health_powerup_icon = renderer->createRawSprite();
  if (!setupSprite(*health_powerup_icon,
                   "data/UI/Power Up Icons/HealthIcon.png",
                   65,
                   game_height - 55,
                   45,
                   45))
  {
    return false;
  }

  move_speed_powerup_icon = renderer->createRawSprite();
  if (!setupSprite(*move_speed_powerup_icon,
                   "data/UI/Power Up Icons/MoveSpeedIcon.png",
                   120,
                   game_height - 55,
                   45,
                   45))
  {
    return false;
  }

  shot_size_powerup_icon = renderer->createRawSprite();
  if (!setupSprite(*shot_size_powerup_icon,
                   "data/UI/Power Up Icons/ShotSizeIcon.png",
                   175,
                   game_height - 55,
                   45,
                   45))
  {
    return false;
  }

  shot_speed_powerup_icon = renderer->createRawSprite();
  return setupSprite(*shot_speed_powerup_icon,
                     "data/UI/Power Up Icons/ShotSpeedIcon.png",
                     230,
                     game_height - 55,
                     45,
                     45);
}

/**
 *   @brief   Renders the scene
 *   @param   renderer The ASGE renderer
 *            floor The floort the player is on
 *            coins The money the player has
 *            health The player's health
 *            abilities The abilities the player has
 */
void GameScene::render(ASGE::Renderer* renderer,
                       int floor,
                       int coins,
                       int health,
                       const bool* abilities)
{
  renderer->renderText(
    "Floor " + std::to_string(floor), 10, 30, 1.5f, ASGE::COLOURS::GREY);
  renderer->renderText(
    "$" + std::to_string(coins), 10, 65, 1.5f, ASGE::COLOURS::GREY);

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