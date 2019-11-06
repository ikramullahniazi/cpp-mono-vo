#ifndef FEATURE_HPP_INCLUDE
#define FEATURE_HPP_INCLUDE

#include <vector>
#include <map>
#include <tuple>
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

// I hate this struct.
typedef struct FeatureMapAsVectors {
  std::vector<cv::Mat> descriptors;
  std::vector<cv::Point2f> coords;
  std::vector<int> ids;
  std::vector<int> frame_ids;
  std::vector<int> ages;
} FeatureMapAsVectors;

FeatureMapAsVectors unpack_feature_map(feature_map_t features);

std::pair<feature_map_t, feature_map_t> match_feature_maps(
    feature_map_t features_1,
    feature_map_t features_2);

#endif
