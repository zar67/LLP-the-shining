//
// Created by Zoe on 09/01/2020.
//

#include "Ghost.h"

/**
 *   @brief   Destructor
 *   @details Frees the obj_grabbed memory
 */
Ghost::~Ghost()
{
  if (obj_grabbed)
  {
    obj_grabbed->setIsGrabbed(false);
    obj_grabbed->spriteComponent()->getSprite()->colour(ASGE::COLOURS::BROWN);
    obj_grabbed = nullptr;
  }
}

/**
 *   @brief   Sets up the ghost
 *   @details Sets the default values and adds the relevant components
 *   @param   renderer The ASGE renderer
 *            x_pos The starting x position
 *            y_pos The starting y position
 *   @return  True if setup correctly
 */
bool Ghost::setup(ASGE::Renderer* renderer, float x_pos, float y_pos)
{
  hp = 50;
  damage = 5;
  speed = 150;

  addCollisionComponent();
  if (addSpriteComponent(renderer, "data/Characters/Ghost.png"))
  {
    spriteComponent()->getSprite()->xPos(x_pos);
    spriteComponent()->getSprite()->yPos(y_pos);
    return true;
  }

  return false;
}

/**
 *   @brief   Updates the ghost
 *   @details Randomly teleports the ghost, randomly picks up objects and moves
 * the grabbed object to a random door
 *   @param   objects The crates in the current room
 *            doors The doors of the current room
 *            game_width The width of the game screen
 *            game_height The height of the game screen
 */
void Ghost::update(double delta_time,
                   std::vector<InteractableObjects*>& objects,
                   bool doors[4],
                   int game_width,
                   int game_height)
{
  teleport_timer += delta_time;
  if (teleport_timer >= 5)
  {
    teleport_timer = 0;

    int ghost_loc_x = rand() % 12;
    int ghost_loc_y = rand() % 12;

    float x_pos = ghost_teleports_x[ghost_loc_x];
    float y_pos = ghost_teleports_y[ghost_loc_y];

    spriteComponent()->getSprite()->xPos(x_pos);
    spriteComponent()->getSprite()->yPos(y_pos);
  }
  // Random update
  if (obj_grabbed)
  {
    // Move Object to Block Door
    if (getDistanceBetween(obj_grabbed->spriteComponent()->getSprite()->xPos(),
                           obj_grabbed->spriteComponent()->getSprite()->yPos(),
                           door_pos[0],
                           door_pos[1]) > 50.0f)
    {
      direction =
        getDirectionFromTo(obj_grabbed->spriteComponent()->getSprite()->xPos(),
                           obj_grabbed->spriteComponent()->getSprite()->yPos(),
                           door_pos[0],
                           door_pos[1]);
      obj_grabbed->move(
        delta_time, direction[0], direction[1], jedi_force_speed);
    }
    else
    {
      obj_grabbed->setIsGrabbed(false);
      obj_grabbed->spriteComponent()->getSprite()->colour(ASGE::COLOURS::BROWN);
      obj_grabbed = nullptr;
    }
  }
  else
  {
    // Grab Object
    obj_grabbed = grabClosestObject(objects);
    getMoveToDoor(doors, door_pos, game_width, game_height);
    if (obj_grabbed)
    {
      obj_grabbed->spriteComponent()->getSprite()->colour(
        ASGE::COLOURS::GREENYELLOW);
    }
  }
}

/**
 *   @brief   Selects the closest object as the one to move
 *   @param   objects The crates in the room
 *   @return  The object it grabs
 */
InteractableObjects*
Ghost::grabClosestObject(std::vector<InteractableObjects*> objects)
{
  ASGE::Sprite* ghost_sprite = spriteComponent()->getSprite();
  InteractableObjects* closest_obj = nullptr;
  float distance = -1.0f;
  for (auto& obj : objects)
  {
    if (obj->isGrabbed())
    {
      continue;
    }
    ASGE::Sprite* obj_sprite = obj->spriteComponent()->getSprite();
    float next_distance = getDistanceBetween(ghost_sprite->xPos(),
                                             ghost_sprite->yPos(),
                                             obj_sprite->xPos(),
                                             obj_sprite->yPos());
    if (distance == -1.0f || distance > next_distance)
    {
      distance = next_distance;
      closest_obj = obj;
    }
  }
  if (closest_obj)
  {
    closest_obj->setIsGrabbed(true);
  }
  return closest_obj;
}

/**
 *   @brief   Chooses a random door to move objects towards
 *   @param   doors The doors of the current room
 *            out_pos A pointer to the array to change the values of
 *            game_width The width of the game screen
 *            game_height The height of the game screen
 */
void Ghost::getMoveToDoor(const bool doors[4],
                          float (&out_pos)[2],
                          float game_width,
                          float game_height)
{
  int choice = 0;
  do
  {
    choice = rand() % 4;
  } while (!doors[choice]);

  float x_pos;
  float y_pos;

  if (choice == 0)
  {
    x_pos = game_width / 2.0f;
    y_pos = 150.0f;
  }
  else if (choice == 1)
  {
    x_pos = game_width - 150.0f;
    y_pos = game_height / 2.0f;
  }
  else if (choice == 2)
  {
    x_pos = game_width / 2.0f;
    y_pos = game_height - 150.0f;
  }
  else
  {
    x_pos = 150.0f;
    y_pos = game_height / 2.0f;
  }

  out_pos[0] = x_pos;
  out_pos[1] = y_pos;
}
