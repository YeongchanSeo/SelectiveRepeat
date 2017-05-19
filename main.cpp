#include <iostream>
#include <Windows.h>
#include <string>
#include <string.h>
#include <time.h>
#include "SelectiveRepeat.h"
#include "ErrorDetection.h"
#include "MyTImer.h"
#define BLACK 0
#define DARK_BLUE 1
#define DARK_GREEN 2
#define DARK_SKY 3
#define DARK_RED 4
#define DARK_PUPPLE 5
#define DARK_YELLOW 6
#define GRAY 7
#define DARK_GRAY 8
#define BLUE 9
#define GREEN 10
#define SKY 11
#define RED 12
#define PUPPLE 13
#define YELLOW 14
#define WHITE 15

using namespace std;

void gotoxy(int x, int y)//x,y좌표에 원하는 내용을 찍을 수 있도록 설정
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void color(int background, int text){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), background * 16 + text);
}

void printUI(int x, int y, int sizeX, int sizeY);
void printWindowUI(int x, int y, int sizeX, int sizeY);
void deleteWindowUI(int x, int y, int sizeX, int sizeY);
void printDataSend(int x, int y, int* data, int dataSize);
void printAckSend(int x, int y, int* data, int dataSize);
void printMessage(char* str);
int main()
{
	int stime = 0;
	int ftime = 0;
	for (int i = 0; i <= 80; i++){
		for (int j = 0; j <= 25; j++){
			gotoxy(i, j);
			color(WHITE, BLACK);
			cout << " ";
		}
	}
	gotoxy(1, 1);
	gotoxy(33, 3);
	cout << "Selective Repeat";
	gotoxy(62, 24);
	cout << "20112149 서영찬";
	SelectiveRepeat sr = SelectiveRepeat(17,4);
	ErrorDetection ed = ErrorDetection();
	MyTimer tm = MyTimer(0,0);
	printUI(8,5, 35, 3);
	printUI(8,18, 35, 3);
	for(int t = 0;;t++){
		for (int i = 0; i < sr.getFrameSize(); i++){
			gotoxy(10 + 4* i, 7);
			if (sr.getAck()[i] == 1){
				color(WHITE, RED);
			}
			else{
				color(WHITE, BLACK);
			}
			cout << sr.getSendingBuff()[i];
		}
		if (t == 0){
			color(WHITE, BLUE);
			printWindowUI((sr.receivingFirst) * 4 + 8, 18, sr.getWindowSize() * 2 + 1, 3);
		}
			deleteWindowUI(sr.sendingSecond * 4 + 8, 5, sr.getWindowSize() * 2 + 1, 3);
		color(WHITE, BLUE);
			printWindowUI(sr.sendingFirst * 4 + 8, 5, sr.getWindowSize() * 2 + 1, 3);
			int total = 0;
			for (int i = 0; i < sr.getFrameSize(); i++){
				if (sr.getAck()[i] == 1&&sr.getPacketNumber()[i] ==1)
					total += 1;
			}
			if (total == sr.getFrameSize()){
				gotoxy(40, 30);
				color(BLACK, WHITE);
				int* num = new int[8];
				num[0] = 1;
				for (int i = 1; i < 5; i++)
					num[i] = rand() % 2;

				ed.errorDetect(num);
				return 0;
			}
		sr.printOut();
		if (sr.tempDataSize == 0){
			tm.setStartTime(++stime);
			if (stime >= 2)
				printMessage("DATA 재전송");
		}
		if (sr.tempAckSize == 0){
			tm.setFinishTime(++ftime);
			if (ftime >= 2)
				printMessage("ACK 재전송");
		}
		color(WHITE, BLACK);
		printDataSend(35, 10, sr.tempData, sr.tempDataSize);

		for (int i = 0; i < sr.getFrameSize(); i++){
			gotoxy(10 + 4 * i, 20);
			if (sr.getReceivingBuff()[i] != -1)
				cout << sr.getReceivingBuff()[i];
		}
		int x = 0;
		while (sr.getReceivingBuff()[x++] != -1&&x<sr.getFrameSize());
		if (x >= 14)
			x = 14;
		sr.receivingFirst = x-1;
		deleteWindowUI((sr.receivingSecond) * 4 + 8, 18, sr.getWindowSize() * 2 + 1, 3);
		color(WHITE, BLUE);
		printWindowUI((sr.receivingFirst) * 4 + 8, 18, sr.getWindowSize() * 2 + 1, 3);
		sr.receivingSecond = sr.receivingFirst;
		printAckSend(35, 14, sr.tempAck, sr.tempAckSize);
	}
	return 0;
}

