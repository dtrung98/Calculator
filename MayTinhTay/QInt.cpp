#include"QInt.h"

QInt::QInt()
{
	_size = 2;
	_arrayBits = new __int64[_size];
	for (int i = 0; i < _size; i++)
		_arrayBits[i] = 0;
}
void QInt::Clear() {
	for (int i = 0; i < _size; i++)
		_arrayBits[i] = 0;
}
QInt::QInt(int size)
{
	_size = size;
	_arrayBits = new __int64[_size];
	for (int i = 0; i < _size; i++)
		_arrayBits[i] = 0;
}

QInt::QInt(const QInt& num)
{
	_size = num._size;
	_arrayBits = new __int64[_size];
	for (int i = 0; i < _size; i++)
		_arrayBits[i] = num._arrayBits[i];
}

QInt::~QInt()
{
	delete[] _arrayBits;
	_arrayBits = NULL;
}


void QInt::operator=(const QInt& num)
{
	if (this == &num)
		return;
	if (_arrayBits != NULL)
	{
		delete[] _arrayBits;
		_arrayBits = NULL;
	}
	_size = num._size;
	_arrayBits = new __int64[_size];
	for (int i = 0; i < _size; i++)
		_arrayBits[i] = num._arrayBits[i];
}


QInt QInt::operator&(const QInt& num)
{
	QInt result;
	result._size = _size;
	for (int i = 0; i < _size; i++)
		result._arrayBits[i] = _arrayBits[i] & num._arrayBits[i];
	return result;
}

QInt QInt::RotateRight()
{
	__int64 mask1 = 0x8000000000000000;
	__int64 mask2 = 0x7FFFFFFFFFFFFFFF;
	QInt result(*this);
	if ((result._arrayBits[_size - 1] & 1) != 0)
	{
		result = result >> 1;
		result._arrayBits[0] = result._arrayBits[0] | mask1;
	}
	else
	{
		result = result >> 1;
		result._arrayBits[0] = result._arrayBits[0] & ((unsigned __int64)mask2 >> 1);
	}
	return result;
}

QInt QInt::RotateLeft()
{
	__int64 mask1 = 0x8000000000000000;
	__int64 mask2 = 0x7FFFFFFFFFFFFFFF;
	QInt result(*this);
	if ((result._arrayBits[0] & mask1) != 0)
	{
		result = result << 1;
		result._arrayBits[_size - 1] = result._arrayBits[_size - 1] | 1;
	}
	else
	{
		result = result << 1;
	}
	return result;
}

QInt QInt::operator|(const QInt& num) //Nạp chồng toán tử OR
{
	QInt result(_size);
	for (int i = 0; i < _size; i++)
	{
		result._arrayBits[i] = _arrayBits[i] | num._arrayBits[i];
	}
	return result;
}

QInt QInt::operator>>(int numOfPos) //Nạp chồng toán tử dịch bit phải
{
	QInt result(*this);
	if (numOfPos == 0)
	{
		return result;
	}
	else
	{

		for (int i = 0; i < numOfPos; i++)
		{
			result = result.ShiftRight1Unit();
		}
	}
	return result;
}

QInt QInt::ShiftRight1Unit() //Dịch phải một đơn vị
{
	QInt result(*this);
	for (int i = _size - 1; i > 0; i--)
	{
		__int64 temp = 1;
		temp = temp & result._arrayBits[i - 1];
		result._arrayBits[i] = (unsigned __int64)result._arrayBits[i] >> 1;//Ép kiểu tất cả các phần tử từ thứ nhất đến cuối để dịch phải theo luận lí
		if (temp != 0)
		{
			__int64 temp2 = 0x8000000000000000;
			result._arrayBits[i] = result._arrayBits[i] | temp2;
		}
	}
	result._arrayBits[0] = result._arrayBits[0] >> 1;
	return result;
}

QInt QInt::ShiftLeft1Unit() //Dịch trái một đơn vị
{
	QInt result(*this);
	for (int i = 0; i < _size - 1; i++)
	{
		__int64 temp = 0x8000000000000000;
		temp = temp & result._arrayBits[i + 1];
		result._arrayBits[i] = result._arrayBits[i] << 1;
		if (temp != 0)
		{
			__int64 temp2 = 1;
			result._arrayBits[i] = result._arrayBits[i] | temp2;
		}
	}
	result._arrayBits[_size - 1] = result._arrayBits[_size - 1] << 1;
	return result;
}

