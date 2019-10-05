#ifndef TRACKER_HPP_INCLUDE
#define TRACKER_HPP_INCLUDE

#include <vector>

#include <opencv2/core.hpp>

#include "Utils/Feature.hpp"

class Tracker {
  public:
    Tracker();
    // TODO: How to actually extract tracking functionality?
    // Current thought: take in prev, cur -> return new prev, cur
    // What's the best way to return two vectors?
  private:
    // 
};

class TrackerParams {
  public:
    TrackerParams();
  private:
    //
};

#endif
