#include "ModeHandler.hpp"

#include <string>
#include <stdio.h>

ModeHandler::ModeHandler(): a(0.1), b(0.075), c(-0.3), d(-0.495), g(0.02), z1(0.3), z2(0.1) {}
bool ModeHandler::mode1(const StaticGesture gesture) {
	if (letterSelected) {
    std::string s;
		switch (gesture) {
			case LEFT_ZERO_RIGHT_ZERO:
				std::cout << "Cancel, selecting new letter." << std::endl;
				letterSelected = false;
				break;
			case LEFT_FIVE_RIGHT_FIVE:
				std::cout << "Accept : " << letterMode1 << std::endl << "Selecting new letter." << std::endl;
				writeLetter(letterMode1);
				letterSelected = false;
				break;
			case FIVE_FINGERS_LEFT_HAND:
				letterSelected = false;
				strcpy(letterMode1, "!");
				communicator.sendData(letterMode1);
				return false;
				break;
			default:
				break;
		}
	} else {
		switch (gesture) {
			case LEFT_ZERO_RIGHT_ONE:
        strcpy(letterMode1, "a");
				letterSelected = true;
				break;
			case LEFT_ZERO_RIGHT_TWO:
				strcpy(letterMode1, "b");
				letterSelected = true;
				break;
			case LEFT_ZERO_RIGHT_THREE:
				strcpy(letterMode1, "c");
				letterSelected = true;
				break;
			case LEFT_ZERO_RIGHT_FOUR:
				strcpy(letterMode1, "d");
				letterSelected = true;
				break;
			case LEFT_ZERO_RIGHT_FIVE:
				strcpy(letterMode1, "e");
				letterSelected = true;
				break;
			case LEFT_ONE_RIGHT_ONE:
				strcpy(letterMode1, "f");
				letterSelected = true;
				break;
			case LEFT_ONE_RIGHT_TWO:
				strcpy(letterMode1, "g");
				letterSelected = true;
				break;
			case LEFT_ONE_RIGHT_THREE:
				strcpy(letterMode1, "h");
				letterSelected = true;
				break;
			case LEFT_ONE_RIGHT_FOUR:
				strcpy(letterMode1, "i");
				letterSelected = true;
				break;
			case LEFT_ONE_RIGHT_FIVE:
				strcpy(letterMode1, "j");
				letterSelected = true;
				break;
			case LEFT_TWO_RIGHT_ONE:
				strcpy(letterMode1, "k");
				letterSelected = true;
				break;
			case LEFT_TWO_RIGHT_TWO:
				strcpy(letterMode1, "l");
				letterSelected = true;
				break;
			case LEFT_TWO_RIGHT_THREE:
				strcpy(letterMode1, "m");
				letterSelected = true;
				break;
			case LEFT_TWO_RIGHT_FOUR:
				strcpy(letterMode1, "n");
				letterSelected = true;
				break;
			case LEFT_TWO_RIGHT_FIVE:
				strcpy(letterMode1, "o");
				letterSelected = true;
				break;
			case LEFT_THREE_RIGHT_ONE:
				strcpy(letterMode1, "p");
				letterSelected = true;
				break;
			case LEFT_THREE_RIGHT_TWO:
				strcpy(letterMode1, "q");
				letterSelected = true;
				break;
			case LEFT_THREE_RIGHT_THREE:
				strcpy(letterMode1, "r");
				letterSelected = true;
				break;
			case LEFT_THREE_RIGHT_FOUR:
				strcpy(letterMode1, "s");
				letterSelected = true;
				break;
			case LEFT_THREE_RIGHT_FIVE:
				strcpy(letterMode1, "t");
				letterSelected = true;
				break;
			case LEFT_FOUR_RIGHT_ONE:
				strcpy(letterMode1, "u");
				letterSelected = true;
				break;
			case LEFT_FOUR_RIGHT_TWO:
				strcpy(letterMode1, "v");
				letterSelected = true;
				break;
			case LEFT_FOUR_RIGHT_THREE:
				strcpy(letterMode1, "w");
				letterSelected = true;
				break;
			case LEFT_FOUR_RIGHT_FOUR:
				strcpy(letterMode1, "x");
				letterSelected = true;
				break;
			case LEFT_FOUR_RIGHT_FIVE:
				strcpy(letterMode1, "y");
				letterSelected = true;
				break;
			case LEFT_FIVE_RIGHT_ONE:
				strcpy(letterMode1, "z");
				letterSelected = true;
				break;
			case LEFT_FIVE_RIGHT_TWO:
				strcpy(letterMode1, ".");
				letterSelected = true;
				break;
			case LEFT_FIVE_RIGHT_THREE:
				strcpy(letterMode1, " ");
				letterSelected = true;
				break;
			case FIVE_FINGERS_LEFT_HAND:
				letterSelected = false;
				std::cout << "Leaving mode 1" << '\n';
				return false;
				break;
			default:
				break;
		}
		if (letterSelected) {
			std::cout << "Selected letter : " << letterMode1 << std::endl;
		}
	}
  return true;
}

