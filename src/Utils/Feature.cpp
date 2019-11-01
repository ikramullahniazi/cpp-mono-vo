#include "Feature.hpp"

Feature::Feature()
{
  this->coords = cv::Point2f();
  this->descriptor = cv::Mat();
  this->id = -1;
  this->frame_id = -1;
  this->age = 0;
}

Feature::Feature(cv::Point2f coords,
    cv::Mat descriptor,
    int id,
    int frame_id,
    int age)
{
  this->coords = coords;
  this->descriptor = descriptor;
  this->id = id;
  this->frame_id = frame_id;
  this->age = age;
}

std::vector<cv::Point2f> unpack_feature_vector(
    std::vector<Feature> features)
{
  std::vector<cv::Point2f> out_vec = std::vector<cv::Point2f>();

  for (Feature f : features) {
    cv::Point2f temp_point = f.coords;

    // Add pixel to back of vector (maintains order so can reassociate
    // if needed)
    out_vec.push_back(temp_point);
  }

  return out_vec;
}
