#include "SelectiveRepeat.h"
#include "MyTimer.h"
#include <random>
#include <time.h>
#include <Windows.h>
#include <iostream>

using namespace std;

int SelectiveRepeat::createFrame(int frameSize){
	
	srand(time(NULL));
	this->sendingBuff = new int[frameSize];
	this->receivingBuff = new int[frameSize];
	this->packetNumber = new int[frameSize];
	this->ack = new int[frameSize];
	int random = (rand()+1)%frameSize;
	for (int i = 0; i < frameSize; i++){
		packetNumber[i] = -1;
	}
	for (int i = 0; i < frameSize; i++){
		getSendingBuff()[i] = i%random;
	}
	for (int i = 0; i < frameSize; i++){
		getReceivingBuff()[i] = -1;
	}
	for (int i = 0; i < frameSize; i++){
		getAck()[i] = -1;
	}
	return 0;
}

void SelectiveRepeat::flowControl(int frameSize, int windowSize){
	int* packetNumber = getPacketNumber();
	sendingSecond = sendingFirst;
	sendingControl(frameSize, packetNumber, windowSize);
	recevingControl(frameSize, packetNumber, windowSize);
	for (int i = 0; i < frameSize; i++){
		if (ack[i] == 1){
			if (i >= 13)
				sendingFirst = 13;
			else
				sendingFirst = i+1;
		}
		else
			break;
	}
	
	for (int i = 0; i < frameSize; i++){
		if (ack[i] == 1 && packetNumber[i] == 1)
			if (i >= 12)
				receivingFirst = 13;
			else
			receivingFirst = i+1;
		else
			break;
	}
}

int SelectiveRepeat::printOut(){
	flowControl(frameSize, windowSize);
	return 1;
}

void SelectiveRepeat::sendingControl(int frameSize, int* packetNumber, int windowSize){
	int* sendingBuff = getSendingBuff();
	tempDataSize = 0;
	for (int i = sendingFirst; i < sendingFirst + windowSize; i++){
		if (i >= frameSize)
			break;
		else if (packetNumber[i] == -1){
			if (!errorProbability()){
				packetNumber[i] = 1;
				tempData[tempDataSize++] = sendingBuff[i];
			}
		}
	}
}

void SelectiveRepeat::recevingControl(int frameSize, int* packetNumber, int windowSize){
	int* receivingBuff = getReceivingBuff();
	tempAckSize = 0;
	for (int i = sendingFirst; i < sendingFirst + windowSize; i++){
		if (i >= frameSize)
			break;
		else if (packetNumber[i] == 1&&ack[i]!=1){
			receivingBuff[i] = sendingBuff[i];
			if (!errorProbability()){
				ack[i] = 1;
				tempAck[tempAckSize++] = receivingBuff[i];
			}
		}
	}
}


bool SelectiveRepeat::errorProbability()
{
	if (rand() % 4 == 0) {
		return true;
	} else
	{
		return false;
	}
}

