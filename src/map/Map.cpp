//
// Created by Zoe on 16/12/2019.
//

#include "Map.h"
#include <Engine/FileIO.h>
#include <queue>

/**
 *   @brief   Destructor
 *   @details Frees the memory of the mini_map sprites and collision components
 */
Map::~Map()
{
  for (auto room : mini_map)
  {
    delete room;
  }
  mini_map.clear();

  for (auto& i : room_wall_collision)
  {
    delete i;
    i = nullptr;
  }

  for (auto& i : room_door_collision)
  {
    delete i;
    i = nullptr;
  }
}

/**
 *   @brief   Sets up the collision components for the room
 *   @param   game_width The width of the game screen
 *            game_height The height of the game screen
 */
void Map::setupRoomCollision(int game_width, int game_height)
{
  this->game_width = game_width;
  this->game_height = game_height;

  for (auto& i : room_wall_collision)
  {
    i = new CollisionComponent();
  }

  for (auto& i : room_door_collision)
  {
    i = new CollisionComponent();
  }

  setupBoundingBox(room_wall_collision[0], 0, 0, 96, 288);
  setupBoundingBox(room_wall_collision[1], 0, 0, 480, 96);
  setupBoundingBox(room_wall_collision[2], 576, 0, 480, 96);
  setupBoundingBox(room_wall_collision[3], 960, 0, 96, 288);

  setupBoundingBox(room_wall_collision[4], 0, 384, 96, 288);
  setupBoundingBox(room_wall_collision[5], 0, 576, 480, 96);
  setupBoundingBox(room_wall_collision[6], 576, 576, 480, 96);
  setupBoundingBox(room_wall_collision[7], 960, 384, 96, 288);

  setupBoundingBox(room_door_collision[0], 480, 0, 96, 96);   // North
  setupBoundingBox(room_door_collision[1], 960, 288, 96, 96); // East
  setupBoundingBox(room_door_collision[2], 480, 576, 96, 96); // South
  setupBoundingBox(room_door_collision[3], 0, 288, 96, 96);   // West
}

/**
 *   @brief   Handles the collision with the player and the room and the axe
 * psycho
 *   @param   player A reference to the player
 */
void Map::handlePlayerCollision(Player* player)
{
  player->updateCollisionComponent();
  CollisionComponent* player_collider = player->collisionComponent();
  axe_psycho.updateCollisionComponent();

  for (auto& wall : room_wall_collision)
  {
    if (player_collider->hasCollided(*wall))
    {
      CollisionComponent::CollisionSide side =
        player_collider->getCollisionSide(*wall);
      fixCollision(player, wall, side);
    }
    if (axe_psycho.inRoom() &&
        (player_collider->hasCollided(*axe_psycho.collisionComponent()) ||
         axe_psycho.collisionComponent()->hasCollided(*player_collider)) &&
        !axe_psycho.isPaused())
    {
      player->takeDamage(axe_psycho.attackDamage());
      axe_psycho.isPaused(true);
    }
  }

  std::vector<InteractableObjects*> objects =
    getCurrentRoom()->getObjectsInRoom();
  for (auto& obj : objects)
  {
    bool collision = obj->collisionComponent()->hasCollided(*player_collider);
    if (!collision)
    {
      collision = player_collider->hasCollided(*obj->collisionComponent());
    }
    if (collision)
    {
      CollisionComponent::CollisionSide side =
        player_collider->getCollisionSide(*obj->collisionComponent());
      fixCollision(player, obj->collisionComponent(), side);
      if (obj->isGrabbed())
      {
        player->takeDamage(obj->damage());
        obj->setIsGrabbed(false);
      }
    }
  }

  checkNorthDoorCollision(player);
  checkEastDoorCollision(player);
  checkSouthDoorCollision(player);
  checkWestDoorCollision(player);
}

/**
 *   @brief   Handles the collision of the enemies/items and the room
 *   @param   colliders The gameobjects to check against the room collision
 */
