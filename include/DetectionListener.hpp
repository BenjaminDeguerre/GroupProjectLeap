#ifndef DETECTION_LISTENER_HPP
#define DETECTION_LISTENER_HPP

#define _CRT_SECURE_NO_DEPRECATE

#include <cstring>
#include <iostream>

#include "GestValidator.hpp"
#include "Leap.h"
#include "ModeHandler.hpp"
#include "StaticGestures.hpp"

/**
 * \class DetectionListener
 * \brief Handles the differents event that can occur during a session.
 **/
class DetectionListener : public Leap::Listener {
 private:
  ModeHandler handler;
  GestValidator validator;

  int mode = 0;
  bool selectingMode;

 public:
  DetectionListener() : selectingMode(true) {}

  /**
   * \fn void DetectionListener::onInit(const Leap::Controller& controller)
   * \brief Called on init, does nothing.
   **/
  virtual void onInit(const Leap::Controller&);

  /**
   * \fn void DetectionListener::onConnect(const Leap::Controller& controller)
   * \brief Enables the four dynamic gestures used to control the robot.
   **/
  virtual void onConnect(const Leap::Controller&);

  /**
   * \fn void DetectionListener::onDisconnect(const Leap::Controller&)
   * \brief Called when the Listener disconnects, does nothing.
   **/
  virtual void onDisconnect(const Leap::Controller&);

  /**
   * \fn void DetectionListener::onExit(const Leap::Controller& controller)
   * \brief Called on exit, does nothing.
   **/
  virtual void onExit(const Leap::Controller&);

  /**
   * \fn void DetectionListener::onFrame(const Leap::Controller& controller)
   * \brief Wait for a new frame and either switch between modes or send command
   *to the robot depending on the mode. If no mode is selected we wait for
   *either ONE_FINGER_RIGHT_HAND or TWO_FINGERS_RIGHT_HAND to select mode one or
   *two. If a mode is selected but not validated, we wait for GRAB_ONE_HAND or
   *FIVE_FINGERS_RIGHT_HAND to validate or go back to selection. Else, we
   *call the correct function.
   **/
  virtual void onFrame(const Leap::Controller&);

  /**
   * \fn void DetectionListener::onFocusGained(const Leap::Controller&
   *controller)
   * \brief Called when the focus is gained, does nothing.
   **/
  virtual void onFocusGained(const Leap::Controller&);

  /**
   * \fn void DetectionListener::onFocusLost(const Leap::Controller& controller)
   * \brief Called when the focus is lost, does nothing.
   **/
  virtual void onFocusLost(const Leap::Controller&);

  /**
   * \fn void DetectionListener::onDeviceChange(const Leap::Controller&
   *controller)
   * \brief Just print stuff if the device is changed/lost and found
   *again.
   **/
  virtual void onDeviceChange(const Leap::Controller&);

  /**
   * \fn void DetectionListener::onServiceConnect(const Leap::Controller&
   *controller)
   * \brief Called when the service connects, does nothing.
   **/
  virtual void onServiceConnect(const Leap::Controller&);

  /**
   * \fn void DetectionListener::onServiceDisconnect(const Leap::Controller&
   *controller)
   * \brief Called when the service disconnects, does nothing.
   **/
  virtual void onServiceDisconnect(const Leap::Controller&);
};

#endif
