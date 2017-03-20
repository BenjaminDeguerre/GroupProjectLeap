#include "Gesture.hpp"

Gesture::Gesture(Leap::HandList hands) {
	this->hands = hands;
	handCount = hands.count();
	if (handCount == 1) {
		leftHand = hands[0].isLeft();
	}
}

Gesture::~Gesture() {
}

int Gesture::getGesture() {
	switch (handCount) {
	case 1:
		return detectGestureOneHand();
		break;
	case 2:
		return detectGestureTwoHands();
		break;
	default:
		return ERROR;
		break;
	}
}

int Gesture::detectGestureOneHand() {

	if (hands.count() != 1) {
		return ERROR;
	}

	int extendedFingersHand =  hands[0].fingers().extended().count();

	switch (extendedFingersHand) {
		case 0:
			return GRAB_ONE_HAND;
			break;
		case 1:
			return ONE_FINGER_ONE_HAND;
			break;
		case 2:
			return TWO_FINGERS_ONE_HAND;
			break;
		case 3:
			return THREE_FINGERS_ONE_HAND;
			break;
		case 4:
			return FOUR_FINGERS_ONE_HAND;
			break;
		case 5:
			return FIVE_FINGERS_ONE_HAND;
			break;
		default:
			return ERROR;
			break;
		}
}

int Gesture::detectGestureTwoHands() {

	if (hands.count() >= 3) {
		return ERROR;
	}

	int fingersNumber, extendedFingersHand1, extendedFingersHand2;
	float grabAngle1 = hands[0].grabAngle(), grabAngle2 = hands[1].grabAngle();

	strength[0] = hands[0].grabStrength();
	strength[1] = hands[1].grabStrength();

	extendedFingersHand1 = hands[0].fingers().extended().count();
	extendedFingersHand2 = hands[1].fingers().extended().count();

	fingersNumber = extendedFingersHand1 + extendedFingersHand2;

	switch (fingersNumber) {
		case 1:
			return ONE_FINGER;
			break;
		case 2:
			return TWO_FINGERS;
			break;
		case 3:
			return THREE_FINGERS;
			break;
		case 4:
			return FOUR_FINGERS;
			break;
		case 5:
			return FIVE_FINGERS;
			break;
		case 6:
			return SIX_FINGERS;
			break;
		case 7:
			return SEVEN_FINGERS;
			break;
		case 8:
			return EIGHT_FINGERS;
			break;
		case 9:
			return NINE_FINGERS;
			break;
		case 10:
			return TEN_FINGERS;
			break;
		default://do nothing to not return an error before the other checks.
			break;
	}

	if (strength[0] < 0.5 && strength[1] < 0.5) return WEAK_GRAB;
	if (grabAngle1 > 1.5 && grabAngle2 > 1.5) return STRONG_GRAB;

	return ERROR;
}
