#ifndef GESTURE_HPP
#define GESTURE_HPP

#include <iostream>
#include <cstring>
#include "Leap.h"
#include "GestControl.hpp"

enum GesturesAvailable {
 ERROR = -1,

 ONE_FINGER,
 TWO_FINGERS,
 THREE_FINGERS,
 FOUR_FINGERS,
 FIVE_FINGERS,
 SIX_FINGERS,
 SEVEN_FINGERS,
 EIGHT_FINGERS,
 NINE_FINGERS,
 TEN_FINGERS,

 WEAK_GRAB,
 STRONG_GRAB,
 GRAB_ONE_HAND,

 ONE_FINGER_ONE_HAND,
 TWO_FINGERS_ONE_HAND,
 THREE_FINGERS_ONE_HAND,
 FOUR_FINGERS_ONE_HAND,
 FIVE_FINGERS_ONE_HAND,
};


class Gesture{
private:
  int detectGestureOneHand();
  int detectGestureTwoHands();

  Leap::HandList hands;
  int handCount;
  float strength[2];
  bool leftHand;

public:
	Gesture() : handCount(0), leftHand(false) {}
	Gesture(Leap::HandList hand);
	~Gesture();

	//Methods to recognize gestures

  //return for one and two hands
	int getGesture();
};

#endif