bool ModeHandler::mode2(const StaticGesture gesture, const Leap::GestureList gestures, const Leap::FingerList fingers) {

  Leap::Vector newPosition;

  //Switching mode if ten fingers
  if (gesture == LEFT_ZERO_RIGHT_ZERO) {
    cv::destroyWindow("My image");
    return false;
  }

  if (gesture == GRAB_ONE_HAND) {
    stopMode3 = true;
  }
  else if (gesture != ERROR_SG) {
    stopMode3 = false;

    if (fingers.count() != 0) {
      positions.clear();
      for (Leap::FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); fl++) {
        if ((*fl).type() == 1) {
          newPosition = (*fl).tipPosition();
        }
      }
      actual.y = -static_cast<int>(newPosition.y) + rows - 40;
      actual.x = static_cast<int>(newPosition.x) * 2 + cols / 2;
      positions.push_back(newPosition);
    }
  }

  //Looking for a swipe (to be changed for dynamic gestures)
  for (int g = 0; g < gestures.count(); ++g) {
  	Leap::Gesture gesture = gestures[g];
  	switch (gesture.type()) {
  	case Leap::Gesture::TYPE_SWIPE:
  		image.setTo(cv::Scalar(255));
  		cv::imshow("My image", image);
  		cv::waitKey(300);
  		break;
  	default:
  		break;
  	}
  }

  if (!stopMode3 && fingers.count() > 0) {
  	Leap::Vector fingerTip;
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
		std::cout << fingerTip.x << '\n';
		std::cout << fingerTip.y << '\n';
    fingerTip.x = fingerTip.x / 1000;
    fingerTip.y = fingerTip.y / 1000;
    if (fingerTip.x > 1 || fingerTip.x < -1) {
      fingerTip.x = 0;
    }
    if (fingerTip.y > 1 || fingerTip.y < -1) {
      fingerTip.y = 0;
    }
  	if (fingerTip.x != 0 && fingerTip.y != 0) {
      sprintf(buffer, "movel(p[%f, %f, %f, 0, 3.14, 0])\n", fingerTip.x + 0.160, fingerTip.y - 0.58, z2);
      std::string s = buffer;
      communicator.sendData(buffer, false, s.size());
  		previous.x = actual.x;
  		previous.y = actual.y;
  		actual.y = -static_cast<int>(fingerTip.y) + rows - 40;
  		actual.x = static_cast<int>(fingerTip.x) * 2 + cols / 2;
  		line(image, previous, actual, cv::Scalar(0, 0, 0), 5);
      cv::imshow("My image", image);
      cv::waitKey(40);
  	}
  }
  return true;
}

