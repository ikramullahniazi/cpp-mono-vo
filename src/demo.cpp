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

// Include estimator
#include "Estimator/Estimator.hpp"

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
   * TODO: Implement System object that handles obtaining sensor readings
   * and passing them to assorted handlers.
   */

  // --------
  // Frontend
  // --------

  // Create Camera
  cv::Mat camera_matrix = (cv::Mat_<double>(3,3) << 718.856, 0.0, 607.1928, 0.0, 718.856, 185.2157, 0.0, 0.0, 1.0);
  cv::Mat distortion_params = cv::Mat();
  cv::Size size = cv::Size(1241, 376);

  std::shared_ptr<Camera> camera_ptr = std::make_shared<Camera>(
      camera_matrix,
      distortion_params,
      size);

  // Create Detector
  std::shared_ptr<DefaultDetector> detector_ptr = std::make_shared<DefaultDetector>();
  
  // Create Tracker
  std::shared_ptr<DefaultTracker> tracker_ptr = std::make_shared<DefaultTracker>();

  // Create FeatureTracker
  FeatureTracker feature_tracker = FeatureTracker(
      camera_ptr, 
      detector_ptr, 
      tracker_ptr);

  // ----------------
  // Backend (no opt)
  // ----------------
  
  // Create map
  std::shared_ptr<Map> map_ptr = std::make_shared<Map>();

  // Create Estimator
  Estimator estimator = Estimator();

  // Create Optimizer
  // ...

  // Now ready to actually process images

  // Grab images
  std::vector<std::string> filenames = std::vector<std::string>();
  std::vector<cv::Mat> images = std::vector<cv::Mat>();
  std::string path = "../data/*.png";
  cv::glob(path, filenames);
  std::cout << filenames.size() << " images found" << std::endl;

  for (std::string filename : filenames)
  {
    cv::Mat im = cv::imread(filename);
    cv::cvtColor(im, im, cv::COLOR_BGR2GRAY);
    images.push_back(im);
  }

  // Initialize map from first two images
  // ...
  
  for (cv::Mat image : images)
  {
    Frame current_frame = feature_tracker.process_image(image);
    std::cout << "processed image" << std::endl;
  }
  
  return 0;
}

