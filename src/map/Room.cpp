//
// Created by Zoe on 16/12/2019.
//

#include "Room.h"

/**
 *   @brief   Constructor
 *   @param   id The unique id of the room
 *            room_type The type of the room
 *            n_door Whether the room has a north door
 *            e_door Whether the room has an east door
 *            s_door Whether the room has a south door
 *            w_door Whether the room has a west door
 */
Room::Room(int id,
           RoomType room_type,
           bool n_door,
           bool e_door,
           bool s_door,
           bool w_door)
{
  ID = id;
  type = room_type;
  north = n_door;
  east = e_door;
  south = s_door;
  west = w_door;
  movement_enabled = false;
}

/**
 *   @brief   Destructor
 *   @details Frees up the memory of the enemies and items in the room
 */
Room::~Room()
{
  for (auto demon : demons)
  {
    delete demon;
  }
  demons.clear();

  for (auto ghost : ghosts)
  {
    delete ghost;
  }
  ghosts.clear();

  for (auto item : items)
  {
    delete item;
  }
  items.clear();
}

/**
 *   @brief   Sets up the room
 *   @details Adds a sprite component and adds crates to the room
 *   @param   renderer The ASGE renderer
 *            filename The location of the texture to load
 *   @return  True if set up correctly
 */
bool Room::setup(ASGE::Renderer* renderer, std::string* filename)
{
  addSpriteComponent(renderer, *filename);

  int num_objs = 1 + rand() % 3;
  for (int i = 0; i < num_objs; ++i)
  {
    auto* object = new InteractableObjects();
    while (true)
    {
      int x_rand = 100 + rand() % 450;
      int y_rand = 100 + rand() % 250;
      object->setup(renderer, x_rand, y_rand);

      for (auto& obj : interactable_objs)
      {
        if (object->collisionComponent()->hasCollided(
              *obj->collisionComponent()))
        {
          continue;
        }
      }
      break;
    }
    interactable_objs.push_back(object);
  }
}

/**
 *   @brief   Gets the ID of the room
 *   @return  ID
 */
int Room::getId()
{
  return ID;
}

/**
 *   @brief   Gets the type of the room
 *   @return  type
 */
Room::RoomType Room::getType()
{
  return type;
}

/**
 *   @brief   Sets the type of the room
 *   @param   room_type The new room type
 */
void Room::setType(RoomType room_type)
{
  type = room_type;
}

/**
 *   @brief   Gets the north door boolean
 *   @return  north
 */
bool Room::getNorth()
{
  return north;
}

/**
 *   @brief   Gets the east door boolean
 *   @return  east
 */
bool Room::getEast()
{
  return east;
}

/**
 *   @brief   Gets the south door boolean
 *   @return  south
 */
bool Room::getSouth()
{
  return south;
}

/**
 *   @brief   Gets the west door boolean
 *   @return  west
 */
bool Room::getWest()
{
  return west;
}

/**
 *   @brief   Gets if the player can leave the room
 *   @return  movement_enabled
 */
bool Room::canMove()
{
  return movement_enabled;
}

/**
 *   @brief   Sets if the player can leave the room
 *   @param   movement The new value
 */
void Room::canMove(bool movement)
{
  movement_enabled = movement;
}

/**
 *   @brief   Gets if the room had been entered before
 *   @return  revealed
 */
bool Room::found()
{
  return revealed;
}

/**
 *   @brief   Sets if the room has been found
 *   @param   found The new value
 */
void Room::found(bool found)
{
  revealed = found;
}

/**
 *   @brief   Renders all the enemies and items in the room
 *   @param   renderer The ASGE renderer
 */
void Room::renderObjectsInRoom(ASGE::Renderer* renderer)
{
  for (auto& demon : demons)
  {
    demon->render(renderer);
  }

  for (auto& ghost : ghosts)
  {
    ghost->render(renderer);
  }

  for (auto& item : items)
  {
    item->renderItem(renderer);
  }

  for (auto& obj : interactable_objs)
  {
    renderer->renderSprite(*obj->spriteComponent()->getSprite());
  }
}

/**
 *   @brief   Updates all the enemies in the room and checks collision of items
 *   @param   renderer The ASGE renderer
 *            audio A reference to the audio manager
 *            player A reference to the player
 *            game_width The width of the game screen
 *            game_height The height of the game screen
 *   @return  True if the player needs to descend floors (has collided with the
 * staircase)
 */
bool Room::updateObjectsInRoom(ASGE::Renderer* renderer,
                               AudioManager* audio,
                               double delta_time,
                               Player* player,
                               int game_width,
                               int game_height)
{
  bool descend = false;

  for (auto& demon : demons)
  {
    demon->update(renderer, delta_time, player, interactable_objs);
  }

  bool doors[4] = { north, east, south, west };
  for (auto& ghost : ghosts)
  {
    ghost->update(
      delta_time, interactable_objs, doors, game_width, game_height);
  }

  for (auto& item : items)
  {
    if (item->hasCollidedWithPlayer(player))
    {
      item->hasPickedUpItem();

      if (item->itemType() == Item::GameItems::COIN)
      {
        player->addCoins(2);
        audio->playCoin();
      }
      else if (item->itemType() == Item::GameItems::HEART)
      {
        player->addHealth(20);
        audio->playHeart();
      }
      else if (item->itemType() == Item::GameItems::STAIRCASE)
      {
        descend = true;
        audio->playDownAFloor();
      }
    }
  }

  // check if any enemies have been killed
  checkEnemyHealth();

  // check interactable objects health
  auto itr = interactable_objs.begin();
  for (auto& obj : interactable_objs)
  {
    bool is_destroyed = obj->checkHealth(renderer);
    if (is_destroyed)
    {
      chanceForItem(renderer, obj->spriteComponent()->getSprite());
      interactable_objs.erase(itr);
    }
    itr++;
  }

  return descend;
}

