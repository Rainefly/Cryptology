#include<iostream>
#include<math.h>
#include<string>
#include<time.h>
#include<stdlib.h>
#include<fstream>

#include"BigInt.h"     // 自定义大整数的类
using namespace std;


BigInte::BigInte()         // 全部归零
{
	int i;
	for (i = 0; i < max; i++)
	{
		num[i] = 0;
	}
	sign = 0;
}

BigInte::BigInte(int in)       // 十进制转成二进制存储（右边为最低位）
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

BigInte::BigInte(string in)        // 十六进制转二进制存储（右边为最低位）
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

BigInte::BigInte(string in,int a)        // 十六进制转二进制存储（右边为最低位）
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

// //这个生成随机数的算法是给512bit的每一位都按时间生成一个随机数，然后%2；但是随机数生成依赖时间，时间又很近似，所以随机效果可能不太好
//void BigInte::GeneRandom(int n)
//{
//	BigInte temp;
//	srand((int)time(0));
//	for (int i = 0; i < n; i++)
//	{
//		int x = rand() % 2;         // 对每一位都生成随机数，是奇数->该位置1；是偶数->该位置0
//		if (x == 1)
//			num[i] = 1;
//		else
//			num[i] = 0;
//	}
//	for (int i = max - 1; i >= n; i--)
//	{
//		num[i] = 0;
//	}
//	num[n - 1] = 1;     //保证最高位是1 -> 保证位数
//	num[0] = 1;    //保证最低位是1 -> 保证是奇数
//}

//按照线性同余算法生成随机数
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
	BigInte result;      // 用于作为返回值
	int i;           
	bool temp = 0;       // temp表示低位是否进位       
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
						temp = 1;        //进位为1
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
	if (temp)        //如果最后还是产生进位的话，说明两个数加起来最后和的位数变多了
	{
		cout << "Overflow" << endl;
	}
	return result;
}

BigInte operator-(BigInte a, BigInte b)
{
	BigInte result;
	int i;
	bool temp = 0;      //表示之前低位的借位
	if (a.sign == b.sign) {
		if (!(b.abs() > a.abs()))     //这里没有写成b.abs()<=a.abs()是因为下面只实现了！和>的友元函数实现，未实现<=的编写
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
	// 二进制数的乘法算法就是先看乘数该位是否为1，是的话就让积加上被乘数，不是的话就不加；而后每一次都要进行被乘数的位数左移，即被乘数×2
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

	BigInte tempDiv = tempB;          // 循环遍历后得到除数

	// 以下算法是一个朴素的除法算法， 就是把除数从大往小扩充，和被除数作比较。
	// 例：如果扩充了左移位3位后比a小，说明a除以b的第三位应该要被置1；
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

// 得到余数
BigInte operator%(BigInte a, BigInte b)
{
	BigInte result;
	result = a - (a / b) * b;    //被除数-除数*取整的除数=余数
	return result;
}

// 比较大小：
// 符号相异时： 先从符号位判断那个大：正数肯定大于负数；（但是要注意，如果正负数，但是全0的话，则两数相等，因为没有正负0）
// 符号相同时： 正数：从高位到低位比，一旦出现a的那1位比b的那1位小的话，那么肯定a<b;   负数：与正数情况相反
// 相等时，返回的JudgeBig也是false
bool operator>(BigInte a, BigInte b)
{
	bool JudgeBig = 0;
	int i;
	if (a.sign == 0 && b.sign == 1) {     //符号相异，判断是否有全0
		JudgeBig = true;
		bool AllZero = true;      //判断是否全0
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
		if (a.sign == 1 && b.sign == 0) {     //符号相异，判断是否有全0
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
			if (a.sign == 0 && b.sign == 0) {    //符号相同，且都为正数
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
			else {                             //符号相同，且都为负数
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

// 判断是否相等：对符号位以及每一位数值位进行比较，必须全部相等才能判断为相等
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

// 对符号位以及每一个数值位进行比较，一旦有一个不用，则判断为相异
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

// 同余运算，实现的是a*b(mod c)
// 乘法同前，只是在每一步的处理后减去比c大的部分完成取模
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

// 乘指数后，得到对y的模数，即 result=（*this）^x (mod y)
BigInte BigInte::exp(BigInte x, BigInte y)
{
	BigInte result("1");
	int i = max - 1;
	while (!x[i]) {
		i--;
	}           //得到x的最高位
	int j;
	for (j = i; j >= 0; j--) {
		result = mod(result, result, y);
		if (x[j]) {
			result = mod(result, (*this), y);
		}
	}
	return result;
}



// 求x对y的逆元，即result*x=1(mod y)
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

// 左移操作（相对所表示的二进制数的），传入的参数为移位位数
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

// 对于二进制数的下标索引
bool BigInte::operator[](int i)
{
	return num[i];
}

// 对于二进制数的位数置位，传入的参数依次为：位置，值（0/1）
void BigInte::make(int i, bool a)
{
	num[i] = a;
}

// 按照十六进制的形式输出该二进制数
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
	} //得到该二进制数的最高位
	i++;
	int k;
	int length = 0;
	// 把二进制数的位数长度变成4的整数倍，便于下面的十六进制输出
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


// 符号取反
void BigInte::Sign_Change()
{
	this->sign = !(this->sign);
}

// 取绝对值：即如果是正数，则返回自身；如果是负数，则取反后返回
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

