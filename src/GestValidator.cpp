#include "GestValidator.hpp"

void GestValidator::setFrameLimit(int limit) {
	frameLimit = limit;
}

int GestValidator::getFrameLimit() {
	return frameLimit;
}

void GestValidator::setGesture(StaticGesture gesture) {
	currentGesture = gesture;
}

StaticGesture GestValidator::getCurrentValidGesture() {
  //Call controller on the count
  if (count >= frameLimit) {
    count = 0;
    return currentGesture;
  }

  return ERROR_SG;
}

void GestValidator::update(StaticGesture gesture){

	if (currentGesture == gesture) {
		count++;
	} else {
		//if we change gesture
		count = 1;
		currentGesture = gesture;
	}
}
