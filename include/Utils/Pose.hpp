#ifndef POSE_HPP_INCLUDE
#define POSE_HPP_INCLUDE

#include <opencv2/core.hpp>

class Pose {
  public:
    // Constructors
    Pose();
    Pose(cv::Mat rotation, cv::Mat translation);

    // Functions
    // Getters
    cv::Mat get_rotation_vector();
    cv::Mat get_rotation_matrix();
    cv::Mat get_translation_vector();

    // Setters
    void set_rotation(cv::Mat rotation);
    void set_translation(cv::Mat translation);


    // Data
  private:
    // Owned Objects

    // Functions

    // Data
    // Rotation is represented as a 3x1 vector in modified axis-angle form
    cv::Mat rotation_;
    // Translation is represented as a 3x1 vector
    cv::Mat translation_;
};

#endif
