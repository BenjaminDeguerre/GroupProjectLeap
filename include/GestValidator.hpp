#ifndef GESTVALIDATOR_HPP
#define GESTVALIDATOR_HPP

#include <cstring>
#include <iostream>

#include "Leap.h"
#include "StaticGestures.hpp"

/**
 * \class GestValidator
 * \brief Helper class to return wether a gest is valid or not.
 **/
class GestValidator {
 private:
  int count;
  int frameLimit;
  StaticGesture currentGesture;

 public:
  GestValidator() : currentGesture(ERROR_SG), count(0), frameLimit(10){};
  ~GestValidator(){};

  /**
   * \fn GestValidator::setFrameLimit(int limit)
   * \brief Setter for the frame limit parameter. A gesture needs to be present
   *for at least "limit" frames to be considered as valid.Œ \param limit[in] The
   *new limit to be used.
   **/
  void setFrameLimit(int limit);

  /**
   * \fn GestValidator::getFrameLimit()
   * \brief Get the current frame limit.
   **/
  int getFrameLimit();

  /**
   * \fn GestValidator::setGesture(StaticGesture gesture)
   * \brief Setter for the gesture parameter.
   * \param gesture[in] The new gesture.
   **/
  void setGesture(StaticGesture gesture);

  /**
   * \fn GestValidator::update(StaticGesture gesture)
   * \brief Update the counter for the gesture. If the gesture is the same,
   * update the count by one, else set it to one and reset the gesture
   * to the new gesture.
   * \param gesture[in] The new gesture.
   **/
  void update(StaticGesture gesture);

  /**
   * \fn StaticGesture GestValidator::getCurrentValidGesture()
   * \brief Return the gesture if detected a suffisant number of times.
   **/
  StaticGesture getCurrentValidGesture();
};
#endif
