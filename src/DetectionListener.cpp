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
	StaticGestures sGestures(frame.hands());
	StaticGesture sGesture = sGestures.getGesture();
	if (validator.isValid(sGesture) ){
		if (mode == 0) {
			switch (sGesture) {
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
				break;
			}
			validator.setGesture(ERROR); //setting to new gesture
		} else if (mode != 0 && selectingMode) {
			if (sGesture == GRAB_ONE_HAND) {
				std::cout << "Activating selected mode" << '\n';
				selectingMode = false;
			} else if (sGesture == FIVE_FINGERS_ONE_HAND) {
				std::cout << "New selection" << '\n';
				mode = 0;
			}
			validator.setGesture(ERROR);
		} else {
			switch (mode) {
				case 1:
				selectingMode = !handler.mode1();
				break;
				case 2:
				selectingMode = !handler.mode2();
				break;
				case 3:
				selectingMode = !handler.mode3(sGesture, frame.gestures(), frame.fingers());
				break;
				case 4:
				selectingMode = !handler.mode4();
				break;
				default:
				break;
			}
			if (selectingMode) {
				mode = 0;
			}
		}
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
