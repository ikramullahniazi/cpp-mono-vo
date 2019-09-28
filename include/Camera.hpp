#ifndef CAMERA_HPP_INCLUDE
#define CAMERA_HPP_INCLUDE

#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp> // For undistortPoints()

class Camera {
  public:
    Camera(cv::Mat K, cv::Mat dist);
    std::vector<cv::Point2f> normalize_points(std::vector<cv::Point2f> pixel_coords);
    std::vector<cv::Point2f> project_points(std::vector<cv::Point3f> world_points);
  private:
    cv::Mat intrinsic_params_;
    cv::Mat distortion_coeffs_;
};

#endif
