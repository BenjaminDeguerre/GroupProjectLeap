#ifndef GestControl_h
#define GestControl_h

#include <iostream>
#include <cstring>

#include "Leap.h"
#include "Gesture.hpp"

class GestControl {
public:
	static GestControl& getInstance();
	static void freeInstance();

	void setFrameLimit(int limit) { frameLimit = limit; }
	int getFrameLimit() { return frameLimit; }

	bool setGesture(int id);
	//void validateGesture(int id);

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

	GestControl() :gestureId(-1), count(0), frameLimit(60) {};
	~GestControl() {};
	//preventing using default copy constructor
	GestControl& operator=(const GestControl& gc) {};
};
#endif