void Map::handleObjectCollision(std::vector<GameObject*> colliders)
{
  std::vector<InteractableObjects*> scene_objects =
    getCurrentRoom()->getObjectsInRoom();
  for (auto& col : colliders)
  {
    col->updateCollisionComponent();

    for (auto& wall : room_wall_collision)
    {
      if (col->collisionComponent()->hasCollided(*wall))
      {
        CollisionComponent::CollisionSide side =
          col->collisionComponent()->getCollisionSide(*wall);
        fixCollision(col, wall, side);
      }
    }

    for (auto& door : room_door_collision)
    {
      if (col->collisionComponent()->hasCollided(*door))
      {
        CollisionComponent::CollisionSide side =
          col->collisionComponent()->getCollisionSide(*door);
        fixCollision(col, door, side);
      }
    }

    for (auto& obj : scene_objects)
    {
      if (col->collisionComponent()->hasCollided(*obj->collisionComponent()) ||
          obj->collisionComponent()->hasCollided(*col->collisionComponent()))
      {
        CollisionComponent::CollisionSide side =
          col->collisionComponent()->getCollisionSide(
            *obj->collisionComponent());
        fixCollision(col, obj->collisionComponent(), side);
      }
    }
  }
}

/**
 *   @brief   Resolve colliding objects
 *   @details Push the object out of the other, direction depending on the side
 * hit
 *   @param   object The object to move
 *            collided The other object collided with
 *            side The side of the object hit
 */
void Map::fixCollision(GameObject* object,
                       CollisionComponent* collided,
                       CollisionComponent::CollisionSide side)
{
  float col_bounding_box[4];
  collided->getBoundingBox(col_bounding_box);

  ASGE::Sprite* object_sprite = object->spriteComponent()->getSprite();

  if (side == CollisionComponent::CollisionSide::SIDE_LEFT)
  {
    float x_pos = col_bounding_box[0] - object_sprite->width();
    object_sprite->xPos(x_pos);
  }

  else if (side == CollisionComponent::CollisionSide::SIDE_RIGHT)
  {
    float x_pos = col_bounding_box[0] + col_bounding_box[2];
    object_sprite->xPos(x_pos);
  }

  else if (side == CollisionComponent::CollisionSide::SIDE_TOP)
  {
    float y_pos = col_bounding_box[1] - object_sprite->height();
    object_sprite->yPos(y_pos);
  }

  else if (side == CollisionComponent::CollisionSide::SIDE_BOTTOM)
  {
    float y_pos = col_bounding_box[1] + col_bounding_box[3];
    object_sprite->yPos(y_pos);
  }
}

/**
 *   @brief   Move north
 *   @return  True if was able to move
 */
bool Map::moveNorth()
{
  if (getCurrentRoom()->getNorth() && getCurrentRoom()->canMove())
  {
    current_room -= map_size;
    getCurrentRoom()->found(true);
    updateMiniMap();
    return true;
  }

  return false;
}

/**
 *   @brief   Move east
 *   @return  True if was able to move
 */
bool Map::moveEast()
{
  if (getCurrentRoom()->getEast() && getCurrentRoom()->canMove())
  {
    current_room += 1;
    getCurrentRoom()->found(true);
    updateMiniMap();
    return true;
  }

  return false;
}

/**
 *   @brief   Move south
 *   @return  True if was able to move
 */
bool Map::moveSouth()
{
  if (getCurrentRoom()->getSouth() && getCurrentRoom()->canMove())
  {
    current_room += map_size;
    getCurrentRoom()->found(true);
    updateMiniMap();
    return true;
  }
  return false;
}

/**
 *   @brief   Move west
 *   @return  True if was able to move
 */
bool Map::moveWest()
{
  if (getCurrentRoom()->getWest() && getCurrentRoom()->canMove())
  {
    current_room -= 1;
    getCurrentRoom()->found(true);
    updateMiniMap();
    return true;
  }

  return false;
}

/**
 *   @brief   Get room with the specific ID
 *   @param   id The ID of the room to find
 *   @return  A pointer to the room
 */
Room* Map::getRoom(int id)
{
  int x_index = id % map_size;
  return &rooms[x_index][id - (x_index * map_size)];
}

/**
 *   @brief   Gets the current room
 *   @return  A pointer to the current room
 */
Room* Map::getCurrentRoom()
{
  return getRoom(current_room);
}

/**
 *   @brief   Render the current room and the objects in it
 *   @param   renderer The ASGE renderer
 */
