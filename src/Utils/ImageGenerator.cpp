#include "Utils/ImageGenerator.hpp"

ImageGenerator::ImageGenerator()
{

}

bool ImageGenerator::load_images(std::string folder_name, std::string filetype)
{
  std::vector<std::string> filenames;
  std::string image_path = folder_name + "*" + filetype;
  cv::glob(image_path, filenames);

  for (std::string name : filenames)
  {
    cv::Mat im = cv::imread(name);
    cv::cvtColor(im, im, cv::COLOR_BGR2GRAY);
    images_.push(im);
  }

  return true;
}

bool ImageGenerator::empty()
{
  return images_.empty();
}

cv::Mat ImageGenerator::get_next_image()
{
  cv::Mat im;
  if (images_.size() != 0)
  {
    im = images_.front();
    images_.pop();
  }
  return im;
}
