#include "Map.hpp"

Map::Map()
{

}

bool Map::add_frame(Frame frame)
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
