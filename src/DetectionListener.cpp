#include "DetectionListener.hpp"

void DetectionListener::onInit(const Leap::Controller& controller) {
  std::cout << "Initialized" << std::endl;
}

void DetectionListener::onConnect(const Leap::Controller& controller) {
  std::cout << "Connected" << std::endl;
  controller.enableGesture(Leap::Gesture::TYPE_CIRCLE);
  controller.enableGesture(Leap::Gesture::TYPE_KEY_TAP);
  controller.enableGesture(Leap::Gesture::TYPE_SCREEN_TAP);
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
  validator.update(sGesture);
  sGesture = validator.getCurrentValidGesture();

  if (mode == 0) {
    switch (sGesture) {
      case ONE_FINGER_RIGHT_HAND:
        // mode 1 - select text and print it on the screen
        std::cout << "selecting mode 1" << '\n';
        mode = 1;
        validator.setGesture(ERROR_SG);  // setting to new gesture
        break;
      case TWO_FINGERS_RIGHT_HAND:
        // mode 2 - writing with gestures
        std::cout << "selecting mode 2" << '\n';
        mode = 2;
        validator.setGesture(ERROR_SG);  // setting to new gesture
        break;
      default:
        // do nothing and wait for detection.
        break;
    }
  } else if (mode != 0 && selectingMode) {
    if (sGesture == GRAB_ONE_HAND) {
      std::cout << "Activating selected mode" << '\n';
      selectingMode = false;
      validator.setGesture(ERROR_SG);
    } else if (sGesture == FIVE_FINGERS_RIGHT_HAND) {
      std::cout << "New selection" << '\n';
      mode = 0;
      validator.setGesture(ERROR_SG);
    }
  } else {
    switch (mode) {
      case 1:
        selectingMode = !handler.mode1(sGesture);
        break;
      case 2:
        selectingMode =
            !handler.mode2(sGesture, frame.gestures(), frame.fingers());
        break;
      default:
        break;
    }
    if (selectingMode) {
      mode = 0;
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
    std::cout << "  isStreaming: "
              << (devices[i].isStreaming() ? "true" : "false") << std::endl;
  }
}

void DetectionListener::onServiceConnect(const Leap::Controller& controller) {
  std::cout << "Service Connected" << std::endl;
}

void DetectionListener::onServiceDisconnect(
    const Leap::Controller& controller) {
  std::cout << "Service Disconnected" << std::endl;
}
