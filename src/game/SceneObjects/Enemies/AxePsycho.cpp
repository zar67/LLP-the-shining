//
// Created by Zoe on 10/01/2020.
//

#include "AxePsycho.h"

bool AxePsycho::setup(ASGE::Renderer* renderer, float x_pos, float y_pos)
{
  hp = 500;
  damage = 25;
  speed = 120;

  if (addSpriteComponent(renderer, "data/Characters/Demon.png"))
  {
    spriteComponent()->getSprite()->xPos(x_pos);
    spriteComponent()->getSprite()->yPos(y_pos);
    return true;
  }

  return false;
}

void AxePsycho::update(double delta_time, float player_x, float player_y)
{
  // Move Towards Player
  if (in_room)
  {
    std::vector<float> direction_to_player =
      getDirectionFromTo(spriteComponent()->getSprite()->xPos(),
                         spriteComponent()->getSprite()->yPos(),
                         player_x,
                         player_y);

    move(delta_time, -direction_to_player[0], -direction_to_player[1], speed);
  }

  // If Colliding With Player Attack
}
