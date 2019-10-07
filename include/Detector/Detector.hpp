#ifndef DETECTOR_HPP_INCLUDE
#define DETECTOR_HPP_INCLUDE

#include <vector>

#include <opencv2/core.hpp>

#include "Utils/Feature.hpp"

/*
 * The detector class take in images and detects feature points.
 */

class Detector {
  public:
    Detector();
    Detector(DetectorParams params);

    // Detect feature points in an incoming image.
    // Include functionality for forcing features to be 
    // spread across image.
    std::vector<Feature> detect_features(const cv::Mat image, const std::vector<Feature> previous_features);
    
  private:
    DetectorParams params_;

    // This increments every time a feature is detected
    // Use it to assign unique ids to new features
    uint64_t feature_counter_;
};

class DetectorParams {
  public:
    DetectorParams();
  private:
    size_t minimum_features_;
};

#endif
