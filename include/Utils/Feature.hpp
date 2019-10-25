#ifndef FEATURE_HPP_INCLUDE
#define FEATURE_HPP_INCLUDE

#include <vector>
#include <opencv2/core.hpp>

// This is a data class to store detected 2d features in an image
// TODO: Should this be a struct?

class Feature {
  public:
    // ------------
    // Constructors
    // ------------
    Feature();
    Feature(cv::Point2f coords,
        // cv::Mat descriptor,
        int id,
        int frame_id,
        int age);

    // ---------
    // Functions
    // ---------

    // ----
    // Data
    // ----
    cv::Point2f coords; // pixel observation 
    // cv::Mat descriptor; // feature descriptor
    int id; // unique identifier for this feature
    int frame_id; // what frame was this observation from?
    int age; // how many frames has this been seen in?
};


#endif
