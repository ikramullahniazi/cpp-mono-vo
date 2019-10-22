#ifndef CAMERA_HPP_INCLUDE
#define CAMERA_HPP_INCLUDE

#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp>

class Camera {
  public:
    // ------------
    // Constructors
    // ------------
    Camera();
    Camera(cv::Mat K, cv::Mat dist, cv::Size size);

    // ---------
    // Functions
    // ---------
    std::vector<cv::Point2f> normalize_points(std::vector<cv::Point2f> pixel_coords);
    std::vector<cv::Point2f> project_points(std::vector<cv::Point3f> world_points);
    // Getters
    cv::Mat get_intrinsic_params();
    cv::Mat get_distortion_coeffs();
    cv::Size get_size();

    // Setters
    
    // ----
    // Data
    // ----

  private:
    // -------------
    // Owned Objects
    // -------------

    // ---------
    // Functions
    // ---------

    // ----
    // Data
    // ----
    // Intrinsic Matrix (3x3)
    cv::Mat intrinsic_params_;

    // Distortion Coefficients (1x5)
    cv::Mat distortion_coeffs_;

    // Image size (width, height)
    cv::Size size_;
};

#endif
