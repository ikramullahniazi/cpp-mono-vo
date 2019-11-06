#include "Utils/Frame.hpp"

// Constructors
Frame::Frame()
{
  pose = Pose();
  id = -1;
  is_keyframe = false;
  is_processed = false;
}

Frame::Frame(
    feature_map_t features,
    Pose pose,
    int id,
    bool is_keyframe,
    bool is_processed)
{
  features = features;
  pose = pose;
  id = id;
  is_keyframe = is_keyframe;
  is_processed = is_processed;
}

