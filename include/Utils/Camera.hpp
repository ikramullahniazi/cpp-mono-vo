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
    Camera(
        cv::Mat K, 
        cv::Mat dist, 
        cv::Size size);

    // ---------
    // Functions
    // ---------
    std::vector<cv::Point2f> normalize_points(
        std::vector<cv::Point2f> pixel_coords);

    std::vector<cv::Point2f> project_points(
        std::vector<cv::Point3f> world_points);
    
    // ----
    // Data
    // ----
    // Intrinsic Matrix (3x3)
    cv::Mat K;

    // Distortion Coefficients (1x5)
    cv::Mat D;

    // Image size (width, height)
    cv::Size size;

  private:
};

#endif
