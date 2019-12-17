//
// Created by Zoe on 16/12/2019.
//

#include <Engine/FileIO.h>
#include <array>
#include <iostream>
#include <queue>

#include "Map.h"

void Map::changeRooms(int new_ID)
{
  current_room = new_ID;
}

Room* Map::getCurrentRoom()
{
  for (auto row : rooms)
  {
    for (auto room : rooms)
    {
      if (room->getId() == current_room)
      {
        return room;
      }
    }
  }

  return nullptr;
}

bool Map::generateRooms()
{
  // Generate Starting Room
  rooms[2][2] = Room(
    num_initialised_rooms, "data/Rooms/NESW.png", 2, 2, true, true, true, true);
  num_initialised_rooms += 1;

  // Create Queue of Rooms From Open Doors
  std::queue<std::array<int, 2>> rooms_to_generate;
  rooms_to_generate.push({ 2, 1 });
  rooms_to_generate.push({ 1, 2 });
  rooms_to_generate.push({ 2, 3 });
  rooms_to_generate.push({ 3, 2 });

  // For Each Room in the Queue
  while (!rooms_to_generate.empty())
  {
    int x = rooms_to_generate.front()[0];
    int y = rooms_to_generate.front()[1];

    if (rooms[x][y].getId() == -1)
    {
      // Calculate Required Doors (NESW)
      std::string doors_needed = needNorthDoor(x, y) + needEastDoor(x, y) +
                                 needSouthDoor(x, y) + needWestDoor(x, y);

      // Randomly Select Room with Correct Doors
      // Directory: data/Rooms/NESW.png
      // _ = No Door
      std::vector<std::string> possible_rooms;

      // For Each File
      std::vector<std::string> files = ASGE::FILEIO::enumerateFiles("data/"
                                                                    "Rooms");
      for (auto name : files)
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
      rooms[x][y] = Room(num_initialised_rooms,
                         "data/Rooms/" + possible_rooms[index],
                         y,
                         x,
                         possible_rooms[index][0] == 'N',
                         possible_rooms[index][1] == 'E',
                         possible_rooms[index][2] == 'S',
                         possible_rooms[index][3] == 'W');
      num_initialised_rooms += 1;

      // Add New Rooms To Generate To Queue
      if (rooms[x][y].getNorth() && rooms[x - 1][y].getId() == -1)
      {
        rooms_to_generate.push({ x - 1, y });
      }
      if (rooms[x][y].getEast() && rooms[x][y + 1].getId() == -1)
      {
        rooms_to_generate.push({ x, y + 1 });
      }
      if (rooms[x][y].getSouth() && rooms[x + 1][y].getId() == -1)
      {
        rooms_to_generate.push({ x + 1, y });
      }
      if (rooms[x][y].getWest() && rooms[x][y - 1].getId() == -1)
      {
        rooms_to_generate.push({ x, y - 1 });
      }

      // Remove This Room from Queue
      rooms_to_generate.pop();
    }
    else
    {
      // Remove This Room from Queue
      rooms_to_generate.pop();
    }
  }

  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      std::cout << i << ", " << j << " : " << rooms[i][j].getId() << "->"
                << rooms[i][j].getNorth() << ", " << rooms[i][j].getEast()
                << ", " << rooms[i][j].getSouth() << ", "
                << rooms[i][j].getWest() << std::endl;
    }
    std::cout << std::endl;
  }

  return true;
}

std::string Map::needNorthDoor(int x, int y)
{
  if (x - 1 >= 0)
  {
    if (rooms[x - 1][y].getId() != -1)
    {
      if (rooms[x - 1][y].getSouth())
      {
        return "N";
      }
      else
      {
        return "_";
      }
    }
    else
    {
      return "*";
    }
  }
  else
  {
    return "_";
  }
}

std::string Map::needEastDoor(int x, int y)
{
  if (y + 1 < 5)
  {
    if (rooms[x][y + 1].getId() != -1)
    {
      if (rooms[x][y + 1].getWest())
      {
        return "E";
      }
      else
      {
        return "_";
      }
    }
    else
    {
      return "*";
    }
  }
  else
  {
    return "_";
  }
}

std::string Map::needSouthDoor(int x, int y)
{
  if (x + 1 < 5)
  {
    if (rooms[x + 1][y].getId() != -1)
    {
      if (rooms[x + 1][y].getNorth())
      {
        return "S";
      }
      else
      {
        return "_";
      }
    }
    else
    {
      return "*";
    }
  }
  else
  {
    return "_";
  }
}

std::string Map::needWestDoor(int x, int y)
{
  if (y - 1 >= 0)
  {
    if (rooms[x][y - 1].getId() != -1)
    {
      if (rooms[x][y - 1].getEast())
      {
        return "W";
      }
      else
      {
        return "_";
      }
    }
    else
    {
      return "*";
    }
  }
  else
  {
    return "_";
  }
}

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