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

    // If not using an actual descriptor (ie ORB), this can store the pixel 
    // patch around the feature for direct methods(?).
    cv::Mat descriptor;
    uint64_t id; // unique identifier for this feature
    uint64_t frame_id; // what frame was this observation from?
  private:
    // Nothing yet
};

#endif
