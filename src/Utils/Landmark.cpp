#include "Landmark.hpp"

Landmark::Landmark()
{

}

Landmark::Landmark(
    int id,
    cv::Point3f location)
{
  this->id = id;
  this->location = location;
}

Landmark::Landmark(
    int id,
    cv::Point3f location,
    std::vector<Feature> observations)
{
  this->id = id;
  this->location = location;
  this->observations = observations;
}
