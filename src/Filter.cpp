#include "Filter.hpp"

Filter::Filter() {}

Leap::Vector Filter::filterMean(std::vector<Leap::Vector> positions) {
  float x = 0, y = 0, z = 0;
  int size = static_cast<int>(positions.size());

  for (int i = 0; i < size; i++) {
    x += positions[i].x;
    y += positions[i].y;
    z += positions[i].z;
  }
  return Leap::Vector(x / size, y / size, z / size);
}
