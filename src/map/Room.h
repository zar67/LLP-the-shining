//
// Created by Zoe on 16/12/2019.
//

#ifndef PROJECT_ROOM_H
#define PROJECT_ROOM_H

#include "../game/SceneObjects/Enemies/Demon.h"
#include "../game/SceneObjects/GameObject.h"
#include <string>
#include <vector>

class Room : public GameObject
{
 public:
  Room() = default;
  Room(int id,
       std::string* filename,
       int x_pos,
       int y_pos,
       bool n_door,
       bool e_door,
       bool s_door,
       bool w_door);
  ~Room();

  bool setup(ASGE::Renderer* renderer, std::string* filename);
  int getId();
  bool getNorth();
  bool getEast();
  bool getSouth();
  bool getWest();

  void renderObjectsInRoom(ASGE::Renderer* renderer);
  void updateObjectsInRoom(double delta_time, float player_x, float player_y);
  void addDemonToRoom(ASGE::Renderer* renderer, float x_pos, float y_pos);
  void removeDemonFromRoom(int demon_index);

 private:
  int ID = -1;
  bool north = false;
  bool east = false;
  bool south = false;
  bool west = false;

  std::vector<Demon*> demons;
  // std::vector<Ghost> ghosts;
  // std::vector<Item> items;
};

#endif // PROJECT_ROOM_H
