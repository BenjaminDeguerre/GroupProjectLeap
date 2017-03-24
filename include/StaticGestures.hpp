#ifndef STATIC_GESTURE_HPP
#define STATIC_GESTURE_HPP

#include <iostream>
#include <cstring>

#include "Leap.h"

enum StaticGesture {
 ERROR = -1,

 GRAB_ONE_HAND,

 ONE_FINGER_ONE_HAND,
 TWO_FINGERS_ONE_HAND,
 THREE_FINGERS_ONE_HAND,
 FOUR_FINGERS_ONE_HAND,
 FIVE_FINGERS_ONE_HAND,

 // LEFT_ONE_RIGHT_ONE - left hand one finger, right hand one finger
	LEFT_ZERO_RIGHT_ONE,
	LEFT_ZERO_RIGHT_TWO,
	LEFT_ZERO_RIGHT_THREE,
	LEFT_ZERO_RIGHT_FOUR,
	LEFT_ZERO_RIGHT_FIVE,

	LEFT_ONE_RIGHT_ONE,
	LEFT_ONE_RIGHT_TWO,
	LEFT_ONE_RIGHT_THREE,
	LEFT_ONE_RIGHT_FOUR,
	LEFT_ONE_RIGHT_FIVE,

	LEFT_TWO_RIGHT_ONE,
	LEFT_TWO_RIGHT_TWO,
	LEFT_TWO_RIGHT_THREE,
	LEFT_TWO_RIGHT_FOUR,
	LEFT_TWO_RIGHT_FIVE,

	LEFT_THREE_RIGHT_ONE,
	LEFT_THREE_RIGHT_TWO,
	LEFT_THREE_RIGHT_THREE,
	LEFT_THREE_RIGHT_FOUR,
	LEFT_THREE_RIGHT_FIVE,

	LEFT_FOUR_RIGHT_ONE,
	LEFT_FOUR_RIGHT_TWO,
	LEFT_FOUR_RIGHT_THREE,
	LEFT_FOUR_RIGHT_FOUR,
	LEFT_FOUR_RIGHT_FIVE,
	
	LEFT_FIVE_RIGHT_ONE,
	LEFT_FIVE_RIGHT_TWO,
	LEFT_FIVE_RIGHT_THREE,

	CANCEL, // if both hands are open
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
	int countFingers;

public:
	StaticGestures() : handCount(0), leftHand(false) {}
	StaticGestures(Leap::HandList hands);
	~StaticGestures();

  //return for one and two hands
	StaticGesture getGesture();
};

#endif
