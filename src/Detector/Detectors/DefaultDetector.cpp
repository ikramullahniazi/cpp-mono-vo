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
  max_corners_ = 500;
  quality_level_ = 0.01;
  min_distance_ = 10;
  block_size_ = 3;
  gradient_size_ = 3;
  use_harris_detector_ = 0;
  k_ = 0.04;
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
  cv::Mat mask;
  // Run detect_features with an empty mask
  std::vector<Feature> out = detect_features(image, mask);
  return out;
}

std::vector<Feature> DefaultDetector::detect_features(const cv::Mat image, 
    const cv::Mat mask)
{
  std::vector<cv::Point2f> temp_output;
  std::vector<Feature> output;
  cv::goodFeaturesToTrack(image, temp_output,
      params_.max_corners_,
      params_.quality_level_,
      params_.min_distance_,
      mask,
      params_.block_size_,
      params_.gradient_size_,
      params_.use_harris_detector_,
      params_.k_);

  // TODO: Use subpixel optimization

  for (cv::Point2f pt : temp_output) {
    Feature temp_feature(pt);
    temp_feature.id = feature_counter_++;
    output.push_back(temp_feature);
  }
  
  return output;

}

cv::Mat DefaultDetector::draw_features(const cv::Mat image, 
    const std::vector<Feature> features) 
{
  // Simply draw features as red dots
  cv::Mat color_image;
  cv::cvtColor(image, color_image, cv::COLOR_GRAY2BGR);

  for (Feature f : features) {
    // Color the corresponding pixel red
    cv::Point2f coords = f.raw_coords;
    int col = (int)coords.x;
    int row = (int)coords.y;
    color_image.at<cv::Vec3b>(row, col)[0] = 0;
    color_image.at<cv::Vec3b>(row, col)[1] = 0;
    color_image.at<cv::Vec3b>(row, col)[2] = 255;
  }

  return color_image;
}
