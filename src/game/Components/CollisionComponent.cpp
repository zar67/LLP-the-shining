//
// Created by Owner on 17/12/2019.
//

#include "CollisionComponent.h"

/**
 *   @brief   Calculates if this component has collided with an other
 *   @details Uses AABB collision
 *   @param   collided The other collider to check for collision with
 *   @return  True if collided
 */
bool CollisionComponent::hasCollided(const CollisionComponent& collided)
{
  float collided_box[4];
  collided.getBoundingBox(collided_box);

  return (bounding_box[0] >= collided_box[0] &&
            bounding_box[0] <= collided_box[0] + collided_box[2] ||
          bounding_box[0] + bounding_box[2] >= collided_box[0] &&
            bounding_box[0] + bounding_box[2] <=
              collided_box[0] + collided_box[2]) &&
         (bounding_box[1] >= collided_box[1] &&
            bounding_box[1] <= collided_box[1] + collided_box[3] ||
          bounding_box[1] + bounding_box[3] >= collided_box[1] &&
            bounding_box[1] + bounding_box[3] <=
              collided_box[1] + collided_box[3]);
}

/**
 *   @brief   Calculates which side the collision is on
 *   @details Finds the side of the collided component that the collision has
 * occured on
 *   @param   collided The bounding box to find the side of
 *   @return  SIDE_NONE, SIDE_LEFT, SIDE_RIGHT, SIDE_TOP, SIDE_BOTTOM
 */
CollisionComponent::CollisionSide
CollisionComponent::getCollisionSide(const CollisionComponent& collided)
{
  float other_box[4];
  collided.getBoundingBox(other_box);

  float left_depth = bounding_box[0] + bounding_box[2] - other_box[0];
  float right_depth = other_box[0] + other_box[2] - bounding_box[0];
  float top_depth = bounding_box[1] + bounding_box[3] - other_box[1];
  float bottom_depth = other_box[1] + other_box[3] - bounding_box[1];

  if (left_depth < right_depth && left_depth < top_depth &&
      left_depth < bottom_depth)
  {
    return CollisionSide::SIDE_LEFT;
  }

  if (right_depth < left_depth && right_depth < top_depth &&
      right_depth < bottom_depth)
  {
    return CollisionSide::SIDE_RIGHT;
  }

  if (top_depth < left_depth && top_depth < right_depth &&
      top_depth < bottom_depth)
  {
    return CollisionSide::SIDE_TOP;
  }

  if (bottom_depth < left_depth && bottom_depth < right_depth &&
      bottom_depth < top_depth)
  {
    return CollisionSide::SIDE_BOTTOM;
  }

  return CollisionSide::SIDE_NONE;
}

/**
 *   @brief   Update the position of the bounding box
 *   @details Every time collision is checked update the bounding box to the
 * position of the sprite
 *   @param   rect The values to update to
 */
void CollisionComponent::updateBoundingBox(const float rect[4])
{
  for (int i = 0; i < BOX_SIZE; ++i)
  {
    bounding_box[i] = rect[i];
  }
}

/**
 *   @brief   Gets the bounding box of the component
 *   @param   out_rect The array to update the values of
 */
void CollisionComponent::getBoundingBox(float (&out_rect)[4]) const
{
  for (int i = 0; i < BOX_SIZE; ++i)
  {
    out_rect[i] = bounding_box[i];
  }
}
