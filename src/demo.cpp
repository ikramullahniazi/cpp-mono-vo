#include "Camera.hpp"
#include "Estimator.hpp"
#include "FeatureTracker.hpp"

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp> // for imshow
#include <opencv2/imgcodecs.hpp> // for imread()

#include <iostream>

int main() {
  // Set up camera parameters
  cv::Mat camera_matrix = (cv::Mat_<double>(3,3) << 718.856, 0.0, 607.1928, 0.0, 718.856, 185.2157, 0.0, 0.0, 1.0);
  cv::Mat distortion_params;
  Camera cam = Camera(camera_matrix, distortion_params);

  return 0;
}