void Map::renderCurrentRoom(ASGE::Renderer* renderer)
{
  renderer->renderSprite(*getCurrentRoom()->spriteComponent()->getSprite());
  getCurrentRoom()->renderObjectsInRoom(renderer);

  bool render_flash = axe_psycho.flashComponent()->isVisible();
  if (render_flash)
  {
    renderer->renderSprite(
      *axe_psycho.flashComponent()->spriteComponent()->getSprite());
  }
  else if (axePsycho()->inRoom())
  {
    renderer->renderSprite(*axePsycho()->spriteComponent()->getSprite());
  }
}

/**
 *   @brief   Updates the current room and the objects in it
 *   @param   renderer The ASGE renderer
 *            audio A reference to the audio manager
 *            player A reference to the player
 *            game_width The width of the game screen
 *            game_height The height of the game screen
 *   @return  True if player needs to descend a level
 */
bool Map::updateCurrentRoom(ASGE::Renderer* renderer,
                            AudioManager* audio,
                            double delta_time,
                            Player* player,
                            int game_width,
                            int game_height)
{
  bool descend = false;
  if (getCurrentRoom()->updateObjectsInRoom(
        renderer, audio, delta_time, player, game_width, game_height))
  {
    descend = true;
  }

  if (getEnemies(false).empty())
  {
    getCurrentRoom()->canMove(true);
  }

  if (roomChanged())
  {
    bool is_ready = axe_psycho.spawnTimerEnd(
      delta_time, axe_psycho.flashAimTime(), *axe_psycho.currentFlashTime());
    if (is_ready)
    {
      last_room = current_room;
      axe_psycho.flashComponent()->isFlashing(
        getCurrentRoom()->axeManPresent(&axe_psycho, game_width, game_height));
    }
  }
  else if (axe_psycho.flashComponent()->isFlashing())
  {
    bool in = axe_psycho.flashComponent()->flash(delta_time);
    axe_psycho.inRoom(in);
  }
  return descend;
}

/**
 *   @brief   Render the mini map
 *   @param   renderer The ASGE renderer
 */
void Map::renderMiniMap(ASGE::Renderer* renderer)
{
  for (int i = 0; i < mini_map.size(); i++)
  {
    /*if (getRoom(mini_map_ids.at(i))->found())
    {
      renderer->renderSprite(*mini_map[i]->spriteComponent()->getSprite());
    }*/
    renderer->renderSprite(*mini_map[i]->spriteComponent()->getSprite());
  }
}

/**
 *   @brief   Generate the starting room
 *   @param   renderer The ASGE renderer
 */
void Map::generateStartingRoom(ASGE::Renderer* renderer)
{
  // Set All Rooms To Empty
  current_room = STARTING_ROOM;
  for (int i = 0; i < map_size; i++)
  {
    for (int j = 0; j < map_size; j++)
    {
      rooms[i][j] = Room();
    }
  }

  // Generate Starting Room
  std::string file = "data/Rooms/NESW.png";
  rooms[map_size / 2][map_size / 2] =
    Room(STARTING_ROOM, Room::NORMAL, true, true, true, true);
  rooms[map_size / 2][map_size / 2].setup(renderer, &file);
  rooms[map_size / 2][map_size / 2].canMove(true);
  rooms[map_size / 2][map_size / 2].found(true);
}

/**
 *   @brief   Generate a new room
 *   @param   renderer The ASGE renderer
 *            x_index The x position in the rooms array
 *            y_index The y position in the rooms array
 */
void Map::generateNewRoom(ASGE::Renderer* renderer, int x_index, int y_index)
{
  // Calculate Required Doors (NESW)
  std::string doors_needed =
    needNorthDoor(x_index, y_index) + needEastDoor(x_index, y_index) +
    needSouthDoor(x_index, y_index) + needWestDoor(x_index, y_index);

  // Randomly Select Room with Correct Doors
  // Directory: data/Rooms/NESW.png
  // _ = No Door
  std::vector<std::string> possible_rooms;

  // For Each File
  std::vector<std::string> files = ASGE::FILEIO::enumerateFiles("data/"
                                                                "Rooms");
  for (const auto& name : files)
  {
    // Check If File is Valid
    if (checkRoomName(name, doors_needed))
    {
      // Add File to Possible Rooms
      possible_rooms.push_back(name);
    }
  }

  // Generate Random Room
  int index = static_cast<int>(rand() % possible_rooms.size());

  // Setup Room
  std::string file = "data/Rooms/" + possible_rooms[index];
  rooms[x_index][y_index] = Room(x_index * map_size + y_index,
                                 Room::NORMAL,
                                 possible_rooms[index][0] == 'N',
                                 possible_rooms[index][1] == 'E',
                                 possible_rooms[index][2] == 'S',
                                 possible_rooms[index][3] == 'W');
  rooms[x_index][y_index].setup(renderer, &file);
}

