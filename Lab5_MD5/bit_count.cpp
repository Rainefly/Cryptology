//
//#include<iostream>
//using namespace std;
//
//
//// 本程序用于统计雪崩效应 （和输入是"BBBBBBBB"的进行比较）
//int main()
//{
//	char temp[129] = "10010110001000011110110111111001101011100000011000001011100000101011000010101001000010110000100110010101111000011010111100101000";
//	char myin[129] = { 0 };
//	int count = 0;
//	while (true)
//	{
//		cout << "next" << endl;
//		cin >> myin;
//		for (int i = 0; i <= 127; i++)
//		{
//			if (temp[i] != myin[i])
//				count++;
//		}
//		cout << "count is : " << count << endl;
//		count = 0;
//		*myin = { 0 };
//	}
//}