void printMessage(char* str){
	for (int i = 0; i < 2; i++){
		gotoxy(35, 13);
		color(WHITE, BLACK);
		cout << str;
		Sleep(500);
		gotoxy(35, 13);
		color(WHITE, WHITE);
		cout << str;
		Sleep(500);
	}
}

void printUI(int x, int y, int sizeX, int sizeY)
{
	gotoxy(x, y++);
	cout << "┏";
	for (int i = 0; i < sizeX-2; i++)
		cout << "━";
	cout << "┓";
	for (int i = 0; i < sizeY; i++){
		gotoxy(x, y);
		cout << "┃";

		gotoxy(x + 2 * (sizeX - 1), y++);
		cout << "┃";
	}
	gotoxy(x, y);
	cout << "┗";
	for (int i = 0; i < sizeX - 2; i++)
		cout << "━";
	gotoxy(x + 2 * (sizeX - 1), y);
	cout << "┛";
}

void printWindowUI(int x, int y, int sizeX, int sizeY)
{
	gotoxy(x, y - 1);
	cout<<"window";
	gotoxy(x, y++);
	cout << "┏";
	for (int i = 0; i < sizeX - 2; i++)
		cout << "━";
	cout << "┓";
	for (int i = 0; i < sizeY; i++){
		gotoxy(x, y);
		cout << "┃";

		gotoxy(x + 2 * (sizeX - 1), y++);
		cout << "┃";
	}
	gotoxy(x, y);
	cout << "┗";
	for (int i = 0; i < sizeX - 2; i++)
		cout << "━";
	gotoxy(x + 2 * (sizeX - 1), y);
	cout << "┛";
}

void deleteWindowUI(int x, int y, int sizeX, int sizeY){
	color(WHITE, WHITE);
	gotoxy(x, y - 1);
	cout << "window";
	gotoxy(x, y++);
	color(WHITE, BLACK);
	if (x == 8)
	cout << "┏";
	else
		cout << "━";
	for (int i = 0; i < sizeX - 1; i++)
		cout << "━";
	for (int i = 0; i < sizeY; i++){
		gotoxy(x, y);
		if (x==8)
			color(WHITE, BLACK);
		else
			color(WHITE, WHITE);
		cout << "┃";
		color(WHITE, WHITE);
		gotoxy(x + 2 * (sizeX - 1), y++);
		cout << "┃";
	}
	color(WHITE, BLACK);
	gotoxy(x, y);
	if (x == 8)
	cout << "┗";
	else
		cout << "━";
	for (int i = 0; i < sizeX - 2; i++)
		cout << "━";

}
void printUI2(int x, int y, int sizeX, int sizeY, int* data, int dataSize, string msg)
{
	gotoxy(x, y++);
	cout << "";
	for (int i = 0; i < sizeX - 2; i++)
		cout << "";
	cout << "";
	gotoxy(x + 3, y);
	for (int i = 0; i < dataSize; i++){
		cout << data[i];
		if (i < dataSize - 1)
			cout << "/";
	}
	for (int i = 0; i < sizeY; i++){
		gotoxy(x, y);
		cout << "";
		gotoxy(x + sizeX - 1, y);
		gotoxy(x + 2 * (sizeX - 1), y++);
		cout << "";
	}
	gotoxy(x+5, y - 1);
	cout << msg;

}

void printDataSend(int x,int y, int* data, int dataSize){
	for (int i = 0; i < 4; i++){
		color(WHITE, BLACK);
		printUI2(x, y, 10, 2, data, dataSize,"DATA");
		Sleep(300);
		color(WHITE, WHITE);
		printUI2(x, y++, 10,2,data, dataSize,"DATA");
	}
	color(WHITE, BLACK);
}

void printAckSend(int x, int y, int* data, int dataSize){
	for (int i = 0; i < 4; i++){
		color(WHITE, BLACK);
		printUI2(x, y, 6, 2, data, dataSize,"ACK");
		Sleep(300);
		color(WHITE, WHITE);
		printUI2(x, y--, 6, 2, data, dataSize,"ACK");
	}
	color(WHITE, BLACK);
}