#pragma once
class ErrorDetection
{
private:
	int* codeword;
	int length;
	int* remainder;
	char* divisor = "1011";
public:
	bool errorDetect(int* dataword);
	int crc();
	void xor();
};