/**
 *   @brief   Room generation function
 *   @details Generates a new map of rooms, with enemies and items inside
 *   @param   renderer The ASGE renderer
 *            game_width The width of the game screen
 *            game_height The height of the game screen
 */
void Map::generateRooms(ASGE::Renderer* renderer,
                        int game_width,
                        int game_height)
{
  axe_psycho.setup(renderer, 0, 0, 92, 92, game_width, game_height);
  generateStartingRoom(renderer);

  // Create Queue of Rooms From Open Doors
  std::queue<std::array<int, 2>> rooms_to_generate;
  rooms_to_generate.push({ 2, 1 });
  rooms_to_generate.push({ 1, 2 });
  rooms_to_generate.push({ 2, 3 });
  rooms_to_generate.push({ 3, 2 });

  Room* last_room = &rooms[map_size / 2][map_size / 2];

  // For Each Room in the Queue
  while (!rooms_to_generate.empty())
  {
    int x_index = rooms_to_generate.front()[0];
    int y_index = rooms_to_generate.front()[1];

    if (rooms[x_index][y_index].getId() == -1)
    {
      generateNewRoom(renderer, x_index, y_index);
      last_room = &rooms[x_index][y_index];

      // Add New Rooms To Generate To Queue
      if (rooms[x_index][y_index].getNorth() &&
          rooms[x_index - 1][y_index].getId() == -1)
      {
        rooms_to_generate.push({ x_index - 1, y_index });
      }
      if (rooms[x_index][y_index].getEast() &&
          rooms[x_index][y_index + 1].getId() == -1)
      {
        rooms_to_generate.push({ x_index, y_index + 1 });
      }
      if (rooms[x_index][y_index].getSouth() &&
          rooms[x_index + 1][y_index].getId() == -1)
      {
        rooms_to_generate.push({ x_index + 1, y_index });
      }
      if (rooms[x_index][y_index].getWest() &&
          rooms[x_index][y_index - 1].getId() == -1)
      {
        rooms_to_generate.push({ x_index, y_index - 1 });
      }

      // Remove This Room From Queue
      rooms_to_generate.pop();
    }
    else
    {
      // Remove This Room From Queue
      rooms_to_generate.pop();
    }
  }

  last_room->setType(Room::EXIT);

  Item* staircase = new Item();
  staircase->setUpItem(renderer,
                       "data/Items/staircase.png",
                       Item::GameItems::STAIRCASE,
                       game_width / 2,
                       game_height / 2);
  last_room->addItemToRoom(staircase);

  generateItemRooms(renderer, game_width / 2, game_height / 2);
  generateEnemies(renderer, game_width, game_height);

  setupMinimap(renderer, game_width, game_height);
}

/**
 *   @brief   Setup the mini map
 *   @details Create a mini map based on the rooms generated
 *   @param   renderer The ASGE renderer
 *            game_width The width of the game screen
 *            game_height The height of the game screen
 */
