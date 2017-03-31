#include "GestValidator.hpp"


// GestControl::Handler GestControl::handler = GestControl::Handler();
//
// GestControl& GestControl::getInstance() {
// 	if (handler.instance == 0)
// 		handler.instance = new GestControl();
// 	return *handler.instance;
// }
//
// void GestControl::freeInstance() {
// 	if (handler.instance != 0)
// 		delete handler.instance;
// 	handler.instance = 0;
//
// }

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
    //validateGesture(gestureId);
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
	}

	currentGesture = gesture;
}
