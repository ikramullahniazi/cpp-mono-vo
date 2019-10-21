#include "Camera.hpp"

Camera::Camera()
{
  // DON'T USE THIS EVER, MAYBE REMOVE?
}


Camera::Camera(cv::Mat K, cv::Mat dist, cv::Size size)
{
  // Check K conforms
  // ...
  intrinsic_params_ = K;

  // Check dist conforms
  // ...
  distortion_coeffs_ = dist;

  // Check size conforms
  // ...
  size_ = size;
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

cv::Mat Camera::get_intrinsic_params()
{
  return intrinsic_params_;
}

cv::Mat Camera::get_distortion_coeffs()
{
  return distortion_coeffs_;
}

cv::Size Camera::get_size()
{
  return size_;
}

