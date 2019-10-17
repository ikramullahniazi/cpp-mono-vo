#include "Utils/Camera.hpp"
#include "Estimator/Estimator.hpp"
#include "FeatureTracker/FeatureTracker.hpp"

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp> // for imshow
#include <opencv2/imgcodecs.hpp> // for imread()

#include <iostream>
#include <vector>

int main() {
  
  // This is just a test run on some Kitti data

  // Set up camera parameters
  cv::Mat camera_matrix = (cv::Mat_<double>(3,3) << 718.856, 0.0, 607.1928, 0.0, 718.856, 185.2157, 0.0, 0.0, 1.0);
  cv::Mat distortion_params;
  Camera cam = Camera(camera_matrix, distortion_params);

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
  //
  
  return 0;
}