QInt QInt::operator<<(int numOfPos) //Nạp chồng toán tử dịch bit trái
{
	QInt result(*this);
	if (numOfPos == 0)
	{
		return result;
	}
	else
	{

		for (int i = 0; i < numOfPos; i++)
		{
			result = result.ShiftLeft1Unit();
		}
	}
	return result;
}

QInt QInt::Reverse()
{
	QInt result(_size);

	for (int i = 0; i < _size; i++)
	{
		__int64 temp = 1;
		for (int j = 0; j < sizeof(__int64)* BYTESIZE; j++)
		{
			if ((_arrayBits[i] & (temp << j)) == 0)
			{
				result._arrayBits[i] = result._arrayBits[i] | (temp << j);
			}
		}
	}
	return result;
}
QInt QInt::operator^(const QInt& num) //Nạp chồng toán tử xor
{
	QInt answer(*this);
	for (int i = 0; i < _size; i++)
	{
		answer._arrayBits[i] = _arrayBits[i] ^ num._arrayBits[i];
	}
	return answer;
}

QInt QInt::operator~() //Nạp chồng toán tử xor
{
	return this->Reverse();
}

QInt QInt::operator+(const QInt& num)
{
	QInt result(_size);
	__int64 temp = 0;
	for (int i = _size - 1; i >= 0; i--)
	{
		__int64 mask1 = 1, mask2 = 1;
		__int64 tmp1, tmp2;
		int k = 0;
		while (k < sizeof(__int64)* BYTESIZE)
		{
			tmp1 = _arrayBits[i] & mask1;
			tmp2 = num._arrayBits[i] & mask2;
			if (((tmp1 != 0) && (tmp2 != 0)) || ((tmp1 == 0) && (tmp2 == 0)))
			{
				if (temp == 1)
					result._arrayBits[i] = result._arrayBits[i] | mask1;
				if ((tmp1 != 0) && (tmp2 != 0))
					temp = 1;
				if ((tmp1 == 0) && (tmp2 == 0))
					temp = 0;
			}
			else
			{
				__int64 subMask = 0xFFFFFFFFFFFFFFFF;
				if (temp == 1)
					result._arrayBits[i] = result._arrayBits[i] & (mask1 ^ subMask);
				else
				{
					result._arrayBits[i] = result._arrayBits[i] | mask1;
				}
			}
			mask1 = mask1 << 1;
			mask2 = mask2 << 1;
			k++;
		}
	}
	return result;
}

QInt QInt::operator-(const QInt& num) //Nạp chồng toán tử trừ
{
	QInt tempThis(*this);
	QInt tempNum(num);
	QInt temp(_size);
	temp._arrayBits[_size - 1] = 1;
	QInt result(_size);
	result = tempThis + ((tempNum.Reverse()) + temp);
	return result;
}

char QInt::getBit(int position) const
{
	int locate = position / (sizeof(__int64)*BYTESIZE);
	position = position % (sizeof(__int64)*BYTESIZE);
	if ((_arrayBits[_size - 1 - locate] & (1 << position)) != 0)
		return 1;
	return 0;
}

void QInt::setBit(int position, char valueBit)
{
	QInt mask(_size);
	mask._arrayBits[_size - 1] = 1;
	if (valueBit == 1)
	{
		*this = *this | (mask << position);
		return;
	}
	*this = *this & (~(mask << position));
}

QInt QInt::operator*(const QInt& M)
{
	QInt A(_size);
	QInt Q(*this);
	char Q_1 = 0;
	char Q0 = 0;
	int size = _size;
	for (int i = 0; i < sizeof(__int64)*BYTESIZE; i++)
	{
		Q0 = Q.getBit(0);
		if (Q0 == 1 && Q_1 == 0)
			A = A - M;
		if (Q0 == 0 && Q_1 == 1)
			A = A + M;
		// shr [A, Q, Q_1]
		Q_1 = Q0;
		Q = Q >> 1;
		Q.setBit(sizeof(__int64)*BYTESIZE - 1, A.getBit(0));
		A = A >> 1;
	}
	return Q;
}

