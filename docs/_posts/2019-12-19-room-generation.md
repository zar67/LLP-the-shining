---
layout: post
title: Random Room Generation
date: 2019-12-06 16:00:00
description: "Room Generation Algorithm"
published: true
category: Development
tags: 
- algorithm
- random-generation
- low-level-programming
---

After spending some time thinking about how I wanted to generate the rooms I came up with a basic algorithm, derived from previous projects, that I could use.

The brief algorithm for setting up the random room generation is:
* Generate starting room, with all 4 doors
* Create a queue of rooms to generate based on open doors
* For each room in the queue
    * Check surrounding rooms for doors
    * Select the required doors
    * Randomly generate a room with the correct doors
    * Add new rooms to generate to queue
* Generate mini map

With this algorithm I can start to make the map of the game. There will be two main classes I need to do this: Map and Room.

Rooms inherit from GameObject, they have a type to determine what should be in the room and a boolean for each door. Each room also has a unique ID to help locate them in the 2D array I plan to use in the Map.
The Map class controls everything about the Rooms from generation to updating to rendering. Rooms will be stored in a 2D array. I contemplated using a vector for this, but decided on an array since the size of the map is static and using a 2D array will be easier for finding adjacent rooms in the generation.

<center><img src="{{ site.baseurl }}/assets/room_uml.png" alt="room uml" style="height: 350px;" /></center><br>

RoomType determines what should be put into the room, normal rooms will have enemies generated in them, item rooms will only have a certain number of items and the exit room will have a staircase down to the next floor. Items and Enemies will be stored in the rooms so that they can be rendered only when the player is in their room. 

```
  enum RoomType
  {
    NORMAL,
    ITEM,
    EXIT
  };
```

The locations of the rooms to be generated will be help in a std::queue. I will need an x and y index to access the room since the Rooms array in Map will be 2D.
For example, this is how the queue will be setup, and how the first rooms to generate will be added.

```
  std::queue<std::array<int, 2>> rooms_to_generate;
  rooms_to_generate.push({ 2, 1 });
  rooms_to_generate.push({ 1, 2 });
  rooms_to_generate.push({ 2, 3 });
  rooms_to_generate.push({ 3, 2 });
```

Using a std::queue will allow me to add new rooms to generate to the back and generate rooms in order by generating rooms at the front of the queue first.
After a room is correctly setup and complete it can be removed from the queue with the pop() method, which removes the first element in the queue.

After setting up the room generation and enabling the rooms to be switched between by just a press of a button, the Map is fully generated and working.
In order for the Rooms to be fully completed, I need to setup the collision on the walls, I'm not entirely sure how to do this and also need to wait for the CollisionComponent to be fully setup before beginning work on this. 

So, for now, the Map is done.
Next onto the UI System and the Scene Manager.