void Map::setupMinimap(ASGE::Renderer* renderer,
                       int game_width,
                       int game_height)
{
  mini_map.clear();
  mini_map_ids.clear();

  int count = 0;
  // For Each Valid Room, Setup Mini Map Room With a Sprite Component
  for (int i = 0; i < map_size * map_size; i++)
  {
    if (getRoom(i)->getId() == -1)
    {
      continue;
    }

    std::string file = "data/MiniMap/";
    file += getRoom(i)->getNorth() ? "N" : "_";
    file += getRoom(i)->getEast() ? "E" : "_";
    file += getRoom(i)->getSouth() ? "S" : "_";
    file += getRoom(i)->getWest() ? "W" : "_";
    file += ".png";

    auto* new_room = new GameObject();
    mini_map.push_back(new_room);
    mini_map_ids.push_back(getRoom(i)->getId());

    if (mini_map.at(count)->addSpriteComponent(renderer, file))
    {
      int column = i % map_size;
      int row = (i - column) / map_size;

      mini_map.at(count)->spriteComponent()->getSprite()->xPos(
        game_width - (30 * map_size) + (column * 30));
      mini_map.at(count)->spriteComponent()->getSprite()->yPos(
        game_height - (30 * map_size) + (row * 30));
      count += 1;
    }
  }

  updateMiniMap();
}

/**
 *   @brief   Set up a bounding box
 *   @details Used to setup the room collision
 *   @param   component The collision component to set up
 *            x_pos The x position
 *            y_pos The y position
 *            width The width of the bounding box
 *            height The height of the bounding box
 */
void Map::setupBoundingBox(CollisionComponent* component,
                           float x_pos,
                           float y_pos,
                           float width,
                           float height)
{
  float bounding_box[4] = { x_pos, y_pos, width, height };
  component->updateBoundingBox(bounding_box);
}

/**
 *   @brief   Check if the player is colliding with the north door
 *   @param   player A reference to the player
 */
void Map::checkNorthDoorCollision(Player* player)
{
  CollisionComponent* player_collider = player->collisionComponent();
  ASGE::Sprite* player_sprite = player->spriteComponent()->getSprite();

  if (player_collider->hasCollided(*room_door_collision[0]))
  {
    if (getCurrentRoom()->getNorth())
    {
      if (player_sprite->yPos() < 10)
      {
        if (moveNorth())
        {
          player_sprite->yPos(576);
        }
        else
        {
          player_sprite->yPos(10);
        }
      }
    }
    else
    {
      CollisionComponent::CollisionSide side =
        player_collider->getCollisionSide(*room_door_collision[0]);
      fixCollision(player, room_door_collision[0], side);
    }
  }
}

/**
 *   @brief   Check if the player is colliding with the east door
 *   @param   player A reference to the player
 */
void Map::checkEastDoorCollision(Player* player)
{
  CollisionComponent* player_collider = player->collisionComponent();
  ASGE::Sprite* player_sprite = player->spriteComponent()->getSprite();

  if (player_collider->hasCollided(*room_door_collision[1]))
  {
    if (getCurrentRoom()->getEast())
    {
      if (player_sprite->xPos() > 1041 - player_sprite->width())
      {
        if (moveEast())
        {
          player_sprite->xPos(15);
        }
        else
        {
          player_sprite->xPos(1041 - player_sprite->width());
        }
      }
    }
    else
    {
      CollisionComponent::CollisionSide side =
        player_collider->getCollisionSide(*room_door_collision[1]);
      fixCollision(player, room_door_collision[1], side);
    }
  }
}

/**
 *   @brief   Check if the player is colliding with the south door
 *   @param   player A reference to the player
 */
void Map::checkSouthDoorCollision(Player* player)
{
  CollisionComponent* player_collider = player->collisionComponent();
  ASGE::Sprite* player_sprite = player->spriteComponent()->getSprite();

  if (player_collider->hasCollided(*room_door_collision[2]))
  {
    if (getCurrentRoom()->getSouth())
    {
      if (player_sprite->yPos() > 657 - player_sprite->height())
      {
        if (moveSouth())
        {
          player_sprite->yPos(15);
        }
        else
        {
          player_sprite->yPos(657 - player_sprite->height());
        }
      }
    }
    else
    {
      CollisionComponent::CollisionSide side =
        player_collider->getCollisionSide(*room_door_collision[2]);
      fixCollision(player, room_door_collision[2], side);
    }
  }
}

/**
 *   @brief   Check if the player is colliding with the west door
 *   @param   player A reference to the player
 */
