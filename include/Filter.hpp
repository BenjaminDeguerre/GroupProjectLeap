#ifndef FILTER
#define FILTER

#include <iostream>
#include <cstring>

#include "Leap.h"

class Filter {
public:
  Filter();
  Leap::Vector filterMean(std::vector<Leap::Vector> positions);

private:
};

#endif