// Include all utility files
#include "Utils/Camera.hpp"

// Include estimator
#include "Estimator/Estimator.hpp"

// Include detectors
#include "Detector/Detector.hpp"
#include "Detector/Detectors/DefaultDetector.hpp"

// Include trackers
#include "Tracker/Tracker.hpp"
#include "Tracker/Trackers/DefaultTracker.hpp"

// Include featuretracker
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

  std::shared_ptr<Camera> camera = std::make_shared<Camera>(camera_matrix,
      distortion_params,
      size);

  // Create Detector
  std::shared_ptr<DefaultDetector> detector = std::make_shared<DefaultDetector>();
  
  // Create Tracker
  std::shared_ptr<DefaultTracker> tracker = std::make_shared<DefaultTracker>();

  // Create FeatureTracker
  FeatureTracker feature_tracker = FeatureTracker(camera, detector, tracker);

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

