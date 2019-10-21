# Estimator

The estimator class takes in measurements from a feature tracker, (namely tracked features), and estimates poses and a map.
The estimator class then passes these estimates to an optimizer, which performs nonlinear optimization over a set of keyframes.
