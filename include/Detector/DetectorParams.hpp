#ifndef DETECTOR_PARAMS_HPP_INCLUDE
#define DETECTOR_PARAMS_HPP_INCLUDE

class DetectorParams {
  public:
    // Methods
    DetectorParams();
    void config_();

    // Data
    // TODO: Move this to Tracker class
    int minimum_features_;

    int max_corners_;
    double quality_level_;
    double min_distance_;
    int block_size_;
    // Note: Masks should be externally provided.
    int gradient_size_;
    bool use_harris_detector_;
    double k_;
};

#endif
