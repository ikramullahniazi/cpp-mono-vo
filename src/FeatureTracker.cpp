#include "FeatureTracker.hpp"

FeatureTracker::FeatureTracker(Camera cam)
{
  cam_ = cam;
}

bool FeatureTracker::process_image(cv::Mat image)
{
  return false;
}

std::vector<Feature> FeatureTracker::get_data()
{
  return std::vector<Feature>;
}