void ModeHandler::writeLetter(char *letter) {
	switch (*letter) {
		case 'a':
			writeLetterA();
			break;
		case 'b':
			writeLetterB();
			break;
		case 'c':
			writeLetterC();
			break;
		default:
			std::cout << "Unknown letter." << '\n'; //Should not go through here
			break;
	}
}

void ModeHandler::writeLetterA() {
	//sprintf(buffer, "set_pos(%f, %f, %f, 0, 3.14, 0)\n", c, d, z1);
	//std::cout << c << '\n';
	//communicator.sendData(buffer);
  std::string s;
  sprintf(buffer, "movel(p[%f, %f, %f, 0, 3.14, 0])\r\n", c, d, z2);
  s.append(buffer);
  communicator.sendData(buffer, true, s.size());

  
	sprintf(buffer, "movel(p[%f, %f, %f, 0, 3.14, 0])\r\n", c+(b/2), d+a, z2);
  s.clear();
  s.append(buffer);
	communicator.sendData(buffer, true, s.size());

	sprintf(buffer, "movel(p[%f, %f, %f, 0, 3.14, 0])\r\n", c+b, d, z2);
  s.clear();
  s.append(buffer);
	communicator.sendData(buffer, true, s.size());

	sprintf(buffer, "movel(p[%f, %f, %f, 0, 3.14, 0])\r\n", c+b, d, z1);
  s.clear();
  s.append(buffer);
	communicator.sendData(buffer, true, s.size());

	sprintf(buffer, "movel(p[%f, %f, %f, 0, 3.14, 0])\r\n", c, d+(a/3), z1);
  s.clear();
  s.append(buffer);
	communicator.sendData(buffer, true, s.size());

	sprintf(buffer, "movel(p[%f, %f, %f, 0, 3.14, 0])\r\n", c, d+(a/3), z2);
  s.clear();
  s.append(buffer);
	communicator.sendData(buffer, true, s.size());

	sprintf(buffer, "movel(p[%f, %f, %f, 0, 3.14, 0])\r\n", c+b, d+(a/3), z2);
  s.clear();
  s.append(buffer);
	communicator.sendData(buffer, true, s.size());

	sprintf(buffer, "movel(p[%f, %f, %f, 0, 3.14, 0])\r\n", c+b, d+(a/3), z1);
  s.clear();
  s.append(buffer);
	communicator.sendData(buffer, true, s.size());

	sprintf(buffer, "movel(p[%f, %f, %f, 0, 3.14, 0])\r\n", c+b, d, z1);
  s.clear();
  s.append(buffer);
	communicator.sendData(buffer, true, s.size());

	sprintf(buffer, "movel(p[%f, %f, %f, 0, 3.14, 0])\r\n", c+b+g, d, z1);
  s.clear();
  s.append(buffer);
	communicator.sendData(buffer, true, s.size());

	c = c+b+g;
}

