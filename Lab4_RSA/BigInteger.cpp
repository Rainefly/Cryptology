#include<iostream>
#include<math.h>
#include<string>
#include<time.h>
#include<stdlib.h>
#include<fstream>

#include"BigInt.h"     // �Զ������������
using namespace std;


BigInte::BigInte()         // ȫ������
{
	int i;
	for (i = 0; i < max; i++)
	{
		num[i] = 0;
	}
	sign = 0;
}

BigInte::BigInte(int in)       // ʮ����ת�ɶ����ƴ洢���ұ�Ϊ���λ��
{
	if (in >= 0)
		sign = 0;
	else 
		sign = 1;
	int i = 0;
	while (in)
	{
		num[i] = in % 2;
		in = in / 2;
		i++;
	}
	for (; i < max; i++)
	{
		num[i] = 0;
	}
}

BigInte::BigInte(string in)        // ʮ������ת�����ƴ洢���ұ�Ϊ���λ��
{
	int i, j = 0;
	int temp;
	for (i = 0; i < max; i++) {
		num[i] = 0;
	}
	for (i = in.length() - 1; i >= 0; i--) {
		if (in[i] >= 'a' && in[i] <= 'f') {
			temp = in[i] - 'a' + 10;
		}
		else {
			if (in[i] >= 'A' && in[i] <= 'F') {
				temp = in[i] - 'A' + 10;
			}
			else {
				temp = in[i] - '0';
			}
		}
		if (temp / 8) {
			num[4 * j + 3] = 1;
		}
		if ((temp % 8) / 4) {
			num[4 * j + 2] = 1;
		}
		if ((temp % 4) / 2) {
			num[4 * j + 1] = 1;
		}
		if (temp % 2) {
			num[4 * j] = 1;
		}
		j++;
	}
	sign = 0;
}

BigInte::BigInte(string in,int a)        // ʮ������ת�����ƴ洢���ұ�Ϊ���λ��
{
	int i, j = 0;
	int temp;
	for (i = 0; i < max; i++) {
		num[i] = 0;
	}
	for (i = in.length()-1; i >= 0; i--) {
		if (in[i] >= 'a' && in[i] <= 'f') {
			temp = in[i] - 'a' + 97;
		}
		else {
			if (in[i] >= 'A' && in[i] <= 'F') {
				temp = in[i] - 'A' + 65;
			}
			else {
				temp = in[i] - '0'+48;
			}
		}
		if (temp / 128) {
			num[8 * j + 7] = 1;
		}
		if ((temp%128 )/ 64) {
			num[8 * j + 6] = 1;
		}
		if ((temp%64) / 32) {
			num[8 * j + 5] = 1;
		}
		if ((temp%32) / 16) {
			num[8 * j + 4] = 1;
		}
		if ((temp%16) / 8) {
			num[8 * j + 3] = 1;
		}
		if ((temp % 8) / 4) {
			num[8 * j + 2] = 1;
		}
		if ((temp % 4) / 2) {
			num[8 * j + 1] = 1;
		}
		if (temp % 2) {
			num[8 * j] = 1;
		}
		j++;
	}
	sign = 0;
}

// //���������������㷨�Ǹ�512bit��ÿһλ����ʱ������һ���������Ȼ��%2�������������������ʱ�䣬ʱ���ֺܽ��ƣ��������Ч�����ܲ�̫��
//void BigInte::GeneRandom(int n)
//{
//	BigInte temp;
//	srand((int)time(0));
//	for (int i = 0; i < n; i++)
//	{
//		int x = rand() % 2;         // ��ÿһλ�������������������->��λ��1����ż��->��λ��0
//		if (x == 1)
//			num[i] = 1;
//		else
//			num[i] = 0;
//	}
//	for (int i = max - 1; i >= n; i--)
//	{
//		num[i] = 0;
//	}
//	num[n - 1] = 1;     //��֤���λ��1 -> ��֤λ��
//	num[0] = 1;    //��֤���λ��1 -> ��֤������
//}

