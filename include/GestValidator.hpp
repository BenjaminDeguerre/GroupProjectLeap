#ifndef GESTVALIDATOR_HPP
#define GESTVALIDATOR_HPP

#include <iostream>
#include <cstring>

#include "Leap.h"
#include "Gesture.hpp"

class GestControl {
private:
	struct Handler {
		GestControl *instance;
		Handler() :instance(0) {};
		~Handler() { if (instance) delete instance; }
	};
	static Handler handler;
	int gestureId;
	int count;
	int frameLimit;
	bool mode_cout;

	GestControl() :gestureId(-1), count(0), frameLimit(60) {};
	~GestControl() {};
	//preventing using default copy constructor
	GestControl& operator=(const GestControl& gc) {};

public:
	static GestControl& getInstance();
	static void freeInstance();

	void setFrameLimit(int limit) { frameLimit = limit; }
	int getFrameLimit() { return frameLimit; }

	bool setGesture(int id);
	void setModeCout(bool mode) { mode_cout = mode; }
	bool getModeCout() { return mode_cout; }
	//void validateGesture(int id);
};
#endif
