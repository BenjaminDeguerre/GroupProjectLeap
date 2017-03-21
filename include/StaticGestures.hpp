#ifndef STATIC_GESTURE_HPP
#define STATIC_GESTURE_HPP

#include <iostream>
#include <cstring>

#include "Leap.h"

enum StaticGesture {
 ERROR = -1,
 ONE_FINGER = 1,

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


class StaticGestures {
private:

  StaticGesture detectGestureOneHand();
	StaticGesture detectGestureTwoHands();

	Leap::HandList hands;
	int handCount;
	Leap::FingerList ext_fingers1;
	Leap::FingerList ext_fingers2;
	Leap::Hand hand;
	float strength[2];
	bool leftHand;
	int count;

public:
	StaticGestures() : handCount(0), leftHand(false) {}
	StaticGestures(Leap::HandList hands);
	~StaticGestures();

  //return for one and two hands
	StaticGesture getGesture();
};

#endif
