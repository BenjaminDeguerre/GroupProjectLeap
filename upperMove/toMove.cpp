void gesture::chooseMode()
{
	int mode;
	bool mode_cout;
	GestControl& gc = GestControl::getInstance();
	gc.setFrameLimit(50);

	current_mode = 0;
	mode = detectGestureOneHand();
	mode_cout = gc.getModeCout();

	if (mode > 0 && mode < 5) {
		current_mode = mode;
		gc.setModeCout(false);
	}

	if (mode_cout == false && current_mode == 0)
	{
		std::cout << "Choose mode 1,2,3 or 4\n";
		gc.setModeCout(true);
	}
}

void gesture::on()
{
	int result;

	if (current_mode == 0) chooseMode();

	switch (current_mode) {
	case 1:
		//mode 1 - select text and print it on the screen
		std::cout << "Mode 1 - switch\n";
		break;

	case 2:
		//mode 2 - writing with gestures
		//detectGestureOneHand();
		//std::cout<<result<< std::endl;
		std::cout << "Mode 2 - switch\n";
		break;

	case 3:
		//mode 3 - drawing by finger
		//result = detectGestureTwoHands();
		//std::cout<<result<< std::endl;
		std::cout << "Mode 3 - switch\n";
		break;

	case 4:
		//mode 4 - moving the robot
		std::cout << "Mode 4 - switch\n";
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
