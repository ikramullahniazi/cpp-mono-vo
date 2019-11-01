#include "Utils/Frame.hpp"

// Constructors
Frame::Frame()
{
  pose = Pose();
  frame_id = 0;
  is_keyframe = false;
  is_processed = false;
}

Frame::Frame(
    std::vector<Feature> features,
    Pose pose,
    int frame_id,
    bool is_keyframe,
    bool is_processed)
{
  features = features;
  pose = pose;
  frame_id = frame_id;
  is_keyframe = is_keyframe;
  is_processed = is_processed;
}

