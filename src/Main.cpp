	/******************************************************************************\
* Copyright (C) 2012-2014 Leap Motion, Inc. All rights reserved.               *
* Leap Motion proprietary and confidential. Not for distribution.              *
* Use subject to the terms of the Leap Motion SDK Agreement available at       *
* https://developer.leapmotion.com/sdk_agreement, or another agreement         *
* between Leap Motion and you, your company or other organization.             *
\******************************************************************************/

#include <iostream>
#include <cstring>
#include "Leap.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Filter.hpp"

using namespace cv;

using namespace Leap;

class SampleListener : public Listener {
  public:
    virtual void onInit(const Controller&);
    virtual void onConnect(const Controller&);
    virtual void onDisconnect(const Controller&);
    virtual void onExit(const Controller&);
    virtual void onFrame(const Controller&);
    virtual void onFocusGained(const Controller&);
    virtual void onFocusLost(const Controller&);
    virtual void onDeviceChange(const Controller&);
    virtual void onServiceConnect(const Controller&);
    virtual void onServiceDisconnect(const Controller&);

  private:
    int numberOfFrames = 0;
    std::vector<Frame> frames;
    Filter filter;
    Mat image = Mat(460, 680, CV_8UC1, Scalar(255));
    Hand hand;
    int rowOrigin, colOrigin;
    bool previousHand = false;
};

const std::string fingerNames[] = {"Thumb", "Index", "Middle", "Ring", "Pinky"};
const std::string boneNames[] = {"Metacarpal", "Proximal", "Middle", "Distal"};
const std::string stateNames[] = {"STATE_INVALID", "STATE_START", "STATE_UPDATE", "STATE_END"};

void SampleListener::onInit(const Controller& controller) {
  std::cout << "Initialized" << std::endl;
}

void SampleListener::onConnect(const Controller& controller) {
  std::cout << "Connected" << std::endl;
  controller.enableGesture(Gesture::TYPE_CIRCLE);
  controller.enableGesture(Gesture::TYPE_KEY_TAP);
  controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
  controller.enableGesture(Gesture::TYPE_SWIPE);
}

void SampleListener::onDisconnect(const Controller& controller) {
  // Note: not dispatched when running in a debugger.
  std::cout << "Disconnected" << std::endl;
}

void SampleListener::onExit(const Controller& controller) {
  std::cout << "Exited" << std::endl;
}

void SampleListener::onFrame(const Controller& controller) {
  // Get the most recent frame and report some basic information
  Frame frame = controller.frame();
  if (numberOfFrames < 10) {
    frames.insert(frames.begin(),frame);
  } else {
    frames.pop_back();
	frames.insert(frames.begin(), frame);
  }

  Vector vec;
  HandList hands = frame.hands();
  for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) {
    hand = *hl;
    vec = filter.filterMeanHand(frames, hand.id());
  }

  if (!previousHand) {
     rowOrigin = vec.y;
     colOrigin = vec.x;
     previousHand = true;
  }
  if (vec.y - rowOrigin + 230 < 0 || vec.y - rowOrigin + 230 > 460 || vec.x - colOrigin + 340 < 0 || vec.x - colOrigin + 340 > 680) {
    std::cout << "out of the picture" << std::endl;
  } else {
    image.at<uchar>(vec.y - rowOrigin + 230, vec.x - colOrigin + 680) = 0;
  }

  cv::imwrite("My image", image);
  }

  // Get tools
  //const ToolList tools = frame.tools();
  //for (ToolList::const_iterator tl = tools.begin(); tl != tools.end(); ++tl) {
  //  const Tool tool = *tl;
  //}

  //// Get gestures
  //const GestureList gestures = frame.gestures();
  //for (int g = 0; g < gestures.count(); ++g) {
  //  Gesture gesture = gestures[g];

  //  switch (gesture.type()) {
  //    case Gesture::TYPE_CIRCLE:
  //    {
  //      CircleGesture circle = gesture;
  //      std::string clockwiseness;

  //      if (circle.pointable().direction().angleTo(circle.normal()) <= PI/2) {
  //        clockwiseness = "clockwise";
  //      } else {
  //        clockwiseness = "counterclockwise";
  //      }

  //      // Calculate angle swept since last frame
  //      float sweptAngle = 0;
  //      if (circle.state() != Gesture::STATE_START) {
  //        CircleGesture previousUpdate = CircleGesture(controller.frame(1).gesture(circle.id()));
  //        sweptAngle = (circle.progress() - previousUpdate.progress()) * 2 * PI;
  //      }
  //      break;
  //    }
  //    case Gesture::TYPE_SWIPE:
  //    {
  //      SwipeGesture swipe = gesture;
  //      break;
  //    }
  //    case Gesture::TYPE_KEY_TAP:
  //    {
  //      KeyTapGesture tap = gesture;
  //      break;
  //    }
  //    case Gesture::TYPE_SCREEN_TAP:
  //    {
  //      ScreenTapGesture screentap = gesture;
  //      break;
  //    }
  //    default:
  //      break;
  //  }
  //  }

  //if (!frame.hands().isEmpty() || !gestures.isEmpty()) {
  //  std::cout << std::endl;
  //}

//}

void SampleListener::onFocusGained(const Controller& controller) {
}

void SampleListener::onFocusLost(const Controller& controller) {
}

void SampleListener::onDeviceChange(const Controller& controller) {
  const DeviceList devices = controller.devices();

  for (int i = 0; i < devices.count(); ++i) {
  }
}

void SampleListener::onServiceConnect(const Controller& controller) {
}

void SampleListener::onServiceDisconnect(const Controller& controller) {
}

int main(int argc, char** argv) {
  // Create a sample listener and controller
  SampleListener listener;
  Controller controller;

  // Have the sample listener receive events from the controller
  controller.addListener(listener);

  if (argc > 1 && strcmp(argv[1], "--bg") == 0)
    controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);

  // Keep this process running until Enter is pressed
  std::cout << "Press Enter to quit..." << std::endl;
  std::cin.get();

  // Remove the sample listener when done
  controller.removeListener(listener);

  return 0;
}
