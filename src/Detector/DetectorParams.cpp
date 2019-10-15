#include "Detector/DetectorParams.hpp"

// Create a params object with defaults for given detector.
// Parameters can then be changed after creation.
DetectorParams::DetectorParams()
{
  config_();
}

// Set default params
void DetectorParams::config_()
{
  max_corners_ = 500;
  quality_level_ = 0.01;
  min_distance_ = 10;
  block_size_ = 3;
  gradient_size_ = 3;
  use_harris_detector_ = false;
  k_ = 0.04;
}

