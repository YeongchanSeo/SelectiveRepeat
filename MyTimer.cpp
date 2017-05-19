#include "MyTimer.h"

void MyTimer::setStartTime(int startTime){
	this->startTime = startTime;	
}

int MyTimer::getStartTime(){
	return this->startTime;
}

void MyTimer::setFinishTime(int finishTime){
	this->finishTime = finishTime;
}

int MyTimer::getFinishTime(){
	return this->finishTime;
}

void MyTimer::setTimer(int startTime, int finishTime){
	setStartTime(startTime);
	setFinishTime(finishTime);
}