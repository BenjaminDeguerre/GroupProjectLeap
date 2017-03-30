#ifndef MODE_HANDLER_HPP
#define MODE_HANDLER_HPP

#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <cstring>

#include <opencv2/core/core.hpp>
//#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Leap.h"
#include "StaticGestures.hpp"
#include "Filter.hpp"

class ModeHandler {
private:
	int numberOfPositions = 0, rows = 460, cols = 680, historicSize = 10, rowOrigin, colOrigin, mode = 0;
	std::vector<Leap::Vector> positions;
	Filter filter;
	cv::Mat image = cv::Mat(rows, cols, CV_8UC1, cv::Scalar(255));
	bool initialized = false, selectingMode;
	cv::Point previous = cv::Point(rows - 40, cols / 2), actual = cv::Point(rows - 40, cols / 2);

	char letterMode1;
	bool letterSelected = false;
	
public:
  bool mode1(const StaticGesture gesture);
  bool mode2();
  bool mode3(const StaticGesture gesture, const Leap::GestureList gestures, const Leap::FingerList fingers);
  bool mode4();
};

#endif
