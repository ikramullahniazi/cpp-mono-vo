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
    void config_();

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
    virtual std::vector<Feature> detect_features(const cv::Mat image);
    virtual std::vector<Feature> detect_features(const cv::Mat image, 
        const cv::Mat mask);

    DetectorParams get_params();
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
    uint64_t feature_counter_;

};


#endif
