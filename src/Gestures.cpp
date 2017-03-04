#include "Gesture.hpp"

Gesture::Gesture(Leap::HandList hands) {
	this->hands = hands;
	hand_count = hands.count();
	strength = new float[hand_count];
	fing = new int[5 * hand_count];
	ext_fingers1 = hands[0].fingers().extended();
	if (hand_count == 1) {
		leftHand = hands[0].isLeft();
		hand = hands[0];
	}
		
		
	/*for (int i = 0; i < 5 * hand_count; i++)
		fing[i] = 0;*/
}

Gesture::~Gesture() {
	delete strength;
	delete fing;
}

int Gesture::getGesture() {
	switch (hand_count) {
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

void Gesture::on()
{
	int result;

	switch (hand_count) {
	case 0:
		//do nothing and wait
		//std::cout << ".";
		break;

	case 1:
		drawfingers();
		detectGestureOneHand();
		break;

	case 2:
		result = detectGestureTwoHands();
		std::cout<<result<< std::endl;
		break;

	default:
		break;
	}
}

void Gesture::drawfingers()
{
	// Get fingers
	for (Leap::FingerList::const_iterator fl = ext_fingers1.begin(); fl != ext_fingers1.end(); ++fl) {
		const Leap::Finger finger = *fl;
		//std::cout << finger.type();
		fing[finger.type()] = 1;
	}
}

int Gesture::detectGestureOneHand() {

	//int result = 0;
	//int num = ext_fingers1.count();

	//GestControl& gestcontrol = GestControl::getInstance();
	//gestcontrol.setFrameLimit(50);
	//result = gestcontrol.setGesture(num);

	//if (result) {
	//	if (num == 1) std::cout << "Mode 1\n";
	//	if (num == 2) std::cout << "Mode 2\n";
	//	if (num == 3) std::cout << "Mode 3\n";
	//	if (num == 4) std::cout << "Mode 4\n";
	//}

	int extendedFingersHand;
	float grabAngle = hand.grabAngle();

	extendedFingersHand = hand.fingers().extended().count();
	
	if (grabAngle > 2.8) return GRAB_ONE_HAND;
	return ERROR;
}

int Gesture::detectGestureTwoHands() {

	int result, extendedFingersHand1, extendedFingersHand2;
	float grabAngle1 = hands[0].grabAngle(), grabAngle2 = hands[1].grabAngle();

	std::cout << grabAngle1 << std::endl;
	strength[0] = hands[0].grabStrength();
	strength[1] = hands[1].grabStrength();
	extendedFingersHand1 = hands[0].fingers().extended().count();
	extendedFingersHand2 = hands[1].fingers().extended().count();

	result = extendedFingersHand1 + extendedFingersHand2;
	
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
	default:
		break;
	}

	if (strength[0] < 0.5 && strength[1] < 0.5) return WEAK_GRAB;
	if (grabAngle1 > 1.5 && grabAngle2 > 1.5) return STRONG_GRAB;
	return ERROR;
}
