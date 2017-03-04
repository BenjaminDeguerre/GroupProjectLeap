#include "GestControl.hpp"


GestControl::Handler GestControl::handler = GestControl::Handler();

GestControl& GestControl::getInstance() {
	if (handler.instance == 0)
		handler.instance = new GestControl();
	return *handler.instance;
}

void GestControl::freeInstance() {
	if (handler.instance != 0) 
		delete handler.instance;
	handler.instance = 0;
	
}

bool GestControl::setGesture(int id) {
	
	if (gestureId == id)
		count++;
	//if we change gesture
	else
		count = 1;

	gestureId = id;

	//Call controller on the count
	if (count == frameLimit) {
		//validateGesture(gestureId);
		count = 0;
		return true;
	}

	return false;
}

/*void GestControl::validateGesture(int id){

	std::cout << id << std::endl;
}*/