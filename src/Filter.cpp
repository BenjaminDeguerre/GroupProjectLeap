#include "Filter.hpp"

Filter::Filter() {
}

Leap::Vector Filter::filterMean(std::vector<Leap::Vector> positions){
  float x = 0, y = 0,z = 0;
  int size = static_cast<int>(positions.size());

  for (int i = 0; i < size; i++) {
    x += positions[i].x;
    y += positions[i].y;
    z += positions[i].z;
  }
  return Leap::Vector(x/size, y/size, z/size);
}

//Leap::Vector Filter::filterMeanFinger(std::vector<Leap::Finger> fingers) {
//	float x = 0, y = 0, z = 0;
//
//	for (int i = 0; i < fingers.size(); i++) {
//		x += fingers[i].tipPosition().x;
//		y += fingers[i].tipPosition().y;
//		z += fingers[i].tipPosition().z;
//	}
//	if (fingers.size() == 0) {
//		return Leap::Vector(50,50, 50);
//	}
//	return Leap::Vector(x / fingers.size(), y / fingers.size(), z / fingers.size());
//}
