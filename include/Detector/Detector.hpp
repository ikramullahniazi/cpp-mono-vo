#ifndef DETECTOR_HPP_INCLUDE
#define DETECTOR_HPP_INCLUDE

#include <vector>
#include <exception>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp> // For gftt

#include "Utils/Feature.hpp"

/**
 * Parent class representing the parameters needed for performing feature
 * detection in an image.
 */
class DetectorParams {
  public:
    // ------------
    // Constructors
    // ------------
    DetectorParams();

    // ---------
    // Functions
    // ---------

    // ----
    // Data
    // ----

  private:
    // -------------
    // Owned Objects
    // -------------
    
    // ---------
    // Functions
    // ---------
    void config_();

    // ----
    // Data
    // ----
};

/**
 * Parent class for implementing a feature detector.
 */
class Detector {
  public:
    // ------------
    // Constructors
    // ------------
    Detector();
    Detector(DetectorParams params);
    
    // ---------
    // Functions
    // ---------
    // Detect features without constraints
    virtual feature_map_t detect_features(const cv::Mat image);
    // Detect features in an image that already has features
    virtual feature_map_t detect_features(
        const cv::Mat image,
        const int num_current_features,
        const cv::Mat mask);

    // ----
    // Data
    // ----

  private:
    // -------------
    // Owned Objects
    // -------------
    DetectorParams params_;
    
    // ---------
    // Functions
    // ---------

    // ----
    // Data
    // ----
    int feature_counter_;

};


#endif