//��������ͬ���㷨���������
void BigInte::GeneRandom(int n)
{
	int wordnum = n / 32;
	BigInte m;
	for (int i = 0; i <= 30; i++)
		m.make(i, 1);     // m=2^31-1
	BigInte a(16807);     // a=16807
	srand((unsigned)time(NULL));
	BigInte X(rand());
	for (int i = 0; i <= wordnum-1; i++)
	{
		BigInte temp((a * X) / m);
		for (int j = 0; j <= 31; j++)
			num[i * 32 + j] = temp[j];
	}
	for (int i = max - 1; i >= n; i--)
		num[i] = 0;
	num[n - 1] = 1;
	num[0] = 1;
}

BigInte operator+(BigInte a, BigInte b)
{
	BigInte result;      // ������Ϊ����ֵ
	int i;           
	bool temp = 0;       // temp��ʾ��λ�Ƿ��λ       
	if (a.sign == b.sign) {
		for (i = 0; i < max; i++) {
			if (a[i] == 0 && b[i] == 0 && temp == 0) {
				result.make(i, 0);
				temp = 0;
			}
			else {
				if (a[i] == 1 && b[i] == 0 && temp == 0 ||
					a[i] == 0 && b[i] == 1 && temp == 0 ||
					a[i] == 0 && b[i] == 0 && temp == 1) {
					temp = 0;
					result.make(i, 1);
				}
				else {
					if (a[i] == 1 && b[i] == 1 && temp == 0 ||
						a[i] == 0 && b[i] == 1 && temp == 1 ||
						a[i] == 1 && b[i] == 0 && temp == 1) {
						temp = 1;        //��λΪ1
						result.make(i, 0);
					}
					else {
						if (a[i] == 1 && b[i] == 1 && temp == 1) {
							temp = 1;
							result.make(i, 1);
						}
					}
				}
			}
		}
		result.sign = a.sign;
	}
	if (a.sign == 0 && b.sign == 1) {
		b.Sign_Change();
		return a - b;
	}
	if (a.sign == 1 && b.sign == 0) {
		a.Sign_Change();
		return b - a;
	}
	if (temp)        //�������ǲ�����λ�Ļ���˵�����������������͵�λ�������
	{
		cout << "Overflow" << endl;
	}
	return result;
}

BigInte operator-(BigInte a, BigInte b)
{
	BigInte result;
	int i;
	bool temp = 0;      //��ʾ֮ǰ��λ�Ľ�λ
	if (a.sign == b.sign) {
		if (!(b.abs() > a.abs()))     //����û��д��b.abs()<=a.abs()����Ϊ����ֻʵ���ˣ���>����Ԫ����ʵ�֣�δʵ��<=�ı�д
		{
			for (i = 0; i < max; i++) {
				if (a[i] == 0 && b[i] == 0 && temp == 0 ||
					a[i] == 1 && b[i] == 0 && temp == 1 ||
					a[i] == 1 && b[i] == 1 && temp == 0) {
					result.make(i, 0);
					temp = 0;
				}
				else {
					if (a[i] == 0 && b[i] == 0 && temp == 1 ||
						a[i] == 0 && b[i] == 1 && temp == 0 ||
						a[i] == 1 && b[i] == 1 && temp == 1) {
						temp = 1;
						result.make(i, 1);
					}
					else {
						if (a[i] == 0 && b[i] == 1 && temp == 1) {
							temp = 1;
							result.make(i, 0);
						}
						else {
							if (a[i] == 1 && b[i] == 0 && temp == 0) {
								temp = 0;
								result.make(i, 1);
							}
						}
					}
				}
			}
			result.sign = a.sign;
		}
		else {
			result = (b - a);
			result.sign = !a.sign;
		}
	}
	if (a.sign == 0 && b.sign == 1) {
		b.Sign_Change();
		return a + b;
	}
	if (a.sign == 1 && b.sign == 0) {
		b.Sign_Change();
		return a + b;
	}
	if (temp) {
		cout << "Overflow" << endl;
	}
	return result;
}

