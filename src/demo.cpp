#include "Utils/Camera.hpp"
#include "Estimator/Estimator.hpp"
#include "FeatureTracker/FeatureTracker.hpp"

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp> // for imshow
#include <opencv2/imgcodecs.hpp> // for imread()

#include <iostream>
#include <vector>

int main() {
  
  /*
   * Part 1: Set up tracking system.
   * FeatureTracker: Takes measurements of features in the environment
   *  * Detector
   *  * Tracker
   * Estimator: Calculates position from measurements
   *  * FeatureTracker
   */

  // Create Camera
  cv::Mat camera_matrix = (cv::Mat_<double>(3,3) << 718.856, 0.0, 607.1928, 0.0, 718.856, 185.2157, 0.0, 0.0, 1.0);
  cv::Mat distortion_params;
  cv::Size size = cv::Size(1241, 376);
  Camera cam = Camera(camera_matrix, distortion_params, size);

  // Create Tracker
  // ...

  // Create Detector
  // ...

  // Create FeatureTracker
  // ...

  // Create Estimator
  // ...
  
  // Create Optimizer
  // ...

  // Now ready to actually process images

  // Grab images
  std::vector<std::string> filenames;
  std::vector<cv::Mat> images;
  std::string path = "../data/*.png";
  cv::glob(path, filenames);
  std::cout << filenames.size() << " images found" << std::endl;

  for (filename : filenames)
  {
    cv::Mat im = cv::imread(filename);
    images.push_back(im);
  }

  // Initialize map from first two images
  // ...
  
  return 0;
}

