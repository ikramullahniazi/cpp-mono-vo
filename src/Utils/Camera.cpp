#include "Camera.hpp"

Camera::Camera()
{
  // DON'T USE THIS EVER
}


Camera::Camera(
    cv::Mat K, 
    cv::Mat D, 
    cv::Size size)
{
  // Check K conforms
  // ...
  this->K = K;

  // Check dist conforms
  // ...
  this->D = D;

  // Check size conforms
  // ...
  this->size = size;
}

std::vector<cv::Point2f> Camera::normalize_points(
    std::vector<cv::Point2f> pixel_coords)
{
  std::vector<cv::Point2f> normalized_pts;

  // Purely convert to normalized coords
  cv::undistortPoints(
      pixel_coords, 
      normalized_pts, 
      K, 
      D);
  return normalized_pts;
}


std::vector<cv::Point2f> project_points(
    std::vector<cv::Point3f> world_points)
{
  std::vector<cv::Point2f> temp;
  return temp;
}

