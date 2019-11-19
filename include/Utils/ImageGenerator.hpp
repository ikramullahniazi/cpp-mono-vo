#ifndef IMAGE_GENERATOR_HPP_INCLUDE
#define IMAGE_GENERATOR_HPP_INCLUDE

#include <queue>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

class ImageGenerator {
  public:
    ImageGenerator();
    bool load_images(std::string folder_name, std::string filetype);
    bool empty();
    cv::Mat get_next_image();

  private:
    std::queue<cv::Mat> images_;
};

#endif
