//
// Created by Owner on 17/12/2019.
//

#ifndef PROJECT_COLLISIONCOMPONENT_H
#define PROJECT_COLLISIONCOMPONENT_H

class CollisionComponent
{
 public:
  enum class CollisionSide
  {
    SIDE_NONE = 0,
    SIDE_TOP = 1,
    SIDE_BOTTOM = 2,
    SIDE_LEFT = 3,
    SIDE_RIGHT = 4
  };

 public:
  CollisionComponent() = default;

  bool hasCollided(const CollisionComponent& collided);
  CollisionSide getCollisionSide(const CollisionComponent& collided);

  void updateBoundingBox(const float rect[4]);

  void getBoundingBox(float (&out_rect)[4]) const;

 private:
  static const int BOX_SIZE = 4;
  float bounding_box[BOX_SIZE]{}; // x,y,width,height
};

#endif // PROJECT_COLLISIONCOMPONENT_H
