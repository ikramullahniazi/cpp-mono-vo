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
    Frame();
    Frame(cv::Mat image,
        std::vector<Feature> features,
        cv::Mat rotation_vector;
        cv::Mat translation_vector,
        bool is_keyframe);

    // Functions
    bool get_is_keyframe();
    cv::Mat get_image();
    std::vector<Feature> get_features();
    cv::Mat get_rotation();
    cv::Mat get_translation();

    // Data

  private:
    // Owned objects

    // Functions

    // Data
    cv::Mat image_;

    // Feature observations in this image
    std::vector<Feature> features_;

    // Pose of the camera when this image was taken
    cv::Mat rotation_vector_;
    cv::Mat translation_vector_;

    // Whether or not this is a keyframe
    bool is_keyframe_;
};
