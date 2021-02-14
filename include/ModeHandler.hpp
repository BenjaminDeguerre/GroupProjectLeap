#ifndef MODE_HANDLER_HPP
#define MODE_HANDLER_HPP

#define _CRT_SECURE_NO_DEPRECATE

#include <cstring>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

#include "Communicator.hpp"
#include "Filter.hpp"
#include "Leap.h"
#include "StaticGestures.hpp"

/**
 * \class ModeHandler
 * \brief Contains all the functions to send the correct command to the robot
 *depending on the mode selected.
 **/
class ModeHandler {
 private:
  int numberOfPositions = 0, rows = 460, cols = 680, historicSize = 10,
      rowOrigin, colOrigin;
  std::vector<Leap::Vector> positions;
  Filter filter;
  cv::Mat image = cv::Mat(rows, cols, CV_8UC1, cv::Scalar(255));
  bool initialized = false;
  cv::Point previous = cv::Point(rows - 40, cols / 2),
            actual = cv::Point(rows - 40, cols / 2);

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
  void writeLetterDot();

 public:
  ModeHandler();

  /**
   * \fn bool ModeHandler::mode1(const StaticGesture gesture)
   * \brief Handle the first mode. Basically, either select a letter or validate
   *a selected letter.
   * \param gesture[in] The new gesture found.
   **/
  bool mode1(const StaticGesture gesture);

  /**
   * \fn bool ModeHandler::mode2(const StaticGesture gesture, const
   *Leap::GestureList gestures, const Leap::FingerList fingers) 
   * \brief Handle the second mode. Allow to directly control the robot by hand. 
   * \param gesture[in] The new gesture found.
   * \param gestures[in] A vector of gestures, used to look for the gesture swipe. 
   * \param fingers[in] A list of finger on screen, the finger of type 1 is used to set the current position.
   **/
  bool mode2(const StaticGesture gesture, const Leap::GestureList gestures,
             const Leap::FingerList fingers);
};

#endif
