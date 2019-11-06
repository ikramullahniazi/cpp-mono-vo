#include "Map.hpp"

Map::Map()
{

}

Map::Map(
    landmark_map_t landmarks,
    frame_map_t frames)
{
  landmarks_ = landmarks;
  frames_ = frames;
}

bool Map::insert_frame(Frame frame)
{
  return false;
}

bool Map::insert_landmark(Landmark landmark)
{
  return false;
}

landmark_map_t Map::get_landmarks()
{
  return landmarks_;
}

frame_map_t Map::get_frames()
{
  return frames_;
}

void Map::set_landmarks(landmark_map_t landmarks)
{
  landmarks_ = landmarks;
}

void Map::set_frames(frame_map_t frames)
{
  frames_ = frames;
}

