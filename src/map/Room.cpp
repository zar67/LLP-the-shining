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
}

bool Room::setup(ASGE::Renderer* renderer, std::string* filename)
{
  addSpriteComponent(renderer, *filename);

  int num_objs = rand() % 4;
  for (int i = 0; i < num_objs; ++i)
  {
    bool next_obj = false;
    GameObject* object = new GameObject();
    do
    {
      object->addCollisionComponent();
      object->addSpriteComponent(renderer, texture_dir);

      int x_rand = 100 + rand() % 450;
      int y_rand = 100 + rand() % 250;
      object->spriteComponent()->getSprite()->xPos(x_rand);
      object->spriteComponent()->getSprite()->yPos(y_rand);
      object->spriteComponent()->getSprite()->width(40);
      object->spriteComponent()->getSprite()->height(40);

      object->updateCollisionComponent();

      for (auto& obj : interactable_objs)
      {
        if (object->collisionComponent()->hasCollided(
              *obj->collisionComponent()))
        {
          break;
        }
      }
      next_obj = true;
    } while (!next_obj);

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
  for (auto& obj : interactable_objs)
  {
    renderer->renderSprite(*obj->spriteComponent()->getSprite());
  }
}

void Room::updateObjectsInRoom(ASGE::Renderer* renderer,
                               double delta_time,
                               Player* player)
{
  for (int i = 0; i < demons.size(); i++)
  {
    demons.at(i)->update(renderer, delta_time, player, interactable_objs);
  }

  bool doors[4] = { north, east, south, west };
  for (int i = 0; i < ghosts.size(); i++)
  {
    ghosts.at(i)->update(delta_time,
                         player->spriteComponent()->getSprite()->xPos(),
                         player->spriteComponent()->getSprite()->yPos(),
                         interactable_objs,
                         doors);
  }

  // check if any enemies have been killed
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
  for (auto& obj : interactable_objs)
  {
    enemies.push_back(obj);
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

std::vector<GameObject*> Room::getObjectsInRoom()
{
  return interactable_objs;
}