void Map::checkWestDoorCollision(Player* player)
{
  CollisionComponent* player_collider = player->collisionComponent();
  ASGE::Sprite* player_sprite = player->spriteComponent()->getSprite();

  if (player_collider->hasCollided(*room_door_collision[3]))
  {
    if (getCurrentRoom()->getWest())
    {
      if (player_sprite->xPos() < 10)
      {
        if (moveWest())
        {
          player_sprite->xPos(960);
        }
        else
        {
          player_sprite->xPos(10);
        }
      }
    }
    else
    {
      CollisionComponent::CollisionSide side =
        player_collider->getCollisionSide(*room_door_collision[3]);
      fixCollision(player, room_door_collision[3], side);
    }
  }
}

/**
 *   @brief   Randomly generate item rooms in the map and populate them
 *   @param   renderer The ASGE renderer
 *            game_width The width of the game screen
 *            game_height The height of the game screen
 */
void Map::generateItemRooms(ASGE::Renderer* renderer,
                            int game_width,
                            int game_height)
{
  int item_room_num = rand() % 3 + 2;

  for (int i = 0; i < item_room_num; i++)
  {
    int id = STARTING_ROOM;
    while (id == STARTING_ROOM || getRoom(id)->getId() == -1 ||
           getRoom(id)->getType() != Room::NORMAL)
    {
      id = rand() % (map_size * map_size);
    }

    getRoom(id)->setType(Room::ITEM);

    // Generate Coins
    int coin_num = rand() & 2 + 1;
    for (int j = 0; j < coin_num; j++)
    {
      getRoom(id)->addItemToRoom(renderer,
                                 "data/Items/coin.png",
                                 Item::GameItems::COIN,
                                 (rand() & (game_width - 192)) + 96,
                                 (rand() & (game_height - 192)) + 96);
    }

    // Generate Hearts
    int heart_num = rand() & 1;
    for (int j = 0; j < heart_num; j++)
    {
      getRoom(id)->addItemToRoom(renderer,
                                 "data/Items/heart.png",
                                 Item::GameItems::HEART,
                                 (rand() & (game_width - 192)) + 96,
                                 (rand() & (game_height - 192)) + 96);
    }
  }
}

/**
 *   @brief   Populate normal rooms with enemies
 *   @param   renderer The ASGE renderer
 *            game_width The width of the game screen
 *            game_height The height of the game screen
 */
void Map::generateEnemies(ASGE::Renderer* renderer,
                          int game_width,
                          int game_height)
{
  for (int i = 0; i < map_size * map_size; i++)
  {
    if (getRoom(i)->getId() == -1 || getRoom(i)->getId() == STARTING_ROOM ||
        getRoom(i)->getType() != Room::NORMAL)
    {
      continue;
    }

    // Generate Demons
    int demon_num = rand() % 2 + 1;
    for (int x = 0; x < demon_num; x++)
    {
      float rand_x = rand() % (game_width - 204) + 102;
      float rand_y = rand() % (game_height - 236) + 118;

      getRoom(i)->addDemonToRoom(renderer, rand_x, rand_y);
    }

    // Generate Ghosts
    int ghost_num = rand() % 2;
    for (int x = 0; x < ghost_num; x++)
    {
      float rand_x = rand() % (game_width - 204) + 102;
      float rand_y = rand() % (game_height - 236) + 118;

      getRoom(i)->addGhostToRoom(renderer, rand_x, rand_y);
    }
  }
}

/**
 *   @brief   Change the colours of the mini map sprites to show the current
 * room
 */
void Map::updateMiniMap()
{
  for (int i = 0; i < mini_map.size(); i++)
  {
    // Update The Current Room To Red
    if (mini_map_ids.at(i) == current_room)
    {
      mini_map.at(i)->spriteComponent()->getSprite()->colour(
        ASGE::COLOURS::RED);
    }
    // Set Exit Room To Blue
    else if (getRoom(mini_map_ids.at(i))->getType() == Room::EXIT)
    {
      mini_map.at(i)->spriteComponent()->getSprite()->colour(
        ASGE::COLOURS::BLUE);
    }
    // Set Item Rooms To Green
    else if (getRoom(mini_map_ids.at(i))->getType() == Room::ITEM)
    {
      mini_map.at(i)->spriteComponent()->getSprite()->colour(
        ASGE::COLOURS::GREEN);
    }
    // Set Every Other Room To Grey
    else
    {
      mini_map.at(i)->spriteComponent()->getSprite()->colour(
        ASGE::COLOURS::GREY);
    }
  }
}