void ModeHandler::writeLetterB() {
	sprintf(buffer, "set_pos(%f, %f, %f, 0, 3.14, 0)\r\n", c, d, z1);
	std::cout << c << '\r\n';
	communicator.sendData(buffer);

	sprintf(buffer, "movel(p[%f, %f, %f, 0, 3.14, 0])\r\n", c, d, z2);
	communicator.sendData(buffer);

	sprintf(buffer, "movel(p[%f, %f, %f, 0, 3.14, 0])\r\n", c, d + a, z2);
	communicator.sendData(buffer);

	sprintf(buffer, "movel(p[%f, %f, %f, 0, 3.14, 0])\r\n", c + (3*b/4), d+a, z2);
	communicator.sendData(buffer);

	sprintf(buffer, "movel(p[%f, %f, %f, 0, 3.14, 0])\r\n", c + b, d+(7*a/8), z2);
	communicator.sendData(buffer);

	sprintf(buffer, "movel(p[%f, %f, %f, 0, 3.14, 0])\r\n", c + b, d + (5 * a / 8), z2);
	communicator.sendData(buffer);

	sprintf(buffer, "movel(p[%f, %f, %f, 0, 3.14, 0])\r\n", c + (3*b/4), d + (a / 2), z2);
	communicator.sendData(buffer);

	sprintf(buffer, "movel(p[%f, %f, %f, 0, 3.14, 0])\r\n", c, d + (a / 2), z2);
	communicator.sendData(buffer);

	sprintf(buffer, "movel(p[%f, %f, %f, 0, 3.14, 0])\r\n", c+(3*b/4), d + (a / 2), z2);
	communicator.sendData(buffer);

	sprintf(buffer, "movel(p[%f, %f, %f, 0, 3.14, 0])\r\n", c + b, d + (3*a / 8), z2);
	communicator.sendData(buffer);

	sprintf(buffer, "movel(p[%f, %f, %f, 0, 3.14, 0])\r\n", c + b, d + (a / 8), z2);
	communicator.sendData(buffer);

	sprintf(buffer, "movel(p[%f, %f, %f, 0, 3.14, 0])\r\n", c + (3*b/4), d, z2);
	communicator.sendData(buffer);

	sprintf(buffer, "movel(p[%f, %f, %f, 0, 3.14, 0])\r\n", c, d, z2);
	communicator.sendData(buffer);

	sprintf(buffer, "movel(p[%f, %f, %f, 0, 3.14, 0])\r\n", c, d, z1);
	communicator.sendData(buffer);

	sprintf(buffer, "movel(p[%f, %f, %f, 0, 3.14, 0])\r\n", c + b + g, d, z1);
	communicator.sendData(buffer);

	c = c + b + g;


}

void ModeHandler::writeLetterC() {
	sprintf(buffer, "set_pos(%f, %f, %f, 0, 3.14, 0)\r\n", c, d, z1);
	std::cout << c << '\r\n';
	communicator.sendData(buffer);

	sprintf(buffer, "movel(p[%f, %f, %f, 0, 3.14, 0])\r\n", c+b, d+(7*a/8), z1);
	communicator.sendData(buffer);

	sprintf(buffer, "movel(p[%f, %f, %f, 0, 3.14, 0])\r\n", c + b, d + (7 * a / 8), z2);
	communicator.sendData(buffer);

	sprintf(buffer, "movel(p[%f, %f, %f, 0, 3.14, 0])\r\n", c + (3*b / 4), d + a, z2);
	communicator.sendData(buffer);

	sprintf(buffer, "movel(p[%f, %f, %f, 0, 3.14, 0])\r\n", c + (b/4), d+a, z2);
	communicator.sendData(buffer);

	sprintf(buffer, "movel(p[%f, %f, %f, 0, 3.14, 0])\r\n", c, d + (7*a / 8), z2);
	communicator.sendData(buffer);

	sprintf(buffer, "movel(p[%f, %f, %f, 0, 3.14, 0])\r\n", c, d+(a/8), z2);
	communicator.sendData(buffer);

	sprintf(buffer, "movel(p[%f, %f, %f, 0, 3.14, 0])\r\n", c+(b/4), d, z2);
	communicator.sendData(buffer);

	sprintf(buffer, "movel(p[%f, %f, %f, 0, 3.14, 0])\r\n", c+(3*b/4), d, z2);
	communicator.sendData(buffer);

	sprintf(buffer, "movel(p[%f, %f, %f, 0, 3.14, 0])\r\n", c + b, d + (a / 8), z2);
	communicator.sendData(buffer);

	sprintf(buffer, "movel(p[%f, %f, %f, 0, 3.14, 0])\r\n", c + b, d + (a / 8), z1);
	communicator.sendData(buffer);

	sprintf(buffer, "movel(p[%f, %f, %f, 0, 3.14, 0])\r\n", c + b + g, d, z1);
	communicator.sendData(buffer);

	c = c + b + g;
}