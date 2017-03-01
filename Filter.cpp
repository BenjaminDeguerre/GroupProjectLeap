#include "Filter.hpp"

Filter::Filter(){}

Vector Filter::filterMeanHand(std::vector<Frame> frames, int id){
  float x = 0, y = 0,z = 0;

  for (int i = 0; i < frames.size(); i++) {
    x += frames.hand(id).palmPosition().x;
    y += frames.hand(id).palmPosition().y;
    z += frames.hand(id).palmPosition().z;
  }
  return Vector(x / frames.size(), y / frames.size(), z / frames.size());
}
