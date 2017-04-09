#ifndef MODE_HANDLER_HPP
#define MODE_HANDLER_HPP

#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <cstring>

#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Leap.h"
#include "StaticGestures.hpp"
#include "Filter.hpp"
#include "Communicator.hpp"

class ModeHandler {
private:
	int numberOfPositions = 0, rows = 460, cols = 680, historicSize = 10, rowOrigin, colOrigin;
	std::vector<Leap::Vector> positions;
	Filter filter;
	cv::Mat image = cv::Mat(rows, cols, CV_8UC1, cv::Scalar(255));
	bool initialized = false;
	cv::Point previous = cv::Point(rows - 40, cols / 2), actual = cv::Point(rows - 40, cols / 2);

	char letterMode1[10];
	bool letterSelected = false;

  bool stopMode3 = false;

	Communicator communicator;
  char buffer[100];
	float c, d;
  float a, b, g, z1, z2;

	void writeLetter(char *letter);
	void writeLetterA();
	void writeLetterB();
	void writeLetterC();
	void writeLetterD();
	void writeLetterE();
	void writeLetterF();
	void writeLetterG();
	void writeLetterH();
	void writeLetterI();
	void writeLetterJ();
	void writeLetterK();
	void writeLetterL();
	void writeLetterM();
	void writeLetterN();
	void writeLetterO();
	void writeLetterP();
	void writeLetterQ();
	void writeLetterR();
	void writeLetterS();
	void writeLetterT();
	void writeLetterU();
	void writeLetterV();
	void writeLetterW();
	void writeLetterX();
	void writeLetterY();
  void writeLetterZ();
	void writeLetterSpace();

public:
	ModeHandler();
  bool mode1(const StaticGesture gesture);
  bool mode2(const StaticGesture gesture, const Leap::GestureList gestures, const Leap::FingerList fingers);
};

#endif
