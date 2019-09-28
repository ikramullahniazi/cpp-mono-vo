#include "Camera.hpp"

Camera::Camera()
{

}


Camera::Camera(cv::Mat K, cv::Mat dist)
{
  // Check K conforms
  // ...
  intrinsic_params_ = K;

  // Check dist conforms
  // ...
  distortion_coeffs_ = dist;
}

std::vector<cv::Point2f> Camera::normalize_points(std::vector<cv::Point2f> pixel_coords)
{
  std::vector<cv::Point2f> normalized_pts;

  // Purely convert to normalized coords
  cv::undistortPoints(pixel_coords, normalized_pts, intrinsic_params_, cv::Mat() );
  return normalized_pts;
}


std::vector<cv::Point2f> project_points(std::vector<cv::Point3f> world_points)
{
  std::vector<cv::Point2f> temp;
  return temp;
}