BigInte operator*(BigInte a, BigInte b)
{
	// ���������ĳ˷��㷨�����ȿ�������λ�Ƿ�Ϊ1���ǵĻ����û����ϱ����������ǵĻ��Ͳ��ӣ�����ÿһ�ζ�Ҫ���б�������λ�����ƣ�����������2
	BigInte result;
	int i;
	for (i = 0; i < max; i++) {
		if (b[i] == 1) {
			result = result + a;
		}
		a.leftMove(1);
	}
	if (a.sign == b.sign) {
		result.sign = 0;
	}
	else {
		result.sign = 1;
	}
	return result;
}

BigInte operator/(BigInte a, BigInte b)
{
	BigInte result;      
	if (a.sign == b.sign) {
		result.sign = 0;
	}
	else {
		result.sign = 1;
	}
	int i, j;
	BigInte tempA = a, tempB = b, ZERO("0");
	if (ZERO > tempA) {
		tempA.Sign_Change();
	}
	if (ZERO > tempB) {
		tempB.Sign_Change();
	}
	for (j = max - 1; j >= 0; j--) {
		if (b[j]) {
			break;
		}
	}

	BigInte tempDiv = tempB;          // ѭ��������õ�����

	// �����㷨��һ�����صĳ����㷨�� ���ǰѳ����Ӵ���С���䣬�ͱ��������Ƚϡ�
	// �����������������λ3λ���aС��˵��a����b�ĵ���λӦ��Ҫ����1��
	for (i = max - j - 1; i >= 0; i--) {
		tempDiv = tempB;
		tempDiv.leftMove(i);
		if (!(tempDiv > tempA)) {
			result.make(i, 1);
			tempA = tempA - tempDiv;
		}
	}
	return result;
}

// �õ�����
BigInte operator%(BigInte a, BigInte b)
{
	BigInte result;
	result = a - (a / b) * b;    //������-����*ȡ���ĳ���=����
	return result;
}

// �Ƚϴ�С��
// ��������ʱ�� �ȴӷ���λ�ж��Ǹ��������϶����ڸ�����������Ҫע�⣬���������������ȫ0�Ļ�����������ȣ���Ϊû������0��
// ������ͬʱ�� �������Ӹ�λ����λ�ȣ�һ������a����1λ��b����1λС�Ļ�����ô�϶�a<b;   ����������������෴
// ���ʱ�����ص�JudgeBigҲ��false
bool operator>(BigInte a, BigInte b)
{
	bool JudgeBig = 0;
	int i;
	if (a.sign == 0 && b.sign == 1) {     //�������죬�ж��Ƿ���ȫ0
		JudgeBig = true;
		bool AllZero = true;      //�ж��Ƿ�ȫ0
		for (i = 0; i < max; i++) {
			if (a[i] != 0 || b[i] != 0) {
				AllZero = false;
			}
		}
		if (AllZero) {
			JudgeBig = false;
		}
	}
	else {
		if (a.sign == 1 && b.sign == 0) {     //�������죬�ж��Ƿ���ȫ0
			JudgeBig = false;
			bool AllZero = true;
			for (i = 0; i < max; i++) {
				if (a[i] != 0 || b[i] != 0) {
					AllZero = false;
				}
			}
			if (AllZero) {
				JudgeBig = false;
			}
		}
		else {
			if (a.sign == 0 && b.sign == 0) {    //������ͬ���Ҷ�Ϊ����
				for (i = max - 1; i >= 0; i--) {
					if (a[i] == 1 && b[i] == 0) {
						JudgeBig = true;
						break;
					}
					if (a[i] == 0 && b[i] == 1) {
						JudgeBig = false;
						break;
					}
				}
			}
			else {                             //������ͬ���Ҷ�Ϊ����
				for (i = max - 1; i >= 0; i--) {
					if (a[i] == 1 && b[i] == 0) {
						JudgeBig = false;
						break;
					}
					if (a[i] == 0 && b[i] == 1) {
						JudgeBig = true;
						break;
					}
				}
			}
		}
	}
	return JudgeBig;
}

