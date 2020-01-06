//
// Created by Zoe on 16/12/2019.
//

#ifndef PROJECT_MAP_H
#define PROJECT_MAP_H

#include "Room.h"
#include <vector>
#include "../game/SceneObjects/GameObject.h"

class Map
{
 public:
  Map() = default;
  ~Map() = default;

  void moveNorth();
  void moveEast();
  void moveSouth();
  void moveWest();
  Room* getCurrentRoom();
  void renderCurrentRoom(ASGE::Renderer* renderer);
  void renderMiniMap(ASGE::Renderer* renderer);
  bool generateRooms(ASGE::Renderer* renderer);
  bool setupMinimap(ASGE::Renderer* renderer, int game_width, int game_height);

 private:
  std::string needNorthDoor(int x_pos, int y_pos);
  std::string needEastDoor(int x_pos, int y_pos);
  std::string needSouthDoor(int x_pos, int y_pos);
  std::string needWestDoor(int x_pos, int y_pos);
  bool checkRoomName(std::string name, std::string required_doors);

  int map_size = 5;
  Room rooms[5][5];
  std::vector<GameObject> mini_map;
  int current_room = map_size / 2 * map_size + (map_size / 2);
};

#endif // PROJECT_MAP_H