void QInt::Divide(const QInt& num, QInt& quotient, QInt& surplus)
{
	QInt a(_size);//khởi tạo kích thước của a = với *this
	QInt sumTemp(2 * _size);//khởi tạo kích thước của [a,số chia] = 
	__int64 test = 1;
	for (int i = _size; i < sumTemp._size; i++)//lắp số chia vào sumTemp
	{
		sumTemp._arrayBits[i] = _arrayBits[i - _size];
	}
	if ((_arrayBits[0] & (test << (sizeof(__int64)* BYTESIZE - 1))) != 0)//Nếu bit đầu tiên là 1 thì là số âm nên tất cả bit của a là 1
	{
		for (int i = 0; i < _size; i++)
			a._arrayBits[i] = 0xFFFFFFFFFFFFFFFF;
	}
	else//Nếu bit đầu tiên khác 1 tức là 0 thì tất cả các bit của a là 0 
	{
		for (int i = 0; i < _size; i++)
			a._arrayBits[i] = 0;
	}
	int k = sizeof(__int64)* _size * BYTESIZE;//Khai báo k = n là số bit của QInt
	while (k>0)
	{
		for (int i = 0; i < _size; i++)
		{
			sumTemp._arrayBits[i] = a._arrayBits[i];//lắp a vào sumTemp
		}
		sumTemp = sumTemp << 1;//dịch trái
		for (int i = 0; i < _size; i++)
			a._arrayBits[i] = sumTemp._arrayBits[i];
		a = a - num;
		if ((a._arrayBits[0] & 0x8000000000000000) != 0)
		{

			__int64 soAsToZero = 0xFFFFFFFFFFFFFFFE;//Khởi tạo biến này để làm bit Qo = 0
			sumTemp._arrayBits[sumTemp._size - 1] = sumTemp._arrayBits[sumTemp._size - 1] & soAsToZero;
			a = a + num;
		}
		else
		{
			sumTemp._arrayBits[sumTemp._size - 1] = sumTemp._arrayBits[sumTemp._size - 1] | 1;//Qo = 1
		}
		k--;
	}
	for (int i = _size; i < sumTemp._size; i++)
		quotient._arrayBits[i - _size] = sumTemp._arrayBits[i];
	for (int i = 0; i < _size; i++)
		surplus._arrayBits[i] = a._arrayBits[i];
}

QInt QInt::operator/(const QInt& num)
{
	QInt quotient(_size);
	QInt surplus(_size);
	Divide(num, quotient, surplus);
	return quotient;
}

QInt QInt::operator%(const QInt& num)
{
	QInt quotient(_size);
	QInt surplus(_size);
	Divide(num, quotient, surplus);
	return surplus;
}

//Lấy chuỗi từ file, dừng khi gặp dấu xuống dòng, cấp phát động
std::string QInt::Fgets(std::ifstream& fin)
{
	std::string str;
	char c;
	do
	{
		c = fin.get();
		if (c == EOF)
			break;
		if (c == '\n')
			break;
		str.push_back(c); //Gán kí tự vừa nhập vào chuỗi
	} while (c != EOF); //Nếu là cuối file cũng sẽ dừng nhập
	return str;
}
std::string hexToBin(std::string hex) {
	std::string result = "";

	int dec_value;
	int cur = hex.length() - 1;

	while (cur != -1) {
		dec_value = hex[cur] - '0';
		if (dec_value > 9) dec_value -= 7;
		// mỗi chứ số hexa tương ứng là 4 bit nhị phân 
		//bin_value =""+ (dec_value >> 4 + '0') + (dec_value >> 3 & 1 +'0') + (dec_value >> 2 & 1 +'0') + (dec_value >> 1 & 1 +'0');
		for (int i = 0; i != 4; i++)
			result = ((char)((dec_value >> i & 1) + '0')) + result;
		cur--;
	}
	//ta thêm 0 cho đủ 128 bits
	for (int i = 128 - result.length(); i != 0; i--)
		result = '0' + result;
	return result;
}


void QInt::InputBin(std::string& str)
{
	QInt mask(_size);
	mask._arrayBits[_size - 1] = 1;
	int min = 0;
	if (str.size() > _size * sizeof(__int64)* BYTESIZE)
		min = str.size() - 1 - _size * sizeof(__int64)* BYTESIZE;
	for (int i = str.size() - 1; i >= min; i--)
	{
		if (str[i] == '1')
			*this = *this | (mask << (str.size() - 1 - i));
	}
}

bool QInt::IsZero()
{
	for (int i = 0; i < _size; i++)
	{
		if (_arrayBits[i] != 0)
			return false;
	}
	return true;
}

std::string QInt::BinToDec()
{
	std::string decimal;
	QInt quotient(_size), surplus(_size), temp(*this);
	QInt number(_size);
	number._arrayBits[_size - 1] = 10;
	if ((this->_arrayBits[0] & 0x8000000000000000) != 0)
	{
		temp = temp.Reverse() + 1;
	}
	quotient = temp;
	while (!quotient.IsZero())
	{
		surplus = quotient % number;
		quotient = quotient / number;
		int temp = surplus._arrayBits[_size - 1];
		std::string sub;
		sub = std::to_string(temp);
		decimal.insert(0, sub);
	}
	if ((this->_arrayBits[0] & 0x8000000000000000) != 0)
	{
		decimal.insert(0, 1, '-');
	}
	return decimal;
}

