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
  // TODO: Any needed checking
  // Use [] rather than .insert() to allow overwriting of a frame
  frames_[frame.id] = frame;
  return true;
}

bool Map::insert_landmark(Landmark landmark)
{
  // TODO: Any needed checking
  // Use [] rather than .insert() to allow overwriting
  landmarks_[landmark.id] = landmark;
  return true;
}

landmark_map_t Map::get_landmarks()
{
  return landmarks_;
}

bool Map::contains_landmark(int id)
{
  if (landmarks_.find(id) == landmarks_.end())
  {
    return false;
  }
  return true;
}

Landmark Map::get_landmark(int id)
{
  // CALL CONTAINS_LANDMARK FIRST
  return landmarks_.at(id);
}

frame_map_t Map::get_frames()
{
  return frames_;
}

bool Map::contains_frame(int id)
{
  if (frames_.find(id) == frames_.end())
  {
    return false;
  }
  return true;
}

Frame Map::get_frame(int id)
{
  return frames_.at(id);
}

void Map::set_landmarks(landmark_map_t landmarks)
{
  landmarks_ = landmarks;
}

void Map::set_frames(frame_map_t frames)
{
  frames_ = frames;
}

std::pair<feature_map_t, landmark_map_t> Map::filter_by_features(
    feature_map_t features)
{
  feature_map_t out_features;
  landmark_map_t out_landmarks;

  for (auto const& f : features)
  {
    int id = f.first;
    if (contains_landmark(id))
    {
      out_features.insert({id, f.second});
      out_landmarks.insert({id, get_landmark(id)});
    }
  }
  
  std::pair<feature_map_t, landmark_map_t> out_pair = 
    std::make_pair(out_features, out_landmarks);
  
  return out_pair;
}
