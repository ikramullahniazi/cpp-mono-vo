#include "Utils/Frame.hpp"

// Constructors
Frame::Frame()
{
  image_ = cv::Mat();
  pose_ = Pose();
  frame_id_ = 0;
  is_keyframe_ = false;
  is_processed_ = false;
}

Frame::Frame(cv::Mat image,
    std::vector<Feature> features,
    Pose pose,
    uint64_t frame_id,
    bool is_keyframe,
    bool is_processed);
{
  image_ = image;
  features_ = features;
  pose_ = pose;
  frame_id_ = frame_id;
  is_keyframe_ = is_keyframe;
  is_processed_ = is_processed;
}


// Functions
// Getters
bool Frame::get_is_keyframe()
{
  return is_keyframe_;
}

bool Frame::get_is_processed()
{
  return is_processed_;
}

cv::Mat Frame::get_image()
{
  return image_;
}

std::vector<Feature> Frame::get_features()
{
  return features_;
}

Pose Frame::get_pose()
{
  return pose_;
}

void Frame::set_is_keyframe(bool is_keyframe)
{
  is_keyframe_ = is_keyframe;
}

void Frame::set_is_processed(bool is_processed)
{
  is_processed_ = is_processed;
}

void Frame::set_image(cv::Mat image)
{
  image_ = image;
}

void Frame::set_features(std::vector<Feature> features)
{
  features_ = features;
}

void Frame::set_pose(Pose pose)
{
  pose_ = pose;
}
