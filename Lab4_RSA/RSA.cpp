#pragma once
#include <iostream>
#include<fstream>
#include <string>
#include<stdlib.h>
#include"BigInt.h"
using namespace std;

// Miller-Rabbin
bool isPrime(BigInte a)
{
	BigInte temp = a;
	BigInte n = a;
	n.make(0, 0);    //n=n-1
	ifstream infile("prime10w.txt");
	int prime;
	const BigInte ONE(1);
	int mark = 511;
	for (int i = 0; i < 5; i++)
	{
		int find = (int(rand()) % 9592);     //10万以内的素数为9592个
		infile.seekg(find, ios::beg);
		infile >> prime;
		BigInte pNum(prime);
		BigInte d(1);
		BigInte x;
		for (int j = mark; j > -1; j--)
		{
			x = d;
			d = (d * d) % temp;
			if ((d == ONE) && (x != ONE) && (x != n))
				return false;
			if (n[j] == true)
				d = (d * pNum) % temp;
		}
		if (d != ONE)
			return false;
	}
	infile.close();
	return true;
}


class RSA
{
private:
	BigInte p, q, phi,d;   //p和q是两个保密的大素数；phi是n的欧拉函数值；d是e的逆元，作为密钥元素之一；
public:
	BigInte e, n;         //e是选择的和n互素的数，是公开钥
	BigInte m, c;         //m为每个明文分组的明文，c是明文加密后的结果，即密文
	RSA(BigInte a, BigInte b)
	{
		BigInte one("1");
		p = a;
		q = b;
		n = p * q;
		phi = (p - one) * (q - one);
		BigInte curr("10001");    //自己选取的和phi互素的数
		e = curr;
		d = e.inv(phi);
	}

	// 加密函数
	void encode(BigInte m1)
	{
		m = m1;
		c = m.exp(e, n);
	}

	//解密函数
	void decode(BigInte c1)
	{
		c = c1;
		m = c.exp(d, n);
	}

	// 针对加密解密操作，输出不同的信息
	void show(int i)
	{
		//1的话，输出解密操作的对应信息
		if (i == 1) {
			cout << "公钥n(hex)：" << endl;
			n.out();
			cout << "私钥d(hex)：" << endl;
			d.out();
			cout << "公钥e(hex)：" << endl;
			e.out();
			cout << "明文(hex)：" << endl;
			//c.out(1);
			m.out();
		}
		else {   //0的话，输出加密操作的对应信息
			cout << "公钥n(hex)：" << endl;
			n.out();
			cout << "私钥d(hex)：" << endl;
			d.out();
			cout << "公钥e(hex)：" << endl;
			e.out();
			cout << "密文(hex)：" << endl;
			c.out();
		}
	}
};
int main()
{
	cout << "0:Exit       1:Encode       2:Decode       3:GetPrime" << endl;
	cout << "please input the number shown above as your choice : " << endl;
	int i; 
	cin >> i;
	while (i != 0)
	{
		cin.get();
		if (i == 1) {
			cout << "请输入大素数p：" << endl;
			string p;
			getline(cin, p);
			cout << "请输入大素数q：" << endl;
			string q;
			getline(cin, q);
			cout << "请输入明文(hex)：" << endl;
			string sm;
			cin >> sm;
			BigInte m(sm, 1);
			m.out();
			RSA rsa(p, q);
			rsa.encode(m);
			rsa.show(0);
		}
		if (i == 2) {
			cout << "请输入大素数p：" << endl;
			string p;
			getline(cin, p);
			cout << "请输入大素数q：" << endl;
			string q;
			getline(cin, q);
			cout << "请输入密文(hex)：" << endl;
			string c;
			getline(cin, c);
			RSA rsa(p, q);
			rsa.decode(c);
			rsa.show(1);
		}
		if (i == 3) {
			cout << "开始生成：" << endl;
			int primeNum[303];    //2000以内的素数有303个
			//以下是 Miller-Rabbin算法，把一个输入的随机数和2000以内的素数进行互素判断。
			ifstream infile("Prime2k.txt");
			int k = 0;
			while (infile >> primeNum[k])
				k++;
			BigInte temp;
			int count = 0;
			bool re = true;
			BigInte TWO("2");
			int cur;
			while (true) 
			{
				if (re) 
				{
					temp.GeneRandom(512);   //生成512位的随机数
					re = false;
				}
				//如果不是素数，则把这个数+2，然后再次投入算法进行运算
				temp = temp + TWO;
				temp.out();
				//对这个数进行2000以内素数互素的判断
				for (cur = 0; cur < 303; cur++)
				{
					if ((temp % primeNum[cur]) == 0)
						break;
				}
				if (cur == 303 && isPrime(temp)) {
					cout << "是素数！" << endl;
					count++;
					re = true;
				}
				if (count == 2)
					break;
			}
		}
		cout << "请输入0-3：" << endl;
		cin >> i;
	}
}
