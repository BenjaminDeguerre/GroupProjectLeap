#include "Filter.hpp"

Filter::Filter() {
}

Leap::Vector Filter::filterMeanHand(std::vector<Leap::Frame> frames, int id){
  float x = 0, y = 0,z = 0;

  for (int i = 0; i < frames.size(); i++) {
    x += frames[i].hand(id).palmPosition().x;
    y += frames[i].hand(id).palmPosition().y;
    z += frames[i].hand(id).palmPosition().z;
  }
  return Leap::Vector(x / frames.size(), y / frames.size(), z / frames.size());
}
