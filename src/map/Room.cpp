//
// Created by Zoe on 16/12/2019.
//

#include "Room.h"

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