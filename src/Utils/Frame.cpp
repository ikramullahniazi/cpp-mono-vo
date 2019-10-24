#include "Utils/Frame.hpp"

// Constructors
Frame::Frame()
{

}


Frame::Frame(cv::Mat image,
    std::vector<Feature> features,
    cv::Mat rotation_vector,
    cv::Mat translation_vector,
    bool is_keyframe)
{
  image_ = image;
  features_ = features;
  rotation_vector_ = rotation_vector;
  translation_vector_ = translation_vector;
  is_keyframe_ = is_keyframe;
}


// Functions
// Getters
bool Frame::get_is_keyframe()
{
  return is_keyframe_;
}

cv::Mat Frame::get_image()
{
  return image_;
}

std::vector<Feature> Frame::get_features()
{
  return features_;
}

cv::Mat Frame::get_rotation()
{
  return rotation_vector_;
}

cv::Mat Frame::get_translation()
{
  return translation_vector_;
}

