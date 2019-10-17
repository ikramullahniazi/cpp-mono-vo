#ifndef DEFAULT_DETECTOR_HPP_INCLUDE
#define DEFAULT_DETECTOR_HPP_INCLUDE

#include <vector>
#include <exception>
#include <iostream>

#include <opencv2/core.hpp>

#include "Utils/Feature.hpp"
// TODO: Define params and detectors in same file

// Superclasses
#include "Detector/Detector.hpp"

/*
 * Params class
 */

class DefaultDetectorParams: public DetectorParams {
  public:
    // Methods
    DefaultDetectorParams();
    void config_();

    // Data
    int max_corners_;
    double quality_level_;
    double min_distance_;
    int block_size_;
    // Note: Masks should be externally provided.
    int gradient_size_;
    bool use_harris_detector_;
    double k_;
};

/*
 * The detector class take in images and detects feature points.
 */

class DefaultDetector: public Detector {
  public:
    DefaultDetector();
    DefaultDetector(DefaultDetectorParams params);

    // Detect feature points in an incoming image.
    // This expects a monochrome image.
    // This should be overwritten by child classes. 
    // TODO: Include functionality for forcing features to be 
    // spread across image.
    // TODO: Mask can also be used to add more features to an image that already
    // has had features detected, should there be functionality to automatically
    // form a mask from existing features?
    std::vector<Feature> detect_features(const cv::Mat image);
    std::vector<Feature> detect_features(const cv::Mat image, 
        const cv::Mat mask);

    cv::Mat draw_features(const cv::Mat image, 
        const std::vector<Feature> features);
    
  private:
    // This contains the parameters to pass to the feature detection method.
    DefaultDetectorParams params_;

    // This increments every time a feature is detected.
    // Use it to assign unique ids to new features.
    uint64_t feature_counter_;
};


#endif
