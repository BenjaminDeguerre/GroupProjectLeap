#include "DetectionListener.hpp"

void DetectionListener::onInit(const Leap::Controller& controller) {
	std::cout << "Initialized" << std::endl;
}

void DetectionListener::onConnect(const Leap::Controller& controller) {
	std::cout << "Connected" << std::endl;
	controller.enableGesture(Leap::Gesture::TYPE_CIRCLE);
	controller.enableGesture(Leap::Gesture::TYPE_KEY_TAP);
	controller.enableGesture(Leap:: Gesture::TYPE_SCREEN_TAP);
	controller.enableGesture(Leap::Gesture::TYPE_SWIPE);
}

void DetectionListener::onDisconnect(const Leap::Controller& controller) {
	// Note: not dispatched when running in a debugger.
	std::cout << "Disconnected" << std::endl;
}

void DetectionListener::onExit(const Leap::Controller& controller) {
	std::cout << "Exited" << std::endl;
}

void DetectionListener::onFrame(const Leap::Controller& controller) {

	// Get the most recent frame and report some basic information
	const Leap::Frame frame = controller.frame();
	Gesture gest(frame.hands());

	if (mode == 0) {
		switch (gest.getGesture()) {
			case ONE_FINGER_ONE_HAND:
				//mode 1 - select text and print it on the screen
				std::cout << "selecting mode 1" << '\n';
				mode = 1;
				break;
			case TWO_FINGERS_ONE_HAND:
				//mode 2 - writing with gestures
				std::cout << "selecting mode 2" << '\n';
				mode = 2;
				break;
			case THREE_FINGERS_ONE_HAND:
				//mode 3 - drawing by finger
				std::cout << "selecting mode 3" << '\n';
				mode = 3;
				break;
			case FOUR_FINGERS_ONE_HAND:
				//mode 4 - moving the robot
				std::cout << "selecting mode 4" << '\n';
				mode = 4;
				break;
			default:
				//do nothing and wait for detection.
				std::cout << "nothing to do" << '\n';
				break;
		}
	} else if (mode != 0 && selectingMode) {
		if (gest.getGesture() == GRAB_ONE_HAND) {
			std::cout << "Activating selected mode" << '\n';
			selectingMode = false;
		} else if (gest.getGesture() == FIVE_FINGERS_ONE_HAND) {
			std::cout << "New selection" << '\n';
			mode = 0;
		}
	} else if (mode == 3){

		const Leap::GestureList gestures = frame.gestures();
		for (int g = 0; g < gestures.count(); ++g) {
			Leap::Gesture gesture = gestures[g];

			switch (gesture.type()) {
			case Leap::Gesture::TYPE_SWIPE:
				image.setTo(cv::Scalar(255));
        cv::imshow("My image", image);
        cv::waitKey(1000);
				break;
			default:
				break;
			}
		}

		//std::cout << gest.getGesture() << " " << STRONG_GRAB << std::endl;
		if (gest.getGesture() != GRAB_ONE_HAND && controller.frame().fingers().count() > 0) {
			Leap::Vector newPosition, fingerTip;
			Leap::FingerList fingers = controller.frame().fingers();
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

			/*fingerTip = newPosition;*/
			fingerTip = filter.filterMean(positions);
			//fingers = frame.hands()[0].fingers();
			//for (Leap::FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); fl++) {
			//	if ((*fl).type() == 1) {
			//		fingerTip = (*fl).tipPosition();
			//	}
			//}
			//std::cout << fingerTip.x << std::endl;
			//std::cout << fingerTip.y << std::endl;
			if (fingerTip.x != 0 && fingerTip.y != 0) {
				previous.x = actual.x;
				previous.y = actual.y;
				actual.y = -static_cast<int>(fingerTip.y) + rows - 40;
				actual.x = static_cast<int>(fingerTip.x) * 2 + cols / 2;
				line(image, previous, actual, cv::Scalar(0, 0, 0), 5);
			}
		}

			// Get fingers
			// const FingerList fingers = hands.fingers();
			// for (FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); ++fl) {
			//   const Finger finger = *fl;
			//   //std::cout << std::string(4, ' ') <<  fingerNames[finger.type()]
			//          //   << " finger, id: " << finger.id()
			//           //  << ", length: " << finger.length()
			//            // << "mm, width: " << finger.width() << std::endl
			// ;

			//   // Get finger bones
			//   for (int b = 0; b < 4; ++b) {
			//     Bone::Type boneType = static_cast<Bone::Type>(b);
			//     Bone bone = finger.bone(boneType);
			//  //   std::cout << std::string(6, ' ') <<  boneNames[boneType]
			//             //  << " bone, start: " << bone.prevJoint()
			//              // << ", end: " << bone.nextJoint()
			//              // << ", direction: " << bone.direction() << std::endl
			//;
			//   }
			// }
			// Get the most recent frame and report some basic information
			// Frame frame = controller.frame();
			// if (numberOfFrames < 5) {
			//   frames.insert(frames.begin(),frame);
			// } else {
			//   frames.pop_back();
			//frames.insert(frames.begin(), frame);
			// }

			// Vector vec;
			// HandList hands = frame.hands();
			// for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) {
			//   hand = *hl;
			//   //vec = filter.filterMeanHand(frames, hand.id());
			//vec = hand.palmPosition();
			// }

			// if (!initialized) {

			//    actual.y = -static_cast<int>(vec.y)+400;
			//    actual.x = static_cast<int>(vec.x)*2+330;
			// initialized = true;
			// } else {
			// previous.x = actual.x;
			// previous.y = actual.y;
			// actual.y = -static_cast<int>(vec.y) + 400;
			// actual.x = static_cast<int>(vec.x)*2 + 330;
			// }

			// /*std::cout << "X position :" << vec.x << std::endl;
			// std::cout << "Y position :" << vec.y << std::endl;*/
			// //if (vec.y - rowOrigin + 230 < 0 || vec.y - rowOrigin + 230 > 460 || vec.x - colOrigin + 340 < 0 || vec.x - colOrigin + 340 > 680) {
			// //  std::cout << "out of the picture" << std::endl;
			// //} else {
			// //image.at<uchar>(-static_cast<int>(vec.y)*2 + 230, static_cast<int>(vec.x)*2 + 340) = 0;
			// //}
			// //std::cout << previous.x << std::endl;
			// //std::cout << previous.y << std::endl;
			// //std::cout << actual.x << std::endl;
			// //std::cout << actual.y << std::endl;
			// line(image, previous, actual, Scalar(0, 0, 0),5);
			// cv::imshow("My image", image);
			// waitKey(40);

		cv::imshow("My image", image);
		cv::waitKey(40);
	}
}

void DetectionListener::onFocusGained(const Leap::Controller& controller) {
	std::cout << "Focus Gained" << std::endl;
}

void DetectionListener::onFocusLost(const Leap::Controller& controller) {
	std::cout << "Focus Lost" << std::endl;
}

void DetectionListener::onDeviceChange(const Leap::Controller& controller) {
	std::cout << "Device Changed" << std::endl;
	const Leap::DeviceList devices = controller.devices();

	for (int i = 0; i < devices.count(); ++i) {
		std::cout << "id: " << devices[i].toString() << std::endl;
		std::cout << "  isStreaming: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
	}
}

void DetectionListener::onServiceConnect(const Leap::Controller& controller) {
	std::cout << "Service Connected" << std::endl;
}

void DetectionListener::onServiceDisconnect(const Leap::Controller& controller) {
	std::cout << "Service Disconnected" << std::endl;
}
