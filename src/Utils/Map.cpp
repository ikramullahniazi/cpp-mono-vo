#include "Map.hpp"

Map::Map()
{

}

bool Map::insert_frame(Frame frame)
{
  return false;
}

bool Map::insert_landmark(Landmark landmark)
{
  return false;
}

std::vector<Landmark> Map::get_landmarks()
{
  return landmarks_;
}

std::vector<Frame> Map::get_keyframes()
{
  return keyframes_;
}

void Map::set_landmarks(std::vector<Landmark> landmarks)
{
  landmarks_ = landmarks;
}

void Map::set_keyframes(std::vector<Frame> keyframes)
{
  keyframes_ = keyframes;
}

