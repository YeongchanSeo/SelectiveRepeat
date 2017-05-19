#pragma once
class MyTimer
{
private:
	int startTime;
	int finishTime;
public:
	MyTimer(int startTime, int finishTime){
		this->startTime = startTime;
		this->finishTime = finishTime;
	}
	void setStartTime(int startTime);
	void setFinishTime(int finishTime);
	int getStartTime();
	int getFinishTime();
	void setTimer(int startTime, int finishTime);
};

