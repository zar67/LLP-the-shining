//
// Created by Zoe on 16/12/2019.
//

#include "Room.h"
#include <iostream>

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
}

void Room::updateObjectsInRoom(ASGE::Renderer* renderer,
                               double delta_time,
                               Player* player)
{
  for (int i = 0; i < demons.size(); i++)
  {
    demons.at(i)->update(renderer, delta_time, player);
  }

  for (int i = 0; i < ghosts.size(); i++)
  {
    ghosts.at(i)->update(delta_time,
                         player->spriteComponent()->getSprite()->xPos(),
                         player->spriteComponent()->getSprite()->yPos());
  }

  // check if any enemies have beeb killed
  checkEnemyHealth();
}

void Room::addDemonToRoom(ASGE::Renderer* renderer, float x_pos, float y_pos)
{
  Demon* new_demon = new Demon();
  demons.push_back(new_demon);
  demons.at(demons.size() - 1)->setup(renderer, x_pos, y_pos);
}

void Room::addGhostToRoom(ASGE::Renderer* renderer, float x_pos, float y_pos)
{
  Ghost* new_ghost = new Ghost();
  ghosts.push_back(new_ghost);
  ghosts.at(ghosts.size() - 1)->setup(renderer, x_pos, y_pos);
}

/*
 * pass enemy memory location up to game.cpp
 * this is so player can access and detect collison
 */
std::vector<GameObject*> Room::getEnemies()
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

void Room::removeItemToRoom(int item_index)
{
  if (item_index < items.size())
  {
    items.erase(items.begin() + item_index);
  }
}
void Room::addItemToRoom(ASGE::Renderer* renderer, float x_pos, float y_pos)
{
  Items* new_Item = new Items();
  items.push_back(new_Item);
  items.at(items.size() - 1)->setUpItems(renderer, x_pos, y_pos);
}