/**
 *   @brief   When generating rooms, check if the current room needs a north
 * door
 *   @param   x_pos The x position of the room
 *            y_pos The y position of the room
 *   @return  N if north door needed
 *            _ if cannot have north door
 *            * if can either have one or not
 */
std::string Map::needNorthDoor(int x_pos, int y_pos)
{
  if (x_pos - 1 >= 0)
  {
    if (rooms[x_pos - 1][y_pos].getId() == -1)
    {
      return "*";
    }

    if (rooms[x_pos - 1][y_pos].getSouth())
    {
      return "N";
    }

    return "_";
  }

  return "_";
}

/**
 *   @brief   When generating rooms, check if the current room needs a east door
 *   @param   x_pos The x position of the room
 *            y_pos The y position of the room
 *   @return  E if east door needed
 *            _ if cannot have east door
 *            * if can either have one or not
 */
std::string Map::needEastDoor(int x_pos, int y_pos)
{
  if (y_pos + 1 < map_size)
  {
    if (rooms[x_pos][y_pos + 1].getId() == -1)
    {
      return "*";
    }

    if (rooms[x_pos][y_pos + 1].getWest())
    {
      return "E";
    }

    return "_";
  }

  return "_";
}

/**
 *   @brief   When generating rooms, check if the current room needs a south
 * door
 *   @param   x_pos The x position of the room
 *            y_pos The y position of the room
 *   @return  S if south door needed
 *            _ if cannot have south door
 *            * if can either have one or not
 */
std::string Map::needSouthDoor(int x_pos, int y_pos)
{
  if (x_pos + 1 < map_size)
  {
    if (rooms[x_pos + 1][y_pos].getId() == -1)
    {
      return "*";
    }

    if (rooms[x_pos + 1][y_pos].getNorth())
    {
      return "S";
    }

    return "_";
  }

  return "_";
}

/**
 *   @brief   When generating rooms, check if the current room needs a west door
 *   @param   x_pos The x position of the room
 *            y_pos The y position of the room
 *   @return  W if west door needed
 *            _ if cannot have west door
 *            * if can either have one or not
 */
std::string Map::needWestDoor(int x_pos, int y_pos)
{
  if (y_pos - 1 >= 0)
  {
    if (rooms[x_pos][y_pos - 1].getId() == -1)
    {
      return "*";
    }

    if (rooms[x_pos][y_pos - 1].getEast())
    {
      return "W";
    }

    return "_";
  }

  return "_";
}

/**
 *   @brief   See if room name has the required doors
 *   @param   name The name to check
 *            required_doors The doors needed
 *   @return  True if name has the correct doors
 */
bool Map::checkRoomName(std::string name, std::string required_doors)
{
  bool valid = true;
  for (int i = 0; i < 4; i++)
  {
    if (required_doors[i] != '*' && name[i] != required_doors[i])
    {
      valid = false;
    }
  }
  return valid;
}

/**
 *   @brief   Adds the axe man to enemies
 *   @details Only adds him if he is in the room, if not he is removed from
 * enemies
 *   @param   include_objects Whether to include_objects in enemies list
 *   @return  vector of enemies in the current room
 */
std::vector<GameObject*> Map::getEnemies(bool include_objects = false)
{
  std::vector<GameObject*> enemies =
    getCurrentRoom()->getEnemies(include_objects);

  auto itr = enemies.begin();
  if (axe_psycho.inRoom() || axe_psycho.flashComponent()->isFlashing())
  {
    getCurrentRoom()->canMove(false);
    enemies.push_back(&axe_psycho);
  }
  else if (axe_psycho.isKilled())
  {
    for (auto& evil : enemies)
    {
      if (evil == &axe_psycho)
      {
        enemies.erase(itr);
        break;
      }
      itr++;
    }
    axe_psycho.isKilled(false);
  }
  return enemies;
}

/**
 *   @brief   Gets a reference to the axe psycho
 *   @return  axe_psycho
 */
AxePsycho* Map::axePsycho()
{
  return &axe_psycho;
}

/**
 *   @brief   Gets if room has changed
 *   @details Used with setting the axe man to spawn
 *   @return  True if room has changed
 */
bool Map::roomChanged()
{
  return current_room != last_room;
}