/**
 *   @brief   Adds a demon to the demons vector
 *   @param   renderer The ASGE renderer
 *            x_pos The starting x position
 *            y_pos The starting y position
 */
void Room::addDemonToRoom(ASGE::Renderer* renderer, float x_pos, float y_pos)
{
  auto* new_demon = new Demon();
  new_demon->setup(renderer, x_pos, y_pos);
  demons.push_back(new_demon);
}

/**
 *   @brief   Adds a ghost to the ghosts vector
 *   @param   renderer The ASGE renderer
 *            x_pos The starting x position
 *            y_pos The starting y position
 */
void Room::addGhostToRoom(ASGE::Renderer* renderer, float x_pos, float y_pos)
{
  auto* new_ghost = new Ghost();
  new_ghost->setup(renderer, x_pos, y_pos);
  ghosts.push_back(new_ghost);
}

/**
 *   @brief   Gets the enemies for player collision detection
 *   @param   include_objects Only include objects when detecting collision
 *   @return  Vector of gameobjects
 */
std::vector<GameObject*> Room::getEnemies(bool include_objects = false)
{
  std::vector<GameObject*> enemies;
  for (auto& demon : demons)
  {
    enemies.push_back(demon);
  }
  for (auto& ghost : ghosts)
  {
    enemies.push_back(ghost);
  }
  if (include_objects)
  {
    for (auto& obj : interactable_objs)
    {
      enemies.push_back(obj);
    }
  }
  return enemies;
}

/**
 *   @brief   Remove any enemies that have health lower than 0
 */
void Room::checkEnemyHealth()
{
  auto itr_ghost = ghosts.begin();
  for (auto& ghost : ghosts)
  {
    if (ghost->health() <= 0)
    {
      delete (ghost);
      ghost = nullptr;
      ghosts.erase(itr_ghost);
    }
    itr_ghost++;
  }

  auto itr_demon = demons.begin();
  for (auto& demon : demons)
  {
    if (demon->health() <= 0)
    {
      delete (demon);
      demon = nullptr;
      demons.erase(itr_demon);
    }
    itr_demon++;
  }
}

/**
 *   @brief   Gets the crates in the room
 *   @return  intractable_objs
 */
std::vector<InteractableObjects*> Room::getObjectsInRoom()
{
  return interactable_objs;
}

/**
 *   @brief   Adds a new item to the items vector
 *   @param   renderer The ASGE renderer
 *            filename The location of the texture to load
 *            item_type The type of item
 *            x_pos The starting x position
 *            y_pos The starting y position
 */
void Room::addItemToRoom(ASGE::Renderer* renderer,
                         std::string filename,
                         Item::GameItems item_type,
                         float x_pos,
                         float y_pos)
{
  Item* new_item = new Item();
  new_item->setUpItem(renderer, std::move(filename), item_type, x_pos, y_pos);
  items.push_back(new_item);
}

/**
 *   @brief   Adds a specific item to the items vector
 *   @param   new_item The item to be added
 */
void Room::addItemToRoom(Item* new_item)
{
  items.push_back(new_item);
}

/**
 *   @brief   Calculates whether to spawn the axe man
 *   @param   axe_man A reference to the psycho axe man
 *            game_width The width of the game screen
 *            game_height The height of the game screen
 *   @return  True if axe man spawned in room
 */
bool Room::axeManPresent(AxePsycho* axe_man, int game_width, int game_height)
{
  int should_Spawn = rand() % 7;
  if (should_Spawn == 0)
  {
    while (true)
    {
      bool doors[] = { north, east, south, west };
      int door_spawned = rand() % 4;
      if (doors[door_spawned])
      {
        int x_pos = 0;
        int y_pos = 0;
        if (door_spawned == 0)
        {
          x_pos =
            game_width / 2 -
            static_cast<int>(axe_man->spriteComponent()->getSprite()->width());
          y_pos = 150;
        }
        else if (door_spawned == 1)
        {
          x_pos = game_width - 150;
          y_pos = game_height / 2;
        }
        else if (door_spawned == 2)
        {
          x_pos =
            game_width / 2 -
            static_cast<int>(axe_man->spriteComponent()->getSprite()->width());
          y_pos = game_height - 150;
        }
        else
        {
          x_pos = 150;
          y_pos = game_height / 2;
        }
        axe_man->setSpawnedLocation(x_pos, y_pos);
        axe_man->spriteComponent()->getSprite()->xPos(x_pos);
        axe_man->spriteComponent()->getSprite()->yPos(y_pos);
        break;
      }
    }

    return true;
  }
  return false;
}

/**
 *   @brief   Calculate the chance for an item to spawn when a crate is
 * destroyed
 *   @param   renderer The ASGE renderer
 *            sprite The crate sprite
 */
void Room::chanceForItem(ASGE::Renderer* renderer, ASGE::Sprite* sprite)
{
  int chance = rand() % 10;
  std::string texture;
  Item::GameItems type;
  if (chance == 1)
  {
    texture = "data/Items/heart.png";
    type = Item::GameItems::HEART;
  }
  else if (chance > 7)
  {
    texture = "data/Items/coin.png";
    type = Item::GameItems::COIN;
  }
  else
  {
    return;
  }
  Item* item = new Item();
  item->setUpItem(renderer, texture, type, sprite->xPos(), sprite->yPos());
  items.push_back(item);
}
