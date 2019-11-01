#ifndef LANDMARK_HPP_INCLUDE
#define LANDMARK_HPP_INCLUDE

#include <vector>
#include <map>

#include <opencv2/core.hpp>

#include "Utils/Feature.hpp" // Features are measurments of landmarks

// This class represents 3D landmarks 

class Landmark {
  public:
    // ------------
    // Constructors
    // ------------
    Landmark();
    Landmark(
        int id,
        cv::Point3f location);
    Landmark(
        int id,
        cv::Point3f location, 
        std::vector<Feature> observations);
    
    // ---------
    // Functions
    // ---------
    
    // ----
    // Data
    // ----
    // Unique ID
    int id;
    // Location relative to origin of map
    cv::Point3f location;

    // Keep track of all observations of this landmark
    std::vector<Feature> observations;
};

// Map landmark ID to landmark object
typedef std::map<int, Landmark> landmark_map_t;

std::vector<cv::Point3f> unpack_landmark_vector(
    std::vector<Landmark> landmarks);

#endif
