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
#include <queue>
#include <chrono>

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
  cv::Mat camera_matrix = (cv::Mat_<float>(3,3) << 718.856, 0.0, 607.1928, 0.0, 718.856, 185.2157, 0.0, 0.0, 1.0);
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
  EstimatorParams estimator_params;
  Estimator estimator = Estimator(
      camera_ptr,
      map_ptr,
      estimator_params);

  // Create Optimizer
  // ...

  // Now ready to actually process images

  // Grab images
  std::vector<std::string> filenames;
  std::queue<cv::Mat> images;
  std::string path = "../data/*.png";
  cv::glob(path, filenames);

  for (std::string filename : filenames)
  {
    cv::Mat im = cv::imread(filename);
    cv::cvtColor(im, im, cv::COLOR_BGR2GRAY);
    images.push(im);
  }

  // Initialize map from first two images
  // ...
  
  cv::Mat image_1 = images.front();
  Frame frame_1 = feature_tracker.process_image(image_1);
  images.pop();
  // Skip second image
  images.pop();

  cv::Mat image_3 = images.front();
  Frame frame_3 = feature_tracker.process_image(image_3);
  images.pop();

  estimator.manual_initialization(
      frame_1,
      frame_3);

  // Initialize from frame 1 and 3
  // ...
  
  // Run for rest of images
  while (!images.empty())
  {
    Frame current_frame = feature_tracker.process_image(images.front());
    current_frame = estimator.process_frame(current_frame);
    images.pop();
  }
  
  return 0;
}

