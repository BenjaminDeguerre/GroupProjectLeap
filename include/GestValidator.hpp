#ifndef GESTVALIDATOR_HPP
#define GESTVALIDATOR_HPP

#include <iostream>
#include <cstring>

#include "Leap.h"
#include "StaticGestures.hpp"

class GestValidator {
private:
	int count;
	int frameLimit;
	StaticGesture currentGesture;

public:
	GestValidator() :currentGesture(ERROR_SG), count(0), frameLimit(10) {};
	~GestValidator() {};

	void setFrameLimit(int limit);
	int getFrameLimit();
	void setGesture(StaticGesture gesture);
  void update(StaticGesture gesture);
  StaticGesture getCurrentValidGesture();
};
#endif
