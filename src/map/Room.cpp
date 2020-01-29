//
// Created by Zoe on 16/12/2019.
//

#include "Room.h"
#include <iostream>
#include <utility>

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

int Room::getId()
{
  return ID;
}

Room::RoomType Room::getType()
{
  return type;
}
void Room::setType(RoomType room_type)
{
  type = room_type;
}

bool Room::getNorth()
{
  return north;
}

bool Room::getEast()
{
  return east;
}

bool Room::getSouth()
{
  return south;
}

bool Room::getWest()
{
  return west;
}

bool Room::canMove()
{
  return movement_enabled;
}

void Room::canMove(bool movement)
{
  movement_enabled = movement;
}

bool Room::found()
{
  return revealed;
}

void Room::found(bool found)
{
  revealed = found;
}

void Room::renderObjectsInRoom(ASGE::Renderer* renderer)
{
  for (int i = 0; i < demons.size(); i++)
  {
    demons.at(i)->render(renderer);
  }

  for (int i = 0; i < ghosts.size(); i++)
  {
    ghosts.at(i)->render(renderer);
  }

  for (int i = 0; i < items.size(); i++)
  {
    items.at(i)->renderItem(renderer);
  }

  for (auto& obj : interactable_objs)
  {
    renderer->renderSprite(*obj->spriteComponent()->getSprite());
  }
}

bool Room::updateObjectsInRoom(ASGE::Renderer* renderer,
                               double delta_time,
                               Player* player,
                               int game_width,
                               int game_height)
{
  bool descend = false;

  for (int i = 0; i < demons.size(); i++)
  {
    demons.at(i)->update(renderer, delta_time, player, interactable_objs);
  }

  bool doors[4] = { north, east, south, west };
  for (int i = 0; i < ghosts.size(); i++)
  {
    ghosts.at(i)->update(
      delta_time, interactable_objs, doors, game_width, game_height);
  }

  for (int i = 0; i < items.size(); i++)
  {
    if (items.at(i)->hasCollidedWithPlayer(player))
    {
      items.at(i)->hasPickedUpItem();

      if (items.at(i)->itemType() == Item::GameItems::COIN)
      {
        player->addCoins(5);
      }
      else if (items.at(i)->itemType() == Item::GameItems::HEART)
      {
        player->addHealth(20);
      }
      else if (items.at(i)->itemType() == Item::GameItems::STAIRCASE)
      {
        descend = true;
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
      interactable_objs.erase(itr);
    }
    itr++;
  }

  return descend;
}

void Room::addDemonToRoom(ASGE::Renderer* renderer, float x_pos, float y_pos)
{
  Demon* new_demon = new Demon();
  new_demon->setup(renderer, x_pos, y_pos);
  demons.push_back(new_demon);
}

void Room::addGhostToRoom(ASGE::Renderer* renderer, float x_pos, float y_pos)
{
  Ghost* new_ghost = new Ghost();
  new_ghost->setup(renderer, x_pos, y_pos);
  ghosts.push_back(new_ghost);
}

/*
 * pass enemy memory location up to game.cpp
 * this is so player can access and detect collision
 * only include objects when detecting collision
 */
std::vector<GameObject*> Room::getEnemies(bool inlcude_objects = false)
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
  if (inlcude_objects)
  {
    for (auto& obj : interactable_objs)
    {
      enemies.push_back(obj);
    }
  }
  return enemies;
}

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

std::vector<InteractableObjects*> Room::getObjectsInRoom()
{
  return interactable_objs;
}

void Room::removeItemFromRoom(int item_index)
{
  if (item_index < items.size())
  {
    items.erase(items.begin() + item_index);
  }
}

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

void Room::addItemToRoom(Item* new_item)
{
  items.push_back(new_item);
}
