#ifndef POSE_HPP_INCLUDE
#define POSE_HPP_INCLUDE

#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp>

// Structure that stores a rotation matrix and translation vector 

class Pose {
  public:
    // Constructors
    Pose();
    Pose(cv::Mat rotation, cv::Mat translation);

    // Data
    cv::Mat R;
    cv::Mat t;
  private:
};

cv::Mat form_transformation_matrix(
    cv::Mat R,
    cv::Mat t);

#endif
