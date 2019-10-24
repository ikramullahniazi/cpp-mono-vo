#ifndef POSE_HPP_INCLUDE
#define POSE_HPP_INCLUDE

#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp>

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
    cv::Mat get_transformation_matrix();

    // Setters
    bool set_pose(cv::Mat rotation,
        cv::Mat translation);


    // Data
  private:
    // Owned Objects

    // Functions
    bool set_rotation_vector_(cv::Mat rotation_vector);
    bool set_rotation_matrix_(cv::Mat rotation_matrix);
    bool set_translation_vector_(cv::Mat translation_vector);
    bool set_transformation_matrix_(cv::Mat rotation_matrix,
        cv::Mat translation_vector);

    bool set_rotation_(cv::Mat rotation); // easy way to handle both rot. types

    // Data
    cv::Mat rotation_vector_;
    cv::Mat rotation_matrix_;
    cv::Mat translation_vector_;
    cv::Mat transformation_matrix_;
};

#endif
