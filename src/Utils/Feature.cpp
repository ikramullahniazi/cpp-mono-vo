#include "Feature.hpp"

Feature::Feature()
{
  this->coords = cv::Point2f();
  this->descriptor = cv::Mat();
  this->id = -1;
  this->frame_id = -1;
  this->age = 0;
}

Feature::Feature(cv::Point2f coords,
    cv::Mat descriptor,
    int id,
    int frame_id,
    int age)
{
  this->coords = coords;
  this->descriptor = descriptor;
  this->id = id;
  this->frame_id = frame_id;
  this->age = age;
}

