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
