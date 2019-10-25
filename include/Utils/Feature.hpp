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
    Feature(cv::Point2f raw);

    // ---------
    // Functions
    // ---------

    // ----
    // Data
    // ----
    cv::Point2f raw_coords;
    cv::Mat descriptor;
    uint64_t id; // unique identifier for this feature
    uint64_t frame_id; // what frame was this observation from?

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


#endif