void QInt::InputDec(std::string& mainstr)
{
	std::string str = mainstr;
	QInt mask(_size);
	QInt temp(_size);
	QInt base(_size);
	QInt maskAsOne(_size);
	mask._arrayBits[_size - 1] = 10;
	base._arrayBits[_size - 1] = 1;
	maskAsOne._arrayBits[_size - 1] = 1;

	if (str[0] != '-')
	{
		for (int i = str.size() - 1; i >= 0; i--)
		{
			temp._arrayBits[_size - 1] = (__int64)atoi(&str[i]);
			*this = *this + base*temp;
			base = base*mask;
			str.pop_back();
		}
	}
	if (str[0] == '-')
	{
		for (int i = str.size() - 1; i >= 1; i--)
		{
			temp._arrayBits[_size - 1] = (__int64)atoi(&str[i]);
			*this = *this + base*temp;
			base = base*mask;
			str.pop_back();
		}
		*this = this->Reverse() + maskAsOne;
	}
}

std::string QInt::ShowBin()
{
	std::string binary;
	__int64 temp = 0x8000000000000000;
	int flag = 0;
	for (int i = 0; i < _size; i++)
	{
		temp = 0x8000000000000000;
		for (int j = 0; j < BYTESIZE * sizeof(__int64); j++)
			if ((this->_arrayBits[i] & ((unsigned __int64)temp >> j)) != 0)
			{
				binary.push_back('1');
				flag = 1;
			}
			else
				if (flag == 1 || ((i == _size - 1) && (j == BYTESIZE * sizeof(__int64) - 1)))
					binary.push_back('0');

	}
	return binary;
}

