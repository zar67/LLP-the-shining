//
// Created by Zoe on 16/12/2019.
//

#include "Room.h"
#include <iostream>

Room::Room(int id,
           std::string* filename,
           int x_pos,
           int y_pos,
           bool n_door,
           bool e_door,
           bool s_door,
           bool w_door)
{
  ID = id;
  north = n_door;
  east = e_door;
  south = s_door;
  west = w_door;
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
}

int Room::getId()
{
  return ID;
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
}

void Room::updateObjectsInRoom(double delta_time,
                               float player_x,
                               float player_y)
{
  for (int i = 0; i < demons.size(); i++)
  {
    demons.at(i)->update(delta_time, player_x, player_y);
  }

  for (int i = 0; i < ghosts.size(); i++)
  {
    ghosts.at(i)->update(delta_time, player_x, player_y);
  }
}

void Room::addDemonToRoom(ASGE::Renderer* renderer, float x_pos, float y_pos)
{
  Demon* new_demon = new Demon();
  demons.push_back(new_demon);
  demons.at(demons.size() - 1)->setup(renderer, x_pos, y_pos);
}

void Room::removeDemonFromRoom(int demon_index)
{
  if (demon_index < demons.size())
  {
    demons.erase(demons.begin() + demon_index);
  }
}

void Room::addGhostToRoom(ASGE::Renderer* renderer, float x_pos, float y_pos)
{
  Ghost* new_ghost = new Ghost();
  ghosts.push_back(new_ghost);
  ghosts.at(ghosts.size() - 1)->setup(renderer, x_pos, y_pos);
}

void Room::removeGhostFromRoom(int ghost_index)
{
  if (ghost_index < ghosts.size())
  {
    ghosts.erase(ghosts.begin() + ghost_index);
  }
}
