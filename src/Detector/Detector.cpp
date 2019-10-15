#include "Detector/Detector.hpp"

/*
 * This is the default (reference) implementation of a feature detector.
 * It uses goodFeaturesToTrack to detect corners.
 */

Detector::Detector()
{
  // If no params are passed, use the default parameters
  params_ = DetectorParams();
  feature_counter_ = 0;
}

Detector::Detector(DetectorParams params)
{
  params_ = params;
}

std::vector<Feature> Detector::detect_features(const cv::Mat image)
{
  cv::Mat mask;
  std::vector<Feature> out = detect_features(image, mask);
  return out;
}

std::vector<Feature> Detector::detect_features(const cv::Mat image, const cv::Mat mask)
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

  for (cv::Point2f pt : temp_output) {
    Feature temp_feature(pt);
    temp_feature.id = feature_counter_++;
    output.push_back(temp_feature);
  }
  
  return output;

}

cv::Mat Detector::draw_features(const cv::Mat image, 
    const std::vector<Feature> features) {
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
