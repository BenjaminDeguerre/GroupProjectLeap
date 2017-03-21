#include "ModeHandler.hpp"

bool ModeHandler::mode1() {
  return false;
}

bool ModeHandler::mode2() {
  return false;
}

bool ModeHandler::mode3(const StaticGesture gesture, const Leap::GestureList gestures, const Leap::FingerList fingers) {

  //Switching mode if ten fingers
  if (gesture == TEN_FINGERS) {
    cv::destroyWindow("My image");
    return false;
  }

  //Looking for a swipe (to be changed for dynamic gestures)
  for (int g = 0; g < gestures.count(); ++g) {
  	Leap::Gesture gesture = gestures[g];
  	switch (gesture.type()) {
  	case Leap::Gesture::TYPE_SWIPE:
  		image.setTo(cv::Scalar(255));
  		cv::imshow("My image", image);
  		cv::waitKey(100);
  		break;
  	default:
  		break;
  	}
  }

  //Drawing
  if (gesture != GRAB_ONE_HAND && fingers.count() > 0) {
  	Leap::Vector newPosition, fingerTip;
  	Leap::FingerList::const_iterator fl = fingers.begin();
  	if (fingers.count() != 0) {
  		for (Leap::FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); fl++) {
  			if ((*fl).type() == 1) {
  				newPosition = (*fl).tipPosition();
  			}
  		}
  	}


  	if (numberOfPositions < historicSize) {
  		positions.insert(positions.begin(), newPosition);
  		numberOfPositions++;
  	}
  	else {
  		positions.pop_back();
  		positions.insert(positions.begin(), newPosition);
  	}

  	fingerTip = filter.filterMean(positions);
  	if (fingerTip.x != 0 && fingerTip.y != 0) {
  		previous.x = actual.x;
  		previous.y = actual.y;
  		actual.y = -static_cast<int>(fingerTip.y) + rows - 40;
  		actual.x = static_cast<int>(fingerTip.x) * 2 + cols / 2;
  		line(image, previous, actual, cv::Scalar(0, 0, 0), 5);
  	}
  }
  return true;
}

bool ModeHandler::mode4() {
  return false;
}
