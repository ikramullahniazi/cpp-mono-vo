#include "Feature.hpp"

Feature::Feature()
{

}

Feature::Feature(cv::Point2f raw)
{
  raw_coords = raw;
}

Feature::Feature(cv::Point2f raw, cv::Point2f normalized)
{
  raw_coords = raw;
  normalized_coords = normalized;
}

std::vector<cv::Point2f> unpack_features(std::vector<Feature> features)
{
  std::vector<cv::Point2f> out_vec;
  return out_vec;
}

std::vector<Feature> pack_features(std::vector<cv::Point2f> points,
    std::vector<Feature> previous_features)
{
  std::vector<Feature> out_vec;
  return out_vec;
}
