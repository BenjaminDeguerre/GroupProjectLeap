#include "StaticGestures.hpp"

StaticGestures::StaticGestures(Leap::HandList hands) {
  this->hands = hands;
  handCount = hands.count();
}

StaticGestures::~StaticGestures() {}

StaticGesture StaticGestures::getGesture() {
  switch (handCount) {
    case 1:
      return detectGestureOneHand();
      break;
    case 2:
      return detectGestureTwoHands();
      break;
    default:
      return ERROR_SG;
      break;
  }
}

StaticGesture StaticGestures::detectGestureOneHand() {
  if (hands.count() != 1) {
    // Should never go through here
    return ERROR_SG;
  }

  bool isLeft = hands[0].isLeft();
  int extendedFingersHand = hands[0].fingers().extended().count();

  if (isLeft) {
    switch (extendedFingersHand) {
      case 0:
        return GRAB_ONE_HAND;
        break;
      case 1:
        return ONE_FINGER_LEFT_HAND;
        break;
      case 2:
        return TWO_FINGERS_LEFT_HAND;
        break;
      case 3:
        return THREE_FINGERS_LEFT_HAND;
        break;
      case 4:
        return FOUR_FINGERS_LEFT_HAND;
        break;
      case 5:
        return FIVE_FINGERS_LEFT_HAND;
        break;
      default:
        return ERROR_SG;
        break;
    }
  } else {
    switch (extendedFingersHand) {
      case 0:
        return GRAB_ONE_HAND;
        break;
      case 1:
        return ONE_FINGER_RIGHT_HAND;
        break;
      case 2:
        return TWO_FINGERS_RIGHT_HAND;
        break;
      case 3:
        return THREE_FINGERS_RIGHT_HAND;
        break;
      case 4:
        return FOUR_FINGERS_RIGHT_HAND;
        break;
      case 5:
        return FIVE_FINGERS_RIGHT_HAND;
        break;
      default:
        return ERROR_SG;
        break;
    }
  }
}

StaticGesture StaticGestures::detectGestureTwoHands() {
  if (hands.count() >= 3 ||
      (hands.count() == 2 && hands[0].isLeft() && hands[1].isLeft()))
    return ERROR_SG;

  int extendedFingersHand1, extendedFingersHand2, countFingers;

  // putting left hand to the zero position
  // the previous method wasn't working
  if (hands[0].isLeft()) {
    extendedFingersHand1 = hands[0].fingers().extended().count();
    extendedFingersHand2 = hands[1].fingers().extended().count();
  } else {
    extendedFingersHand2 = hands[0].fingers().extended().count();
    extendedFingersHand1 = hands[1].fingers().extended().count();
  }

  // avoiding possible mixing in detections
  if (extendedFingersHand2 == 0) {
    switch (extendedFingersHand1) {
      case 0:
        return LEFT_ZERO_RIGHT_ZERO;
        break;
      case 1:
        return LEFT_ONE_RIGHT_ZERO;
        break;
      case 2:
        return LEFT_TWO_RIGHT_ZERO;
        break;
      case 3:
        return LEFT_THREE_RIGHT_ZERO;
        break;
      case 4:
        return LEFT_FOUR_RIGHT_ZERO;
        break;
      case 5:
        return LEFT_FIVE_RIGHT_ZERO;
        break;
      default:
        return ERROR_SG;
        break;
    }
  }

  countFingers = 5 * extendedFingersHand1 + extendedFingersHand2;

  switch (countFingers) {
    case 1:
      return LEFT_ZERO_RIGHT_ONE;
      break;
    case 2:
      return LEFT_ZERO_RIGHT_TWO;
      break;
    case 3:
      return LEFT_ZERO_RIGHT_THREE;
      break;
    case 4:
      return LEFT_ZERO_RIGHT_FOUR;
      break;
    case 5:
      return LEFT_ZERO_RIGHT_FIVE;
      break;
    case 6:
      return LEFT_ONE_RIGHT_ONE;
      break;
    case 7:
      return LEFT_ONE_RIGHT_TWO;
      break;
    case 8:
      return LEFT_ONE_RIGHT_THREE;
      break;
    case 9:
      return LEFT_ONE_RIGHT_FOUR;
      break;
    case 10:
      return LEFT_ONE_RIGHT_FIVE;
      break;
    case 11:
      return LEFT_TWO_RIGHT_ONE;
      break;
    case 12:
      return LEFT_TWO_RIGHT_TWO;
      break;
    case 13:
      return LEFT_TWO_RIGHT_THREE;
      break;
    case 14:
      return LEFT_TWO_RIGHT_FOUR;
      break;
    case 15:
      return LEFT_TWO_RIGHT_FIVE;
      break;
    case 16:
      return LEFT_THREE_RIGHT_ONE;
      break;
    case 17:
      return LEFT_THREE_RIGHT_TWO;
      break;
    case 18:
      return LEFT_THREE_RIGHT_THREE;
      break;
    case 19:
      return LEFT_THREE_RIGHT_FOUR;
      break;
    case 20:
      return LEFT_THREE_RIGHT_FIVE;
      break;
    case 21:
      return LEFT_FOUR_RIGHT_ONE;
      break;
    case 22:
      return LEFT_FOUR_RIGHT_TWO;
      break;
    case 23:
      return LEFT_FOUR_RIGHT_THREE;
      break;
    case 24:
      return LEFT_FOUR_RIGHT_FOUR;
      break;
    case 25:
      return LEFT_FOUR_RIGHT_FIVE;
      break;
    case 26:
      return LEFT_FIVE_RIGHT_ONE;
      break;
    case 27:
      return LEFT_FIVE_RIGHT_TWO;
      break;
    case 28:
      return LEFT_FIVE_RIGHT_THREE;
      break;
    case 29:
      return LEFT_FIVE_RIGHT_FOUR;
      break;
    case 30:
      return LEFT_FIVE_RIGHT_FIVE;
      break;
    default:
      return ERROR_SG;
      break;
  }
}
