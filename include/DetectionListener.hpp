#ifndef DETECTION_LISTENER_HPP
#define DETECTION_LISTENER_HPP

#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <cstring>

#include <opencv2/core/core.hpp>
//#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Leap.h"
#include "StaticGestures.hpp"
#include "GestValidator.hpp"
#include "ModeHandler.hpp"

class DetectionListener : public Leap::Listener {
private:
	ModeHandler handler;
	GestValidator validator;

	int numberOfPositions = 0, rows = 460, cols = 680, historicSize = 10, rowOrigin, colOrigin, mode = 0;
	std::vector<Leap::Vector> positions;
	Filter filter;
	cv::Mat image = cv::Mat(rows, cols, CV_8UC1, cv::Scalar(255));
	bool initialized = false, selectingMode;
	cv::Point previous = cv::Point(rows - 40, cols / 2), actual = cv::Point(rows - 40, cols / 2);

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
