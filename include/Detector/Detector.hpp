#ifndef DETECTOR_HPP_INCLUDE
#define DETECTOR_HPP_INCLUDE

#include <vector>
#include <exception>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp> // For gftt

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
    std::vector<Feature> detect_features(const cv::Mat image, const std::vector<Feature> previous_features, const cv::Mat mask);
    
  private:
    // This contains the parameters to pass to the feature detection method.
    DetectorParams params_;

    // This increments every time a feature is detected.
    // Use it to assign unique ids to new features.
    uint64_t feature_counter_;
};

class DetectorParams {
  public:
    DetectorParams();
  private:

    void config_();

    // TODO: Move this to Tracker class
    size_t minimum_features_;

    int max_corners_;
    double quality_level_;
    double min_distance_;
    int block_size_;
    // Note: Masks should be externally provided.
    int gradient_size_;
    bool use_harris_detector_;
    double k_;
};

#endif
