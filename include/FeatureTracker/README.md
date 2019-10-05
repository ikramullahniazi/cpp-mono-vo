# FeatureTracker

The FeatureTracker class takes in images, generates feature points, and tracks these points from image to image.
It sends these features and their pixel locations (measurements) to the Estimator.
The FeatureTracker class owns a detector for generating image points and a Tracker for matching these points across images.
