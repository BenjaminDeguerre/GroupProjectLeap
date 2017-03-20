#include "Gesture.hpp"

Gesture::Gesture(Leap::HandList hands) {
	this->hands = hands;
	handCount = hands.count();
	if (handCount == 1) {
		leftHand = hands[0].isLeft();
		hand = hands[0];
	}
}

Gesture::~Gesture() {}

void Gesture::chooseMode() 
{
	mode = detectGestureOneHand();
	switch (mode) {
	case 1:
		return mode1();
		break;

	case 2:
		return mode2();
		break;

	case 3:
		return mode3();
		break;

	case 4:
		return mode4();
		break;

	default:
		return ERROR;
		break;
	}
}

int Gesture::getGesture() {
	int result;

	switch (handCount) {
	case 1:
		return detectGestureOneHand();
		break;
	case 2:
		//return detectGestureTwoHands();
		result = detectGestureTwoHands();
		checkLetter(result);
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

	int result = 0;
	int num = ext_fingers1.count();

	GestControl& gestcontrol = GestControl::getInstance();
	gestcontrol.setFrameLimit(500);
	result = gestcontrol.setGesture(num);

	if (result) {
		if (num == 1) std::cout << "Mode 1\n";
		if (num == 2) std::cout << "Mode 2\n";
		if (num == 3) std::cout << "Mode 3\n";
		if (num == 4) std::cout << "Mode 4\n";
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

	GestControl& gestcontrol = GestControl::getInstance();
	gestcontrol.setFrameLimit(100);
	
	int result, num;
	int fingersNumber, extendedFingersHand1, extendedFingersHand2;
	float grabAngle1 = hands[0].grabAngle(), grabAngle2 = hands[1].grabAngle();

	//if (hands[0].isLeft() == false) 
	//{
	//	Leap::Hand term = hands[0];
	//	hands[0] = hands[1];
	//	hands[1] = term;
	//}

	strength[0] = hands[0].grabStrength();
	strength[1] = hands[1].grabStrength();

	extendedFingersHand1 = hands[0].fingers().extended().count();
	extendedFingersHand2 = hands[1].fingers().extended().count();

	fingersNumber = extendedFingersHand1 + extendedFingersHand2;
	
	//num = 5*extendedFingersHand1 + extendedFingersHand2;

	result = gestcontrol.setGesture(fingersNumber);

	switch (result) {
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

void Gesture::checkLetter(int num) 
{

	if (num == 27) std::cout << ".";
	if (num == 28) std::cout << " ";
	if (num > 0 && num < 27)
	{
		char k = num + 96;
		//std::cout << k << std::endl;
		std::cout << k;
	}
	
}
