//#include<iostream>
//#include<string>
//using namespace std;
//
//
////该函数完成从十六进制到二进制的转化，并且和基准序列进行比较，得到不同的位数进行输出。
//int main()
//{
//	char buffer[33] = { 0 };
//	//明文和密钥都是0的密文：
//	string original = "0110011011101001010010111101010011101111100010100010110000111011100010000100110011111010010110011100101000110100001010110010";
//	string model;
//	cin >> buffer;
//	cout << "The result is: " << endl;
//	for (int i = 0; i < 31; i++)
//	{
//		switch (buffer[i])
//		{
//		case'0':cout << "0000"; model += "0000"; break;
//		case'1':cout << "0001"; model += "0001"; break;
//		case'2':cout << "0010"; model += "0010"; break;
//		case'3':cout << "0011"; model += "0011"; break;
//		case'4':cout << "0100"; model += "0100"; break;
//		case'5':cout << "0101"; model += "0101"; break;
//		case'6':cout << "0110"; model += "0110"; break;
//		case'7':cout << "0111"; model += "0111"; break;
//		case'8':cout << "1000"; model += "1000"; break;
//		case'9':cout << "1001"; model += "1001"; break;
//		case'a':cout << "1010"; model += "1010"; break;
//		case'b':cout << "1011"; model += "1011"; break;
//		case'c':cout << "1100"; model += "1100"; break;
//		case'd':cout << "1101"; model += "1101"; break;
//		case'e':cout << "1110"; model += "1110"; break;
//		case'f':cout << "1111"; model += "1111"; break;
//		}
//	}
//	cout << endl;
//
//	int count = 0;
//	for (int i = 0; i <= 127; i++)
//		if (model[i] != original[i])
//			count++;
//	cout << "The different bit count is: " << count << endl;
//	system("pause");
//	return 0;
//}
//
////明文和密钥全0时的密文：
////66e94bd4ef8a2c3b884cfa59ca342b2e
