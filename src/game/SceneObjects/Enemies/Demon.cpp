//
// Created by Zoe on 08/01/2020.
//

#include "Demon.h"
#include <utility>

/**
 *   @brief   Desrtuctor
 *   @details Frees the weapon_component
 */
Demon::~Demon()
{
  delete weapon_component;
  weapon_component = nullptr;
}

/**
 *   @brief   Sets up the Demon
 *   @details Sets the default values and adds the relevant components
 *   @param   renderer The ASGE Renderer
 *            x_pos The starting x position
 *            y_pos The starting y position
 *   @return  True if setup correctly
 */
bool Demon::setup(ASGE::Renderer* renderer, float x_pos, float y_pos)
{
  hp = 100;
  damage = 10;
  speed = 80;

  addCollisionComponent();
  addWeaponComponent(renderer);
  if (addSpriteComponent(renderer, "data/Characters/Demon.png"))
  {
    spriteComponent()->getSprite()->xPos(x_pos);
    spriteComponent()->getSprite()->yPos(y_pos);
    return true;
  }

  return true;
}

/**
 *   @brief   Updates the Demon
 *   @details Moves the Demon towards the Player, tries to shoot and handles
 * collision with the crates
 *   @param   renderer The ASGE renderer
 *            player A reference to the player
 *            scene_objects The crates to detect collision against
 */
void Demon::update(ASGE::Renderer* renderer,
                   double delta_time,
                   Player* player,
                   std::vector<InteractableObjects*> scene_objects)
{
  ASGE::Sprite* sprite = player->spriteComponent()->getSprite();

  // Move Towards Player
  float distance_to_player =
    getDistanceBetween(spriteComponent()->getSprite()->xPos(),
                       spriteComponent()->getSprite()->yPos(),
                       sprite->xPos(),
                       sprite->yPos());
  std::vector<float> direction_to_player =
    getDirectionFromTo(spriteComponent()->getSprite()->xPos(),
                       spriteComponent()->getSprite()->yPos(),
                       sprite->xPos(),
                       sprite->yPos());
  if (distance_to_player > distance_to_keep)
  {
    move(delta_time, direction_to_player[0], direction_to_player[1], speed);
  }
  else if (distance_to_player < distance_to_keep)
  {
    move(delta_time, -direction_to_player[0], -direction_to_player[1], speed);
  }

  // Shoot Player
  if (weapon_component)
  {
    shoot_timer += delta_time;

    if (shoot_timer >= shoot_delay)
    {
      float x_pos = sprite_component->getSprite()->xPos() +
                    sprite_component->getSprite()->width() / 2;
      float y_pos = sprite_component->getSprite()->yPos() +
                    sprite_component->getSprite()->height() / 2;

      float player_x = player->spriteComponent()->getSprite()->xPos() +
                       player->spriteComponent()->getSprite()->width() / 2;
      float player_y = player->spriteComponent()->getSprite()->yPos() +
                       player->spriteComponent()->getSprite()->height() / 2;

      std::vector<float> dir =
        getDirectionFromTo(x_pos, y_pos, player_x, player_y);
      weapon_component->Fire(renderer, x_pos, y_pos, dir.at(0), dir.at(1));

      shoot_timer = 0;
    }

    // pass in crates vector as well to detect collision
    if (weaponComponent()->hitPlayer(
          delta_time, player, std::move(scene_objects)))
    {
      player->takeDamage(damage);
    }
  }
}

/**
 *   @brief   Renders the Demon and any projectiles
 *   @param   renderer The ASGE renderer
 */
void Demon::render(ASGE::Renderer* renderer)
{
  renderer->renderSprite(*sprite_component->getSprite());

  if (weapon_component)
  {
    weapon_component->render(renderer);
  }
}

/**
 *   @brief   Adds a new shooting component
 *   @return  True if setup correctly
 */
bool Demon::addWeaponComponent(ASGE::Renderer* renderer, bool use_arrow)
{
  if (weapon_component)
  {
    delete (weapon_component);
  }
  weapon_component = new ShootingComponent(renderer, use_arrow);

  return true;
}

/**
 *   @brief   Gets the weapon component
 *   @return  weapon_component
 */
ShootingComponent* Demon::weaponComponent()
{
  return weapon_component;
}
