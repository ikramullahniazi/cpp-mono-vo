#include "Detector/Detector.hpp"

/*
 * This is the parent class for all DetectorParams.
 * No functions are implemented.
 */
DetectorParams::DetectorParams()
{
  config_();
}

// Set default params
void DetectorParams::config_()
{

}


/*
 * This is the parent class for all Detectors.
 * No functions are implemented.
 */

Detector::Detector()
{
  // If no params are passed, use the default parameters
  params_ = DetectorParams();
}

Detector::Detector(DetectorParams params)
{
  params_ = params;
}

std::vector<Feature> Detector::detect_features(const cv::Mat image)
{
  std::vector<Feature> out;
  return out;
}

std::vector<Feature> Detector::detect_features(const cv::Mat image, 
    const cv::Mat mask)
{
  std::vector<Feature> out;
  return out;

}

DetectorParams Detector::get_params()
{
  return params_;
}
