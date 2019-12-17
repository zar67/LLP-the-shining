//
// Created by Zoe on 16/12/2019.
//

#ifndef PROJECT_ROOM_H
#define PROJECT_ROOM_H

#include <string>

class Room
{
public:
    Room() = default;
    Room(int id, std::string filename, int x, int y, bool n, bool e, bool s, bool w);
    ~Room() = default;

    int getId();
    bool getNorth();
    bool getEast();
    bool getSouth();
    bool getWest();

private:
    // SpriteComponent* sprite = nullptr;
    // CollisionComponent* collision = nullptr;
    int ID = -1;
    bool north = false;
    bool east = false;
    bool south = false;
    bool west = false;
};


#endif //PROJECT_ROOM_H
