//#include<iostream>
//#include<string>
//#include<map>
//#include<iomanip>
//#include<vector>
//#include<algorithm>
//
//using namespace std;
//
////�������ʵ�ֵ��ǵ����ַ�Ƶ��ͳ�ƺͳ��ֵĵ���Ƶ��ͳ�ƣ����մӴ�С��˳�������
////�������Ե����û�����Ĵ�Ƶ������ǰ�ڴ��룬ֻ��ͳ��Ƶ�ʣ�����Ӧ������ƥ���û��������Ҫ�˹�������Ȼ��������ȥ�ȶԡ�
//
//map<char, double> charactermap;
//map<string, double> wordmap;
//
//typedef pair<char, double> PAIR;
//bool cmp_by_value(const PAIR& lhs, const PAIR& rhs)
//{
//	return lhs.second > rhs.second;     //�Ӵ�С����
//}
//
//typedef pair<string, double> PAIR2;
//bool cmp_by_value2(const PAIR2& lhs, const PAIR2& rhs)
//{
//	return lhs.second > rhs.second;     //�Ӵ�С����
//}
//
//void initial()
//{
//	for (int i = 0; i <= 25; i++)
//	{
//		charactermap[('a' + i)] = 0;
//	}
//}
//
//void frequency_count(string str)
//{
//	int length = str.length();
//	int charactercount = 0;
//	int wordcount = 0;
//	string temp;
//	temp = { 0 };
//	for (int i = 0; i <= length - 1; i++)
//	{
//		if (str[i] >= 'A' && str[i] <= 'Z')
//			str[i] += 32;
//		if (str[i] >= 'a' && str[i] <= 'z')
//		{
//			charactermap[str[i]]++;
//			charactercount++;
//			temp += str[i];
//		}
//		if (str[i] == ' ')
//		{
//			int flag = 0;
//			map<string, double>::iterator worditer;
//			for (worditer = wordmap.begin(); worditer != wordmap.end(); worditer++)
//			{
//				if (worditer->first == temp)
//				{
//					flag = 1;
//					break;
//				}
//			}
//			if (flag == 1)
//				wordmap[temp]++;
//			else
//				wordmap[temp] = 1;
//			wordcount++;
//			temp = { 0 };
//		}
//	}
//
//	cout << " the character frequency is: " << endl;
//	//���Ӵ�С��˳�����
//	vector<PAIR> mycharvec(charactermap.begin(), charactermap.end());
//	sort(mycharvec.begin(), mycharvec.end(), cmp_by_value);
//
//	for (int i = 0; i < mycharvec.size(); i++)
//	{
//		cout << mycharvec[i].first << ": " << mycharvec[i].second/charactercount << endl;
//	}
//
//	//��ԭ�����
//	//map<char, double>::iterator iter1;
//	//for (iter1 = charactermap.begin(); iter1 != charactermap.end(); iter1++)
//	//{
//	//	cout << iter1->first << ": " << iter1->second/charactercount  << endl;
//	//}
//
//	cout << endl << "the word frequency is: " << endl;
//	//���Ӵ�С��˳�����
//	vector<PAIR2> mywordvec(wordmap.begin(), wordmap.end());
//	sort(mywordvec.begin(), mywordvec.end(), cmp_by_value2);
//
//	for (int i = 0; i < mywordvec.size(); i++)
//	{
//		cout << setw(20)<<mywordvec[i].first << ": " << setw(20)<<mywordvec[i].second/wordcount << endl;
//	}
//
//	////��ԭ�����
//	//map<string, double>::iterator worditer;
//	//for (worditer = wordmap.begin(); worditer != wordmap.end(); worditer++)
//	//{
//	//	cout << setw(20)<<worditer->first << ": " <<setw(20)<< worditer->second / wordcount << endl;
//	//}
//
//}
//
//int main()
//{
//	cout << "Please enter your string: " << endl;
//	string mystring;
//	getline(cin, mystring);
//	initial();
//	frequency_count(mystring);
//	system("pause");
//	return 0;
//}