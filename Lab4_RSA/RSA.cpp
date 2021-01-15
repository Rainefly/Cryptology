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
		int find = (int(rand()) % 9592);     //10�����ڵ�����Ϊ9592��
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
	BigInte p, q, phi,d;   //p��q���������ܵĴ�������phi��n��ŷ������ֵ��d��e����Ԫ����Ϊ��ԿԪ��֮һ��
public:
	BigInte e, n;         //e��ѡ��ĺ�n���ص������ǹ���Կ
	BigInte m, c;         //mΪÿ�����ķ�������ģ�c�����ļ��ܺ�Ľ����������
	RSA(BigInte a, BigInte b)
	{
		BigInte one("1");
		p = a;
		q = b;
		n = p * q;
		phi = (p - one) * (q - one);
		BigInte curr("10001");    //�Լ�ѡȡ�ĺ�phi���ص���
		e = curr;
		d = e.inv(phi);
	}

	// ���ܺ���
	void encode(BigInte m1)
	{
		m = m1;
		c = m.exp(e, n);
	}

	//���ܺ���
	void decode(BigInte c1)
	{
		c = c1;
		m = c.exp(d, n);
	}

	// ��Լ��ܽ��ܲ����������ͬ����Ϣ
	void show(int i)
	{
		//1�Ļ���������ܲ����Ķ�Ӧ��Ϣ
		if (i == 1) {
			cout << "��Կn(hex)��" << endl;
			n.out();
			cout << "˽Կd(hex)��" << endl;
			d.out();
			cout << "��Կe(hex)��" << endl;
			e.out();
			cout << "����(hex)��" << endl;
			//c.out(1);
			m.out();
		}
		else {   //0�Ļ���������ܲ����Ķ�Ӧ��Ϣ
			cout << "��Կn(hex)��" << endl;
			n.out();
			cout << "˽Կd(hex)��" << endl;
			d.out();
			cout << "��Կe(hex)��" << endl;
			e.out();
			cout << "����(hex)��" << endl;
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
			cout << "�����������p��" << endl;
			string p;
			getline(cin, p);
			cout << "�����������q��" << endl;
			string q;
			getline(cin, q);
			cout << "����������(hex)��" << endl;
			string sm;
			cin >> sm;
			BigInte m(sm, 1);
			m.out();
			RSA rsa(p, q);
			rsa.encode(m);
			rsa.show(0);
		}
		if (i == 2) {
			cout << "�����������p��" << endl;
			string p;
			getline(cin, p);
			cout << "�����������q��" << endl;
			string q;
			getline(cin, q);
			cout << "����������(hex)��" << endl;
			string c;
			getline(cin, c);
			RSA rsa(p, q);
			rsa.decode(c);
			rsa.show(1);
		}
		if (i == 3) {
			cout << "��ʼ���ɣ�" << endl;
			int primeNum[303];    //2000���ڵ�������303��
			//������ Miller-Rabbin�㷨����һ��������������2000���ڵ��������л����жϡ�
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
					temp.GeneRandom(512);   //����512λ�������
					re = false;
				}
				//���������������������+2��Ȼ���ٴ�Ͷ���㷨��������
				temp = temp + TWO;
				temp.out();
				//�����������2000�����������ص��ж�
				for (cur = 0; cur < 303; cur++)
				{
					if ((temp % primeNum[cur]) == 0)
						break;
				}
				if (cur == 303 && isPrime(temp)) {
					cout << "��������" << endl;
					count++;
					re = true;
				}
				if (count == 2)
					break;
			}
		}
		cout << "������0-3��" << endl;
		cin >> i;
	}
}
