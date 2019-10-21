#ifndef CAMERA_HPP_INCLUDE
#define CAMERA_HPP_INCLUDE

#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp> // For undistortPoints()

class Camera {
  public:
    Camera();
    Camera(cv::Mat K, cv::Mat dist, cv::Size size);
    std::vector<cv::Point2f> normalize_points(std::vector<cv::Point2f> pixel_coords);
    std::vector<cv::Point2f> project_points(std::vector<cv::Point3f> world_points);
    cv::Mat get_intrinsic_params();
    cv::Mat get_distortion_coeffs();
    cv::Size get_size();

  private:
    // Intrinsic Matrix (3x3)
    cv::Mat intrinsic_params_;

    // Distortion Coefficients (idk what size)
    cv::Mat distortion_coeffs_;

    // Image size (width, height)
    cv::Size size_;
};

#endif
