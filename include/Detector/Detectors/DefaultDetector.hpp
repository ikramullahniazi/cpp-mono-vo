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
    void config_();

    // ----
    // Data
    // ----
    int max_corners_;
    double quality_level_;
    double min_distance_;
    int block_size_;
    int gradient_size_;
    bool use_harris_detector_;
    double k_;
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
    std::vector<Feature> detect_features(const cv::Mat image);
    std::vector<Feature> detect_features(const cv::Mat image, 
        const cv::Mat mask);
    cv::Mat draw_features(const cv::Mat image, 
        const std::vector<Feature> features);

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
    uint64_t feature_counter_;

};


#endif
