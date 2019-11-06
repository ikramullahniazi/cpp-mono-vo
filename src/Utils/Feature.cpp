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

// TODO: Expand to extract ALL information from a map
// ex Descriptors, ids, etc
FeatureMapAsVectors unpack_feature_map(
    feature_map_t features)
{

  FeatureMapAsVectors out_struct;

  std::vector<cv::Mat> descriptors;
  std::vector<cv::Point2f> coords;
  std::vector<int> ids;
  std::vector<int> frame_ids;
  std::vector<int> ages;

  for (auto const& f : features) 
  {
    int temp_id = f.first;
    Feature temp_feature = f.second;

    coords.push_back(temp_feature.coords);
    descriptors.push_back(temp_feature.descriptor);
    ids.push_back(temp_feature.id);
    frame_ids.push_back(temp_feature.frame_id);
    ages.push_back(temp_feature.age);

  }

  out_struct.descriptors = descriptors;
  out_struct.coords = coords;
  out_struct.ids = ids;
  out_struct.frame_ids = frame_ids;
  out_struct.ages = ages;

  return out_struct;
}

std::pair<feature_map_t, feature_map_t> match_feature_maps(
    feature_map_t features_1,
    feature_map_t features_2)
{
  feature_map_t pruned_1;
  feature_map_t pruned_2;

  for (const auto& f : features_1)
  {
    int id = f.first;
    if (features_2.find(id) != features_2.end())
    {
      // Feature is in both!
      pruned_1.insert({id, f.second});
      pruned_2.insert({id, features_2.at(id)});
    }
  }

  std::pair<feature_map_t, feature_map_t> matches = std::make_pair(
      pruned_1,
      pruned_2);

  return matches;

}

