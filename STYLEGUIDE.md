# Style Guide

This project uses a subset of the Google C++ style guide.
Important information is consolidated here.

## Versioning

This project targets C++11.

## Header Files

Every .cpp file should have an associated .hpp file, excluding examples and small files containing main() functions.

Every .hpp file should have an include guard of the form:

```c++
#ifndef FILE_NAME_HPP_INCLUDE
#define FILE_NAME_HPP_INCLUDE 

#endif
```

## Namespaces

Everything should be in a namespace.

## Variables

Variables should be initialized as close to declaration as possible.

## Functions

* Prefer return values over output parameters.
* Prefer short functions over long ones.

## Naming

* Classes: MyClass, FeatureTracker
* Variables:
  * local_variable
  * private_variable_
* Functions DoThing(), DetectFeatures()

## Comments

### Classes

Each class declaration should have an associated comment describing what it is for and how it should be used.

### Functions

Each function declaration should have an associated comment describing what the function does and how to use it.
Comments should mention:
* Inputs and Outputs (with any needed assumptions)
* Performance implications
* Whether manual memory management is needed 
