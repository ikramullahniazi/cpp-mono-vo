#include "Landmark.hpp"

Landmark::Landmark()
{

}

Landmark::Landmark(
    int id,
    cv::Point3f coords)
{
  this->id = id;
  this->coords = coords;
}

Landmark::Landmark(
    int id,
    cv::Point3f coords,
    std::vector<Feature> observations)
{
  this->id = id;
  this->coords = coords;
  this->observations = observations;
}

LandmarkMapAsVectors unpack_landmark_map(
    landmark_map_t landmarks)
{
  LandmarkMapAsVectors out_struct;
  std::vector<cv::Point3f> coords;
  std::vector<int> ids;
  std::vector<std::vector<Feature>> observations;
  
  for (auto const& f : landmarks)
  {
    Landmark temp_landmark = f.second;
    coords.push_back(temp_landmark.coords);
    ids.push_back(temp_landmark.id);
    observations.push_back(temp_landmark.observations);
  }

  out_struct.coords = coords;
  out_struct.ids = ids;
  out_struct.observations = observations;

  return out_struct;
}
