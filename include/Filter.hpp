#ifndef FILTER
#define FILTER

#include <cstring>
#include <iostream>

#include "Leap.h"

/**
 * \class Filter
 * \brief Simple filter to smooth the detection.
 **/
class Filter {
 public:
  Filter();

  /**
   * \fn Leap::Vector Filter::filterMean(std::vector<Leap::Vector> positions)
   * \brief Compute the position on all the positions in the given vector.
   * \param[in] positions A vector containing position to be averaged.
   * \return A vector containing the averaged position.
   **/
  Leap::Vector filterMean(std::vector<Leap::Vector> positions);

 private:
};
#endif
