//
// Created by Zoe on 16/12/2019.
//

#ifndef PROJECT_ROOM_H
#define PROJECT_ROOM_H


class Room
{
public:
    Room() = default;
    ~Room() = default;

    int getId();

private:
    // SpriteComponent* sprite = nullptr;
    // CollisionComponent* collision = nullptr;
    int ID;
    bool north;
    bool east;
    bool south;
    bool west;
};


#endif //PROJECT_ROOM_H
