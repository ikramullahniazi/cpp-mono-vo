#ifndef FRAME_HPP_INCLUDE
#define FRAME_HPP_INCLUDE

#include <vector>
#include <opencv2/core.hpp>

#include "Utils/Feature.hpp"

/*
 * 
 */

class Frame {
  public:
    // Constructors
    Frame(); // Do not use for the time being
    Frame(cv::Mat image,
        std::vector<Feature> features,
        cv::Mat rvec_;
        cv::Mat tvec_,
        bool is_keyframe);

    // Functions
    bool is_keyframe();

    // Data

  private:
    // Owned objects

    // Functions

    // Data
    cv::Mat image_;

    // Feature observations in this image
    std::vector<Feature> features_;

    // Pose of the camera when this image was taken
    cv::Mat rvec_;
    cv::Mat tvec_;

    // Whether or not this is a keyframe
    bool is_keyframe_;
};
