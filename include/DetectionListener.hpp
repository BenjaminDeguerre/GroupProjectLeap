#ifndef DETECTION_LISTENER_HPP
#define DETECTION_LISTENER_HPP

#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <cstring>

#include "Leap.h"
#include "StaticGestures.hpp"
#include "GestValidator.hpp"
#include "ModeHandler.hpp"

class DetectionListener : public Leap::Listener {
private:
	ModeHandler handler;
	GestValidator validator;

	int mode = 0;
	bool selectingMode;

public:
	DetectionListener(): selectingMode(true) {}
	virtual void onInit(const Leap::Controller&);
	virtual void onConnect(const Leap::Controller&);
	virtual void onDisconnect(const Leap::Controller&);
	virtual void onExit(const Leap::Controller&);
	virtual void onFrame(const Leap::Controller&);
	virtual void onFocusGained(const Leap::Controller&);
	virtual void onFocusLost(const Leap::Controller&);
	virtual void onDeviceChange(const Leap::Controller&);
	virtual void onServiceConnect(const Leap::Controller&);
	virtual void onServiceDisconnect(const Leap::Controller&);
};

#endif
