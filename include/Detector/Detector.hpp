#ifndef DETECTOR_HPP_INCLUDE
#define DETECTOR_HPP_INCLUDE

#include <vector>
#include <exception>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp> // For gftt

#include "Utils/Feature.hpp"

/*
 * Parameters class
 */

class DetectorParams {
  public:
    // Methods
    DetectorParams();

    // All DetectorParams objects must have this function for variable set-up.
    void config_();

};

/*
 * The detector class take in images and detects feature points.
 */

class Detector {
  public:
    Detector();
    Detector(DetectorParams params);

    // Detect feature points in an incoming image.
    // This expects a monochrome image.
    // This should be overwritten by child classes. 
    virtual std::vector<Feature> detect_features(const cv::Mat image);
    virtual std::vector<Feature> detect_features(const cv::Mat image, 
        const cv::Mat mask);

    DetectorParams get_params();

  private:
    // This contains the parameters to pass to the feature detection method.
    DetectorParams params_;

    // This increments every time a feature is detected.
    // Use it to assign unique ids to new features.
    uint64_t feature_counter_;
};


#endif
