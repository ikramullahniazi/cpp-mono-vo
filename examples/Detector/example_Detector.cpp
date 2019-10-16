#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

#include "Detector/Detectors/DefaultDetector.hpp"

// This example demonstrates how to use a Detector to extract features from an 
// image.

int main() {
  // Read in image
  std::string image_path = "../data/000000.png";

  cv::Mat image_color = cv::imread(image_path);
  cv::Mat image_mono;
  cv::cvtColor(image_color, image_mono, cv::COLOR_BGR2GRAY);

  // Create detector
  DefaultDetector det;

  std::vector<Feature> detections = det.detect_features(image_mono);

  cv::Mat output_image = det.draw_features(image_mono, detections);

  cv::imshow("Detections", output_image);
  cv::waitKey(0);

  return 0;
}

