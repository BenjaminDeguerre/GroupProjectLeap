

#include <iostream>
#include <cstring>
#include "Leap.h"
#include <iostream>  // standard C++ I/O

using namespace Leap;

class Filter {
public:
  Filter();
  Vector filterMeanHand(std::vector<Frame> frame, int id);

};
