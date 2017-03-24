#include "StaticGestures.hpp"

StaticGestures::StaticGestures(Leap::HandList hands) {
	this->hands = hands;
	handCount = hands.count();
	if (handCount == 1) {
		leftHand = hands[0].isLeft();
		hand = hands[0];
	}
}

StaticGestures::~StaticGestures() {}

StaticGesture StaticGestures::getGesture() {
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

StaticGesture StaticGestures::detectGestureOneHand() {

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

StaticGesture StaticGestures::detectGestureTwoHands() {

	if (hands.count() >= 3) return ERROR;

	int result, extendedFingersHand1, extendedFingersHand2;
	
	if (hands[0].isLeft() == false)
	{
		Leap::Hand term = hands[0];
		hands[0] = hands[1];
		hands[1] = term;
	}

	extendedFingersHand1 = hands[0].fingers().extended().count();
	extendedFingersHand2 = hands[1].fingers().extended().count();

	countFingers = 5*extendedFingersHand1 + extendedFingersHand2;
	switch (result) {
	case 1:
		return LEFT_ZERO_RIGHT_ONE;
		break;
	case 2:
		return LEFT_ZERO_RIGHT_TWO;
		break;
	case 3:
		return LEFT_ZERO_RIGHT_THREE;
		break;
	case 4:
		return LEFT_ZERO_RIGHT_FOUR;
		break;
	case 5:
		return LEFT_ZERO_RIGHT_FIVE;
		break;
	case 6:
		return LEFT_ONE_RIGHT_ONE;
		break;
	case 7:
		return LEFT_ONE_RIGHT_TWO;
		break;
	case 8:
		return LEFT_ONE_RIGHT_THREE;
		break;
	case 9:
		return LEFT_ONE_RIGHT_FOUR;
		break;
	case 10:
		return LEFT_ONE_RIGHT_FIVE;
		break;
	case 11:
		return LEFT_TWO_RIGHT_ONE;
		break;
	case 12:
		return LEFT_TWO_RIGHT_TWO;
		break;
	case 13:
		return LEFT_TWO_RIGHT_THREE;
		break;
	case 14:
		return LEFT_TWO_RIGHT_FOUR;
		break;
	case 15:
		return LEFT_TWO_RIGHT_FIVE;
		break;
	case 16:
		return LEFT_THREE_RIGHT_ONE;
		break;
	case 17:
		return LEFT_THREE_RIGHT_TWO;
		break;
	case 18:
		return LEFT_THREE_RIGHT_THREE;
		break;
	case 19:
		return LEFT_THREE_RIGHT_FOUR;
		break;
	case 20:
		return LEFT_THREE_RIGHT_FIVE;
		break;
	case 21:
		return LEFT_FOUR_RIGHT_ONE;
		break;
	case 22:
		return LEFT_FOUR_RIGHT_TWO;
		break;
	case 23:
		return LEFT_FOUR_RIGHT_THREE;
		break;
	case 24:
		return LEFT_FOUR_RIGHT_FOUR;
		break;
	case 25:
		return LEFT_FOUR_RIGHT_FIVE;
		break;
	case 26:
		return LEFT_FIVE_RIGHT_ONE;
		break;
	case 27:
		return LEFT_FIVE_RIGHT_TWO;
		break;
	case 28:
		return LEFT_FIVE_RIGHT_THREE;
		break;
	case 30:
		return CANCEL;
		break;
	default:
		return ERROR;
		break;
	}
}