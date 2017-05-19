#pragma once
class SelectiveRepeat
{
private:
	int frameSize;
	int windowSize;
	int* ack;
	int* packetNumber;
	int* sendingBuff;
	int* receivingBuff;
public:
	int sendingFirst=0;
	int sendingSecond=0;
	int receivingFirst=0;
	int receivingSecond = 0;
	int tempData[5];
	int tempDataSize;
	int tempAck[5];
	int tempAckSize;
	SelectiveRepeat(int frameSize, int windowSize){
		this->frameSize = frameSize;
		this->windowSize = windowSize;
		createFrame(frameSize);
	}
	
	void flowControl(int frameSize, int windowSize);
	void sendingControl(int frameSize, int* packetNumber, int windowSize);
	void recevingControl(int frameSize, int* packetNumber, int windowSize);
	bool errorProbability();
	int printOut();
	int* getAck(){
		return ack;
	}
	int getWindowSize(){
		return windowSize;
	}
	int* getSendingBuff(){
		return sendingBuff;
	}
	int getFrameSize(){
		return frameSize;
	}
	int* getReceivingBuff(){
		return receivingBuff;
	}
	int* getPacketNumber(){
		return packetNumber;
	}
	int createFrame(int frameSize);
	void deleteFrame(SelectiveRepeat sr){
		delete[] sendingBuff;
	}
};
