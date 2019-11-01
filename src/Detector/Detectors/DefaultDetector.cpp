#include "Detector/Detectors/DefaultDetector.hpp"

/*
 * This is the parameters class for the default detector implementation
 */

DefaultDetectorParams::DefaultDetectorParams()
{
  config_();
}

void DefaultDetectorParams::config_()
{
  // Default values taken from
  // https://docs.opencv.org/4.1.0/d2/d1d/samples_2cpp_2lkdemo_8cpp-example.html
  max_corners = 500;
  quality_level = 0.01;
  min_distance = 10;
  block_size = 3;
  gradient_size = 3;
  use_harris_detector = 0;
  k = 0.04;
}




/*
 * This is the default (reference) implementation of a feature detector.
 * It uses goodFeaturesToTrack to detect corners.
 */

DefaultDetector::DefaultDetector()
{
  // If no params are passed, use the default parameters
  params_ = DefaultDetectorParams();
  feature_counter_ = 0;
}

// Overloading constructor to require specifically DefaultDetectorParams object.
DefaultDetector::DefaultDetector(DefaultDetectorParams params)
{
  params_ = params;
}

std::vector<Feature> DefaultDetector::detect_features(const cv::Mat image)
{
  cv::Mat empty_mask = cv::Mat();
  // Run detect_features with an empty mask
  std::vector<Feature> out = detect_features(
      image,
      params_.max_corners,
      empty_mask);
  return out;
}

std::vector<Feature> DefaultDetector::detect_features(
    const cv::Mat image, 
    const int num_features_needed,
    const cv::Mat mask)
{
  std::vector<cv::Point2f> temp_output = std::vector<cv::Point2f>();
  cv::goodFeaturesToTrack(
      image, 
      temp_output,
      num_features_needed,
      params_.quality_level,
      params_.min_distance,
      mask,
      params_.block_size,
      params_.gradient_size,
      params_.use_harris_detector,
      params_.k);

  // TODO: Use subpixel optimization
  std::vector<Feature> output = std::vector<Feature>();

  for (cv::Point2f pt : temp_output) {
    Feature temp_feature = Feature(
        pt,
        cv::Mat(),
        feature_counter_++,
        -1, // -1 is used to indicate no frame assigned
        0);

    output.push_back(temp_feature);
  }

  return output;

}

// TODO: Depreciate, move functionality to Frame
cv::Mat DefaultDetector::draw_features(const cv::Mat image, 
    const std::vector<Feature> features) 
{
  // Simply draw features as red dots
  cv::Mat color_image;
  cv::cvtColor(image, color_image, cv::COLOR_GRAY2BGR);

  for (Feature f : features) {
    // Color the corresponding pixel red
    cv::Point2f coords = f.coords;
    int col = (int)coords.x;
    int row = (int)coords.y;
    color_image.at<cv::Vec3b>(row, col)[0] = 0;
    color_image.at<cv::Vec3b>(row, col)[1] = 0;
    color_image.at<cv::Vec3b>(row, col)[2] = 255;
  }

  return color_image;
}
