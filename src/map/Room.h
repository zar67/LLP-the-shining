//
// Created by Zoe on 16/12/2019.
//

#ifndef PROJECT_ROOM_H
#define PROJECT_ROOM_H

#include "../game/SceneObjects/Enemies/Demon.h"
#include "../game/SceneObjects/Enemies/Ghost.h"
#include "../game/SceneObjects/GameObject.h"
#include <string>
#include <vector>

class Room : public GameObject
{
 public:
  enum RoomType
  {
    NORMAL,
    ITEM,
    EXIT
  };

  Room() = default;
  Room(int id,
       RoomType room_type,
       bool n_door,
       bool e_door,
       bool s_door,
       bool w_door);
  ~Room();

  bool setup(ASGE::Renderer* renderer, std::string* filename);

  int getId();
  RoomType getType();
  void setType(RoomType room_type);

  bool getNorth();
  bool getEast();
  bool getSouth();
  bool getWest();

  bool canMove();
  void canMove(bool movement);

  void renderObjectsInRoom(ASGE::Renderer* renderer);
  void updateObjectsInRoom(double delta_time, float player_x, float player_y);

  void addDemonToRoom(ASGE::Renderer* renderer, float x_pos, float y_pos);
  void removeDemonFromRoom(int demon_index);
  void addGhostToRoom(ASGE::Renderer* renderer, float x_pos, float y_pos);
  void removeGhostFromRoom(int ghost_index);

 private:
  int ID = -1;
  RoomType type = NORMAL;
  bool north = false;
  bool east = false;
  bool south = false;
  bool west = false;
  bool movement_enabled = true;

  std::vector<Demon*> demons;
  std::vector<Ghost*> ghosts;
  // std::vector<Item> items;
};

#endif // PROJECT_ROOM_H
