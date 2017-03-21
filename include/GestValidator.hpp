#ifndef GESTVALIDATOR_HPP
#define GESTVALIDATOR_HPP

#include <iostream>
#include <cstring>

#include "Leap.h"
#include "StaticGesture.hpp"

class GestVlidator {
private:
	// struct Handler {
	// 	GestControl *instance;
	// 	Handler() :instance(0) {};
	// 	~Handler() { if (instance) delete instance; }
	// };
	// static Handler handler;
	int currentGesture;
	int count;
	int frameLimit;

	StaticGesture currentGesture;
	//bool mode_cout;

	//preventing using default copy constructor
	GestControl& operator=(const GestControl& gc) {};

public:
	// static GestControl& getInstance();
	// static void freeInstance();

	GestControl() :currentGesture(-1), count(0), frameLimit(10) {};
	~GestControl() {};

	void setFrameLimit(int limit);
	int getFrameLimit();
	void setGesture(StaticGesture gesture);
	bool isValid(StaticGesture gesture)
	// void setModeCout(bool mode) { mode_cout = mode; }
	// bool getModeCout() { return mode_cout; }
	//void validateGesture(int id);
};
#endif
