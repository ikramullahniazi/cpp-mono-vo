// Include all utility files
#include "Utils/Camera.hpp"
#include "Utils/Feature.hpp"
#include "Utils/Frame.hpp"
#include "Utils/Landmark.hpp"
#include "Utils/Map.hpp"
#include "Utils/Pose.hpp"

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
#include <chrono>

int main() {
  auto X = cv::Mat(4, 4, CV_32F);
  double low = -10;
  double high = 10;
  cv::randu(X, cv::Scalar(low), cv::Scalar(high));
  std::cout << "X: " << X << std::endl;

  auto Y = X(cv::Rect(0,0, 4, 3));
  std::cout << "Y: " << Y << std::endl;

  auto K = cv::Mat::eye(3, 3, CV_32F);
  std::cout << "K*Y" << K*Y << std::endl;

  return 0;
}

