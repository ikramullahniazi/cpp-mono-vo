#ifndef DEFAULT_DETECTOR_HPP_INCLUDE
#define DEFAULT_DETECTOR_HPP_INCLUDE

#include <vector>
#include <exception>
#include <iostream>

#include <opencv2/core.hpp>

#include "Utils/Feature.hpp"

// Superclasses
#include "Detector/Detector.hpp"

/*
 * Params class
 */

class DefaultDetectorParams: public DetectorParams {
  public:
    // ------------
    // Constructors
    // ------------
    DefaultDetectorParams();

    // ---------
    // Functions
    // ---------

    // ----
    // Data
    // ----
    int max_corners;
    double quality_level;
    double min_distance;
    int block_size;
    int gradient_size;
    bool use_harris_detector;
    double k;

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

/*
 * The detector class take in images and detects feature points.
 */

class DefaultDetector: public Detector {
  public:
    // ------------
    // Constructors
    // ------------
    DefaultDetector();
    DefaultDetector(DefaultDetectorParams params);

    // ---------
    // Functions
    // ---------
    feature_map_t detect_features(const cv::Mat image);

    feature_map_t detect_features(
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
    DefaultDetectorParams params_;
    
    // ---------
    // Functions
    // ---------

    // ----
    // Data
    // ----
    int feature_counter_;

};


#endif