// �ж��Ƿ���ȣ��Է���λ�Լ�ÿһλ��ֵλ���бȽϣ�����ȫ����Ȳ����ж�Ϊ���
bool operator==(BigInte a, BigInte b)
{
	int i;
	bool JudgeSame = true;
	if (a.sign != b.sign) {
		JudgeSame = false;
	}
	for (i = 0; i < max; i++) {
		if (a[i] != b[i]) {
			JudgeSame = false;
			break;
		}
	}
	return JudgeSame;
}

// �Է���λ�Լ�ÿһ����ֵλ���бȽϣ�һ����һ�����ã����ж�Ϊ����
bool operator!=(BigInte a, BigInte b)
{
	int i;
	if (a.sign != b.sign) {
		return true;
	}
	for (i = 0; i < max; i++) {
		if (a[i] != b[i]) {
			return true;
		}
	}
	return false;
}

// ͬ�����㣬ʵ�ֵ���a*b(mod c)
// �˷�ͬǰ��ֻ����ÿһ���Ĵ�����ȥ��c��Ĳ������ȡģ
BigInte BigInte::mod(BigInte a, BigInte b, BigInte c)
{
	BigInte result;
	int i;
	for (i = 0; i < max; i++) {
		if (b[i] == 1) {
			result = result + a;
			while (result > c)
				result = result - c;
		}
		a.leftMove(1);
		while (a > c)
			a = a - c;
	}
	if (a.sign == b.sign) {
		result.sign = 0;
	}
	else {
		result.sign = 1;
	}
	return result;
}

// ��ָ���󣬵õ���y��ģ������ result=��*this��^x (mod y)
BigInte BigInte::exp(BigInte x, BigInte y)
{
	BigInte result("1");
	int i = max - 1;
	while (!x[i]) {
		i--;
	}           //�õ�x�����λ
	int j;
	for (j = i; j >= 0; j--) {
		result = mod(result, result, y);
		if (x[j]) {
			result = mod(result, (*this), y);
		}
	}
	return result;
}



// ��x��y����Ԫ����result*x=1(mod y)
BigInte BigInte::inv(BigInte x)
{
	BigInte ZERO("0"), ONE("1");
	BigInte x1 = ONE, x2 = ZERO, x3 = x;
	BigInte y1 = ZERO, y2 = ONE, y3 = (*this);
	BigInte t1, t2, t3;
	if (y3 == ONE) {
		return ONE;
	}
	BigInte q;
	BigInte g;
	do {
		q = x3 / y3;
		t1 = x1 - q * y1;
		t2 = x2 - q * y2;
		t3 = x3 - q * y3;
		x1 = y1;
		x2 = y2;
		x3 = y3;
		y1 = t1;
		y2 = t2;
		y3 = t3;
	} while (!(y3 == ONE));
	g = y2;
	if (!(g > ZERO))
		g = x + g;
	return g;
}

// ���Ʋ������������ʾ�Ķ��������ģ�������Ĳ���Ϊ��λλ��
void BigInte::leftMove(int i)
{
	int k;
	for (k = max - 1; k > i - 1; k--) {
		num[k] = num[k - i];
	}
	for (k = 0; k < i; k++) {
		num[k] = 0;
	}
}

// ���ڶ����������±�����
bool BigInte::operator[](int i)
{
	return num[i];
}

// ���ڶ���������λ����λ������Ĳ�������Ϊ��λ�ã�ֵ��0/1��
void BigInte::make(int i, bool a)
{
	num[i] = a;
}

