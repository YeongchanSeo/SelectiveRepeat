#include "ErrorDetection.h"
#include "SelectiveRepeat.h"
#include <iostream>

using namespace std;



bool ErrorDetection::errorDetect(int* dataword){
	length = 5;
	codeword = new int[length + strlen(divisor)];
	remainder = new int[length + strlen(divisor)];

	for (int i = 0; i < length; i++)
		codeword[i] = dataword[i];
	
	cout << endl << "                       -------------------------------------" << endl;
	cout << "                                 Error Detection            " << endl;
	cout << "                       -------------------------------------" << endl;
	cout << "                          Divisor: " << divisor << endl;

	for (int i = length; i<length + strlen(divisor) - 1; i++)
		codeword[i] = 0;
	cout << "                          Codeword : "; 
	for (int i = 0; i < length + strlen(divisor)-1; i++)
		cout << codeword[i];
	cout << endl;
	crc();
	cout << "                          Remainder : ";
	for (int i = 0; i < strlen(divisor) - 1; i++)
		cout << remainder[i];
	cout << endl;
	for (int i = length; i<length + strlen(divisor) - 1; i++)
		codeword[i] = remainder[i - length];
	cout << "                          Final codeword : ";
	for (int i = 0; i < length + strlen(divisor) - 1; i++)
		cout << codeword[i];
	cout << endl;
	length = 9;
	for (int i = length; i<length + strlen(divisor) - 1; i++)
		codeword[i] = 0;
	crc();
	cout << "                          Syndrom : ";
	for (int i = 0; i < strlen(divisor)-1; i++)
		cout << remainder[i];
	cout << endl;
	cout << "                       -------------------------------------" << endl;
	exit(1);
	return true;
}

int ErrorDetection::crc()
{ 
	int i, j;

	for (i = 0; i < strlen(divisor); i++)
		remainder[i] = codeword[i];
	
	do{
		if (remainder[0] == '1')
			xor();
		for (j = 0; j < strlen(divisor) - 1; j++)
			remainder[j] = remainder[j + 1];
		remainder[j] = codeword[i++];
		
	} while (i <= length + strlen(divisor) - 1);

	return 0;
}

void ErrorDetection::xor()
{
	for (int i = 1; i < strlen(divisor); i++)
	{
		if (remainder[i] == divisor[i])
			remainder[i] = '0';
		else
			remainder[i] = '1';
	}
}