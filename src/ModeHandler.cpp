#include "ModeHandler.hpp"

bool ModeHandler::mode1(const StaticGesture gesture) {
	switch (gesture)
	{
		case CANCEL:
			break;
		case LEFT_ZERO_RIGHT_ONE: 
			std::cout << "a";
			break;
		case LEFT_ZERO_RIGHT_TWO: 
			std::cout << "b";
			break;
		case LEFT_ZERO_RIGHT_THREE: 
			std::cout << "c";
			break;
		case LEFT_ZERO_RIGHT_FOUR: 
			std::cout << "d";
			break;
		case LEFT_ZERO_RIGHT_FIVE: 
			std::cout << "e";
			break;
		case LEFT_ONE_RIGHT_ONE:
			std::cout << "f";
			break;
		case LEFT_ONE_RIGHT_TWO:
			std::cout << "g";
			break;
		case LEFT_ONE_RIGHT_THREE:
			std::cout << "h";
			break;
		case LEFT_ONE_RIGHT_FOUR:
			std::cout << "i";
			break;
		case LEFT_ONE_RIGHT_FIVE:
			std::cout << "j";
			break;
		case LEFT_TWO_RIGHT_ONE:
			std::cout << "k";
			break;
		case LEFT_TWO_RIGHT_TWO:
			std::cout << "l";
			break;
		case LEFT_TWO_RIGHT_THREE:
			std::cout << "m";
			break;
		case LEFT_TWO_RIGHT_FOUR:
			std::cout << "n";
			break;
		case LEFT_TWO_RIGHT_FIVE:
			std::cout << "o";
			break;
		case LEFT_THREE_RIGHT_ONE:
			std::cout << "p";
			break;
		case LEFT_THREE_RIGHT_TWO:
			std::cout << "q";
			break;
		case LEFT_THREE_RIGHT_THREE:
			std::cout << "r";
			break;
		case LEFT_THREE_RIGHT_FOUR:
			std::cout << "s";
			break;
		case LEFT_THREE_RIGHT_FIVE:
			std::cout << "t";
			break;
		case LEFT_FOUR_RIGHT_ONE:
			std::cout << "u";
			break;
		case LEFT_FOUR_RIGHT_TWO:
			std::cout << "v";
			break;
		case LEFT_FOUR_RIGHT_THREE:
			std::cout << "w";
			break;
		case LEFT_FOUR_RIGHT_FOUR:
			std::cout << "x";
			break;
		case LEFT_FOUR_RIGHT_FIVE:
			std::cout << "y";
			break;
		case LEFT_FIVE_RIGHT_ONE:
			std::cout << "z";
			break;
		case LEFT_FIVE_RIGHT_TWO:
			std::cout << ".";
			break;
		case LEFT_FIVE_RIGHT_THREE:
			std::cout << " ";
			break;
		default:
			break;
	}
  return false;
}

bool ModeHandler::mode2() {
  return false;
}

bool ModeHandler::mode3(const StaticGesture gesture, const Leap::GestureList gestures, const Leap::FingerList fingers) {

  //Switching mode if ten fingers
  if (gesture == CANCEL) {
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
