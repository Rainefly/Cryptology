//#include<iostream>
//#include<string.h>
//#include<bitset>
//
//using namespace std;
//
//bitset<64> charToBit(const char input[8])
//{
//	bitset<64> bits;
//	for (int i = 0; i < 8; ++i)
//		for (int j = 0; j < 8; ++j)
//			bits[64 - i * 8 - j] = ((input[i] >> j) & 1);
//	for (int i = 0; i <= 63; i++)
//		cout << bits[63-i];
//	cout << endl;
//	return bits;
//}
//
//bitset<64> hextoBit(char* input)
//{
//	bitset<64> bits;
//	string temp = { 0 };
//	int length = strlen(input);
//	for (int i = 0; i <=length-1; i++)
//	{
//		char e = input[i];
//		if (e >= 'A' && e <= 'F')
//		{
//			int a = int(e - 'A' + 10);
//			//cout << a;
//			switch (a)
//			{
//			case 10:temp = "1010"; cout << "1010"; break;
//			case 11:temp = "1011"; cout << "1011"; break;
//			case 12:temp = "1100"; cout << "1100"; break;
//			case 13:temp = "1101"; cout << "1101"; break;
//			case 14:temp = "1110"; cout << "1110"; break;
//			case 15:temp = "1111"; cout << "1111"; break;
//			}
//		}
//		else if (isdigit(e))
//		{
//			int b = int(e - '0');
//			switch (b)
//			{
//			case 0:temp = "0000"; cout << "0000"; break;
//			case 1:temp = "0001"; cout << "0001"; break;
//			case 2:temp = "0010"; cout << "0010"; break;
//			case 3:temp = "0011"; cout << "0011"; break;
//			case 4:temp = "0100"; cout << "0100"; break;
//			case 5:temp = "0101"; cout << "0101"; break;
//			case 6:temp = "0110"; cout << "0110"; break;
//			case 7:temp = "0111"; cout << "0111"; break;
//			case 8:temp = "1000"; cout << "1000"; break;
//			case 9:temp = "1001"; cout << "1001"; break;
//			}
//		}
//		bitset<4> bittemp(temp);
//		for (int j = 0; j <= 3; j++)
//			bits[ i * 4 + j] = bittemp[j];
//		temp = { 0 };
//	}
//	cout << endl << endl;
//	for (int i = 0; i <= 63; i++)
//		cout << bits[63 - i];
//	cout << endl;
//	return bits;
//}
//
//bitset<64> decToBin(const int in[8])
//{
//	//0xA5 = 1010(a) 0101(5)
//	bitset<64> out;
//	for (int i = 0; i < 8; i++)
//	{
//		//高位和低位
//		int high = in[i] / 16;
//		int low = in[i] % 16;
//		for (int j = 0; j < 4; j++)
//		{
//			out[8 * i + 7 - j] = low % 2;
//			out[8 * i + 3 - j] = high % 2;
//			low /= 2;
//			high /= 2;
//		}
//	}
//	for (int i = 0; i <= 63; i++)
//		cout << out[i];
//	cout << endl;
//	return out;
//}
//
//int* binToDec(bitset<64> in)
//{
//	//0xA5 = 1010(a) 0101(5)
//	int out[8];
//	for (int i = 0; i < 8; i++)
//	{
//		out[i] = 16 * (in[8 * i] * 8 + in[8 * i + 1] * 4 + in[8 * i + 2] * 2 + in[8 * i + 3]) + (in[8 * i + 4] * 8 + in[8 * i + 5] * 4 + in[8 * i + 6] * 2 + in[8 * i + 7]);
//	}
//	for (int i = 0; i <= 7; i++)
//		cout<<out[i]<<" ";
//	return out;
//}
//
//int main()
//{
//	cout << "please test1 : " << endl;
//	int in[8];
//	int* test;
//	bitset<64> out;
//	for (int i = 0; i <= 7; i++)
//		cin >> (hex)>>in[i];
//	out=decToBin(in);
//	test = binToDec(out);
//	//cout << input;
//	system("pause");
//	return 0;
//}
