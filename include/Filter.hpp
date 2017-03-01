#ifndef FILTER
#define FILTER

#include <iostream>
#include <cstring>
#include "Leap.h"
#include <iostream>  // standard C++ I/O


class Filter {
public:
  Filter();
  Leap::Vector filterMeanHand(std::vector<Leap::Frame> frame, int id);

};

#endif