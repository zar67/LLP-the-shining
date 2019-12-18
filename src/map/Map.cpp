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
  for (int i = 0; i < map_size; i++)
  {
    for (int j = 0; j < map_size; j++)
    {
      if (rooms[i][j].getId() == current_room)
      {
        return &rooms[i][j];
      }
    }
  }

  return nullptr;
}

bool Map::generateRooms()
{
  // Generate Starting Room
  rooms[map_size/2][map_size/2] = Room(12, "data/Rooms/NESW.png", 2, 2, true, true, true, true);

  // Create Queue of Rooms From Open Doors
  std::queue<std::array<int, 2>> rooms_to_generate;
  rooms_to_generate.push({ 2, 1 });
  rooms_to_generate.push({ 1, 2 });
  rooms_to_generate.push({ 2, 3 });
  rooms_to_generate.push({ 3, 2 });

  // For Each Room in the Queue
  while (!rooms_to_generate.empty())
  {
    int x_index = rooms_to_generate.front()[0];
    int y_index = rooms_to_generate.front()[1];

    if (rooms[x_index][y_index].getId() == -1)
    {
      // Calculate Required Doors (NESW)
      std::string doors_needed = needNorthDoor(x_index, y_index) + needEastDoor(x_index, y_index) +
                                 needSouthDoor(x_index, y_index) + needWestDoor(x_index, y_index);

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
      rooms[x_index][y_index] = Room(x_index * map_size + y_index,
                         "data/Rooms/" + possible_rooms[index],
                         y_index,
                         x_index,
                         possible_rooms[index][0] == 'N',
                         possible_rooms[index][1] == 'E',
                         possible_rooms[index][2] == 'S',
                         possible_rooms[index][3] == 'W');

      // Add New Rooms To Generate To Queue
      if (rooms[x_index][y_index].getNorth() && rooms[x_index - 1][y_index].getId() == -1)
      {
        rooms_to_generate.push({ x_index - 1, y_index });
      }
      if (rooms[x_index][y_index].getEast() && rooms[x_index][y_index + 1].getId() == -1)
      {
        rooms_to_generate.push({ x_index, y_index + 1 });
      }
      if (rooms[x_index][y_index].getSouth() && rooms[x_index + 1][y_index].getId() == -1)
      {
        rooms_to_generate.push({ x_index + 1, y_index });
      }
      if (rooms[x_index][y_index].getWest() && rooms[x_index][y_index - 1].getId() == -1)
      {
        rooms_to_generate.push({ x_index, y_index - 1 });
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

  for (int i = 0; i < map_size; i++)
  {
    for (int j = 0; j < map_size; j++)
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