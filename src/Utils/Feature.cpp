#include "Feature.hpp"

Feature::Feature()
{
  raw_coords = cv::Point2f();
  descriptor = cv::Mat();
  id = 0;
  frame_id = 0;
}

Feature::Feature(cv::Point2f raw)
{
  raw_coords = raw;

  descriptor = cv::Mat();
  id = 0;
  frame_id = 0;
}

