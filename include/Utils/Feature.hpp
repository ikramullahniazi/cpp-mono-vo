#ifndef FEATURE_HPP_INCLUDE
#define FEATURE_HPP_INCLUDE

#include <vector>
#include <map>
#include <opencv2/core.hpp>

// This is a data class to store detected 2d features in an image


class Feature {
  public:
    // ------------
    // Constructors
    // ------------
    Feature();
    Feature(cv::Point2f coords,
        cv::Mat descriptor,
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
    cv::Mat descriptor; // feature descriptor
    int id; // unique identifier for this feature
    int frame_id; // what frame was this observation from?
    int age; // how many frames has this been seen in?
};

// Structure to map feature ID to feature object
typedef std::map<int, Feature> feature_map_t;

std::vector<cv::Point2f> unpack_feature_vector(
    std::vector<Feature> features);


#endif
