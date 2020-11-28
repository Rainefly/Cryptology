//#include<iostream>
//#include<string>
//#include<map>
//#include<iomanip>
//#include<vector>
//#include<algorithm>
//
//using namespace std;
//
////这个程序实现的是单个字符频率统计和出现的单词频率统计；按照从大到小的顺序输出。
////这个是针对单表置换密码的词频攻击的前期代码，只能统计频率，具体应该怎样匹配置换，这个需要人工根据自然语言特性去比对。
//
//map<char, double> charactermap;
//map<string, double> wordmap;
//
//typedef pair<char, double> PAIR;
//bool cmp_by_value(const PAIR& lhs, const PAIR& rhs)
//{
//	return lhs.second > rhs.second;     //从大到小排序
//}
//
//typedef pair<string, double> PAIR2;
//bool cmp_by_value2(const PAIR2& lhs, const PAIR2& rhs)
//{
//	return lhs.second > rhs.second;     //从大到小排序
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
//	//按从大到小的顺序输出
//	vector<PAIR> mycharvec(charactermap.begin(), charactermap.end());
//	sort(mycharvec.begin(), mycharvec.end(), cmp_by_value);
//
//	for (int i = 0; i < mycharvec.size(); i++)
//	{
//		cout << mycharvec[i].first << ": " << mycharvec[i].second/charactercount << endl;
//	}
//
//	//按原序输出
//	//map<char, double>::iterator iter1;
//	//for (iter1 = charactermap.begin(); iter1 != charactermap.end(); iter1++)
//	//{
//	//	cout << iter1->first << ": " << iter1->second/charactercount  << endl;
//	//}
//
//	cout << endl << "the word frequency is: " << endl;
//	//按从大到小的顺序输出
//	vector<PAIR2> mywordvec(wordmap.begin(), wordmap.end());
//	sort(mywordvec.begin(), mywordvec.end(), cmp_by_value2);
//
//	for (int i = 0; i < mywordvec.size(); i++)
//	{
//		cout << setw(20)<<mywordvec[i].first << ": " << setw(20)<<mywordvec[i].second/wordcount << endl;
//	}
//
//	////按原序输出
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