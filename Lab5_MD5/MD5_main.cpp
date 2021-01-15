#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <string>
#include <stdio.h>
#include<stdlib.h>
#include "MD5.h"
#include<fstream>

using namespace std;

int main(int argc, char* argv[])
{
	cout << "----------------------  MD5 Test  ----------------------" << endl;
	while (true)
	{
		int t;
		cout << "input 1 to encode or 0 to exit :  ";
		cin >> t;
		cout << endl;
		if (t == 1)
		{
			MD5 md5;
			MD5Init(&md5);
			int i;
			unsigned char encrypt[100];
			cout << "Input the message : " << endl;
			cin.ignore();
			cin.getline((char*)encrypt, 100);      // 可读入空格和回车
			unsigned char decrypt[16];
			MD5Packet_Refresh(&md5, encrypt, strlen((char*)encrypt));
			MD5Trans(&md5, decrypt);
			cout << "The MD5 digest is:" << endl;
			char hexstr[33];

			// 以十六进制形式输出
			for (i = 0; i < 16; i++)
			{
				sprintf(&hexstr[i * 2], "%02x", decrypt[i]);
			}
			for (int i = 0; i < 31; i += 2)
			{
				cout << "0x" << hexstr[i] << hexstr[i + 1] << " ";
				if (i == 14)
				{
					cout << endl;
				}
			}
			cout << endl;

			// 以下用于输出的程序检查

			cout << "The code in bin is: ";
			for (int i = 0; i < 32; i++)
			{
				//if (i % 8 == 0)
				//{
				//	cout << endl;
				//}
				//else
				//	cout << " ";
				switch (hexstr[i])
				{
				case '0':
					cout << "0000";
					break;
				case '1':
					cout << "0001";
					break;
				case '2':
					cout << "0010";
					break;
				case '3':
					cout << "0011";
					break;
				case '4':
					cout << "0100";
					break;
				case '5':
					cout << "0101";
					break;
				case '6':
					cout << "0110";
					break;
				case '7':
					cout << "0111";
					break;
				case '8':
					cout << "1000";
					break;
				case '9':
					cout << "1001";
					break;
				case 'a':
					cout << "1010";
					break;
				case 'b':
					cout << "1011";
					break;
				case 'c':
					cout << "1100";
					break;
				case 'd':
					cout << "1101";
					break;
				case 'e':
					cout << "1110";
					break;
				case 'f':
					cout << "1111";
					break;
				}
			}
		}
		if (t == 0)
		{
			cout << endl << "The program is going to close ... " << endl;
			break;
		}
		cout << endl;
	}
	system("Pause");
	return 0;
}
