#ifndef GESTURE_HPP
#define GESTURE_HPP

#include <iostream>
#include <cstring>
#include "Leap.h"
#include "GestControl.hpp"

#define ERROR -1
#define MODE_1 1
#define MODE_2 2
#define MODE_3 3
#define MODE_4 4

#define ONE_FINGER 5
#define TWO_FINGERS 6
#define THREE_FINGERS 7
#define FOUR_FINGERS 8
#define FIVE_FINGERS 9
#define SIX_FINGERS 10
#define SEVEN_FINGERS 11
#define EIGHT_FINGERS 12
#define NINE_FINGERS 13
#define TEN_FINGERS 14

#define WEAK_GRAB 15
#define STRONG_GRAB 16
#define GRAB_ONE_HAND 17

class Gesture{
public:
	Gesture() : hand_count(0), strength(0), leftHand(0) {}
	Gesture(Leap::HandList hand);
	~Gesture();

	void on();
	void drawfingers();

	//Methods to recognize gestures
	// -> define int
	int detectGestureOneHand();
	int detectGestureTwoHands();
	int getGesture();

private:
	Leap::HandList hands;
	Leap::FingerList ext_fingers1;
	Leap::FingerList ext_fingers2;
	Leap::Hand hand;
	int hand_count;
	float* strength;
	bool leftHand;
	int* fing;
	int count;
};

#endif