std::string QInt::BinToHex()
{
	int size = _size;
	std::string hexadecimal = "";
	std::string subHex;
	QInt temp(size);
	int hexa;
	temp._arrayBits[size - 1] = 0xF;
	char hex[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	for (int i = 0; i < ((size * sizeof(__int64)*BYTESIZE) / 4); i++)
	{
		hexa = ((*this >> (HEXSIZE*i)) & temp)._arrayBits[_size - 1];
		hexadecimal.insert(0, 1, hex[hexa]);
	}
	for (int i = 0; i < hexadecimal.size(); i++)
	{
		if (hexadecimal[i] != '0')
		{
			subHex = hexadecimal.substr(i);
			break;
		}
	}
	return subHex;
}

void QInt::InputHex(std::string& str)
{
	for (int i = str.length() - 1; i > -1; i--)
	{
		int j = str.length() - i - 1;
		switch (str[i])
		{
		case '0':	break;
		case '1':	setBit((j << 2), 1);
			break;
		case '2':	setBit((j << 2) + 1, 1);
			break;
		case '3':	setBit((j << 2), 1);	setBit((j << 2) + 1, 1);
			break;
		case '4':	setBit((j << 2) + 2, 1);
			break;
		case '5':	setBit((j << 2) + 2, 1);	setBit((j << 2), 1);
			break;
		case '6':	setBit((j << 2) + 2, 1);	setBit((j << 2) + 1, 1);
			break;
		case '7':	setBit((j << 2) + 2, 1);	setBit((j << 2) + 1, 1);	setBit((j << 2), 1);
			break;
		case '8':	setBit((j << 2) + 3, 1);
			break;
		case '9':	setBit((j << 2) + 3, 1);	setBit((j << 2), 1);
			break;
		case 'A':	setBit((j << 2) + 3, 1);	setBit((j << 2) + 1, 1);
			break;
		case 'B':	setBit((j << 2) + 3, 1);	setBit((j << 2), 1);	setBit((j << 2) + 1, 1);
			break;
		case 'C':	setBit((j << 2) + 3, 1);	setBit((j << 2) + 2, 1);
			break;
		case 'D':	setBit((j << 2) + 3, 1);	setBit((j << 2) + 2, 1);	setBit((j << 2), 1);
			break;
		case 'E':	setBit((j << 2) + 3, 1);	setBit((j << 2) + 2, 1);	setBit((j << 2) + 1, 1);
			break;
		case 'F':	setBit((j << 2) + 3, 1); setBit((j << 2) + 2, 1);	setBit((j << 2) + 1, 1);	setBit((j << 2), 1);
			break;
		}

	}
}

std::string QInt::Cal3Token(std::vector<std::string>& data,QInt& result)
{
	std::string str;
	int base1, base2;
	base1 = atoi(data[0].c_str());
	if (data[1] == "ror" || data[1] == "rol")
	{
		if (base1 == 2)
			result.InputBin(data[2]);
		if (base1 == 10)
			result.InputDec(data[2]);
		if (base1 == 16)
			result.InputHex(data[2]);
		if (data[1] == "ror")
			result = result.RotateRight();
		if (data[1] == "rol")
			result = result.RotateLeft();
		if (base1 == 2)
			str = result.ShowBin();
		if (base1 == 10)
			str = result.BinToDec();
		if (base1 == 16)
			str = result.BinToHex();
	}
	else
	{
		if (data[1] == "~")
		{
			if (base1 == 2)
				result.InputBin(data[2]);
			if (base1 == 10)
				result.InputDec(data[2]);
			if (base1 == 16)
				result.InputHex(data[2]);
			result = ~result;
			if (base1 == 2)
				str = result.ShowBin();
			if (base1 == 10)
				str = result.BinToDec();
			if (base1 == 16)
				str = result.BinToHex();
		}
		else
		{
			base2 = atoi(data[1].c_str());
			if (base1 == 2)
			{
				result.InputBin(data[2]);
				if (base2 == 10)
					str = result.BinToDec();
				if (base2 == 16)
					str = result.BinToHex();
			}
			if (base1 == 10)
			{
				result.InputDec(data[2]);
				str = result.ShowBin();
			}
			if (base1 == 16)
			{
				result.InputHex(data[2]);
				str = result.ShowBin();
			}
		}
	}
	return str;
}

std::string QInt::Cal4Token(std::vector<std::string>& data,QInt& result)
{
	std::string str;
	QInt num1, num2;
	int base1, step;
	base1 = atoi(data[0].c_str());

	if (base1 == 2)
	{
		num1.InputBin(data[1]);
		if (data[2] == ">>" || data[2] == "<<")
			step = stoi(data[3]);
		else
			num2.InputBin(data[3]);
	}
	if (base1 == 10)
	{
		num1.InputDec(data[1]);
		if (data[2] == ">>" || data[2] == "<<")
			step = stoi(data[3]);
		else
			num2.InputDec(data[3]);
	}
	if (base1 == 16)
	{
		num1.InputHex(data[1]);
		if (data[2] == ">>" || data[2] == "<<")
			step = stoi(data[3]);
		else
			num2.InputHex(data[3]);
	}
	if (data[2] == "+")
		result = num1 + num2;
	if (data[2] == "-")
		result = num1 - num2;
	if (data[2] == "*")
		result = num1 * num2;
	if (data[2] == "/")
		result = num1 / num2;
	if (data[2] == "&")
		result = num1 & num2;
	if (data[2] == "|")
		result = num1 | num2;
	if (data[2] == "^")
		result = num1 ^ num2;
	if (data[2] == ">>")
		result = num1 >> step;
	if (data[2] == "<<")
		result = num1 << step;
	if (base1 == 2)
	{
		str = result.ShowBin();
	}
	if (base1 == 10)
	{
		str = result.BinToDec();
	}
	if (base1 == 16)
	{
		str = result.BinToHex();
	}
	return str;
}

void QInt::StrToken(std::string str, std::vector<std::string>& data, int& count)
{
	std::stringstream strStream(str);
	std::string subStr;
	count = 0;

	while (getline(strStream, subStr, ' ')) {
		data.push_back(subStr);
		//cout << data[count] << endl;
		count++;
	}
}
std::string QInt::LoadFile(std::ifstream& fin) {
	std::string output;
	QInt result;
	std::string str = QInt::Fgets(fin); //Gán từng dòng trong file vào str
	if (str == "") //Kiểm tra có gán được str không
	return "0";

	int count = 0;
	std::vector<std::string> data;
	QInt::StrToken(str, data, count);

	if (count == 3)
	{
		output = QInt::Cal3Token(data,result);
	}
	if (count == 4)
	{
		output = QInt::Cal4Token(data,result);
	}
	return output;
}
std::string QInt::LoadFile(std::ifstream& fin,std::string& firstline,QInt& result)
{
	std::string output;
	std::string str = QInt::Fgets(fin); //Gán từng dòng trong file vào str
	firstline = str;
	if (str == "") //Kiểm tra có gán được str không
	{
		firstline = "Your input file is invalid.";
		return "0";
	}
	int count = 0;
	std::vector<std::string> data;
	QInt::StrToken(str, data, count);

	if (count == 3)
	{
		output = QInt::Cal3Token(data,result);
	}
	if (count == 4)
	{
		output = QInt::Cal4Token(data,result);
	}
	return output;
}