// ����ʮ�����Ƶ���ʽ����ö�������
void BigInte::out()
{
	if (this->sign == 1) {
		cout << '-';
	}
	char result[max];
	int i;
	for (i = max - 1; i >= 0; i--) {
		if ((*this)[i] == 1) {
			break;
		}
	} //�õ��ö������������λ
	i++;
	int k;
	int length = 0;
	// �Ѷ���������λ�����ȱ��4�������������������ʮ���������
	switch (i % 4) {
	case 1:
		length = i + 3;
		break;
	case 2:
		length = i + 2;
		break;
	case 3:
		length = i + 1;
		break;
	case 0:
		length = i;
		break;
	}
	for (k = 0; k < length; k = k + 4) {
		if ((*this)[k] == 0 && (*this)[k + 1] == 0 && (*this)[k + 2] == 0 && (*this)[k + 3] == 0) {
			result[k / 4] = '0';
		}
		if ((*this)[k] == 1 && (*this)[k + 1] == 0 && (*this)[k + 2] == 0 && (*this)[k + 3] == 0) {
			result[k / 4] = '1';
		}
		if ((*this)[k] == 0 && (*this)[k + 1] == 1 && (*this)[k + 2] == 0 && (*this)[k + 3] == 0) {
			result[k / 4] = '2';
		}
		if ((*this)[k] == 1 && (*this)[k + 1] == 1 && (*this)[k + 2] == 0 && (*this)[k + 3] == 0) {
			result[k / 4] = '3';
		}
		if ((*this)[k] == 0 && (*this)[k + 1] == 0 && (*this)[k + 2] == 1 && (*this)[k + 3] == 0) {
			result[k / 4] = '4';
		}
		if ((*this)[k] == 1 && (*this)[k + 1] == 0 && (*this)[k + 2] == 1 && (*this)[k + 3] == 0) {
			result[k / 4] = '5';
		}
		if ((*this)[k] == 0 && (*this)[k + 1] == 1 && (*this)[k + 2] == 1 && (*this)[k + 3] == 0) {
			result[k / 4] = '6';
		}
		if ((*this)[k] == 1 && (*this)[k + 1] == 1 && (*this)[k + 2] == 1 && (*this)[k + 3] == 0) {
			result[k / 4] = '7';
		}
		if ((*this)[k] == 0 && (*this)[k + 1] == 0 && (*this)[k + 2] == 0 && (*this)[k + 3] == 1) {
			result[k / 4] = '8';
		}
		if ((*this)[k] == 1 && (*this)[k + 1] == 0 && (*this)[k + 2] == 0 && (*this)[k + 3] == 1) {
			result[k / 4] = '9';
		}
		if ((*this)[k] == 0 && (*this)[k + 1] == 1 && (*this)[k + 2] == 0 && (*this)[k + 3] == 1) {
			result[k / 4] = 'A';
		}
		if ((*this)[k] == 1 && (*this)[k + 1] == 1 && (*this)[k + 2] == 0 && (*this)[k + 3] == 1) {
			result[k / 4] = 'B';
		}
		if ((*this)[k] == 0 && (*this)[k + 1] == 0 && (*this)[k + 2] == 1 && (*this)[k + 3] == 1) {
			result[k / 4] = 'C';
		}
		if ((*this)[k] == 1 && (*this)[k + 1] == 0 && (*this)[k + 2] == 1 && (*this)[k + 3] == 1) {
			result[k / 4] = 'D';
		}
		if ((*this)[k] == 0 && (*this)[k + 1] == 1 && (*this)[k + 2] == 1 && (*this)[k + 3] == 1) {
			result[k / 4] = 'E';
		}
		if ((*this)[k] == 1 && (*this)[k + 1] == 1 && (*this)[k + 2] == 1 && (*this)[k + 3] == 1) {
			result[k / 4] = 'F';
		}
	}
	if (i == 0) {
		cout << '0' << endl;
	}
	else {
		for (i = (k / 4) - 1; i >= 0; i--) {
			cout << result[i];
		}
		cout << endl;
	}
}


// ����ȡ��
void BigInte::Sign_Change()
{
	this->sign = !(this->sign);
}

// ȡ����ֵ����������������򷵻���������Ǹ�������ȡ���󷵻�
BigInte BigInte::abs()
{
	BigInte temp = (*this);
	if (temp.sign == 0) {
		return temp;
	}
	else {
		temp.Sign_Change();
		return temp;
	}
}

