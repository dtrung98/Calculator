#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
const int BYTESIZE = 8;
const int HEXSIZE = 4;
class QInt
{
	int _size; //Biến lưu trữ kích thước số nguyên (bit)
	__int64* _arrayBits; //Thành phần lưu trữ của kiểu dữ liệu, có thể mở rộng lên từ 128 đến 256 bit
	void Divide(const QInt& num, QInt& quotient, QInt& surplus);
public:
	QInt();
	void Clear();
	QInt(int size);
	QInt(const QInt& num);
	~QInt();
	static std::string Fgets(std::ifstream& fin);
	static void StrToken(std::string str, std::vector<std::string>& data, int& count);
	//Lấy chuỗi từ file, dừng khi gặp dấu xuống dòng, cấp phát động
	static std::string Cal3Token(std::vector<std::string>& data,QInt&);
	static std::string Cal4Token(std::vector<std::string>& data,QInt&);
	static std::string LoadFile(std::ifstream& fin);
	static std::string LoadFile(std::ifstream& fin, std::string&,QInt&);
	void InputDec(std::string& str);
	void InputHex(std::string& str);
	void InputBin(std::string& str);
	std::string BinToDec();
	std::string ShowBin();
	std::string BinToHex();
	/*std::string* Input(char* fileName);*/
	QInt operator&(const QInt& num);
	QInt operator|(const QInt& num);
	QInt operator^(const QInt& num);
	void operator=(const QInt& num);
	QInt operator+(const QInt& num);
	QInt operator-(const QInt& num); //Nạp chồng toán tử trừ
	char QInt::getBit(int position) const;
	void QInt::setBit(int position, char valueBit);
	QInt operator*(const QInt& num);
	QInt operator/(const QInt& num);
	QInt operator%(const QInt& num);
	QInt operator~();
	QInt Reverse();
	QInt operator>>(int numOfPos);
	QInt ShiftRight1Unit();
	QInt operator<<(int numOfPos);
	QInt ShiftLeft1Unit();
	QInt RotateRight();
	QInt RotateLeft();
	bool IsZero();
};