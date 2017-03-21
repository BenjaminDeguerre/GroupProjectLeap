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
