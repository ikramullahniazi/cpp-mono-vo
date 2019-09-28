#ifndef FEATURE_HPP_INCLUDE
#define FEATURE_HPP_INCLUDE

#include <vector>
#include <opencv2/core.hpp>

// This is a data class to store detected 2d features in an image

class Feature {
  public:
    // Constructors
    Feature();
    Feature(cv::Point2f raw);
    Feature(cv::Point2f raw, cv::Point2f normalized);

    // Data is publicly accessible
    cv::Point2f normalized_coords;
    cv::Point2f raw_coords;
    cv::Mat descriptor; // Unused for purely optical flow tracking
    uint64_t id;
  private:
    // Nothing yet
};

#endif
