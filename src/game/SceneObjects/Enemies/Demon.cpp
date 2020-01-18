//
// Created by Zoe on 08/01/2020.
//

#include "Demon.h"
#include <iostream>
#include <math.h>

Demon::~Demon()
{
  if (weapon_component)
  {
    delete weapon_component;
    weapon_component = nullptr;
  }
}

bool Demon::setup(ASGE::Renderer* renderer, float x_pos, float y_pos)
{
  hp = 100;
  damage = 10;
  speed = 80;

  addCollisionComponent();
  addWeaponComponent();
  if (addSpriteComponent(renderer, "data/Characters/Demon.png"))
  {
    spriteComponent()->getSprite()->xPos(x_pos);
    spriteComponent()->getSprite()->yPos(y_pos);
    return true;
  }

  return true;
}

void Demon::update(ASGE::Renderer* renderer, double delta_time, Player* player)
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
    std::cout << shoot_timer << std::endl;

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
      weapon_component->setMoveDirection(dir.at(0), dir.at(1));
      weapon_component->Fire(renderer, x_pos, y_pos);

      shoot_timer = 0;
    }

    if (weaponComponent()->hitPlayer(delta_time, player))
    {
      player->takeDamage(damage);
    }
  }
}

void Demon::render(ASGE::Renderer* renderer)
{
  renderer->renderSprite(*sprite_component->getSprite());

  if (weapon_component)
  {
    weapon_component->render(renderer);
  }
}

bool Demon::addWeaponComponent()
{
  if (weapon_component)
  {
    delete (weapon_component);
  }
  weapon_component = new ShootingComponent();

  return true;
}

ShootingComponent* Demon::weaponComponent()
{
  return weapon_component;
}
