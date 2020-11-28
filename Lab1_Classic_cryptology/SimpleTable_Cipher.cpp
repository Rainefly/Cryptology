#include<iostream>
#include<cstdio>
#include<string>
#include<map>

//�������ʵ�ֵ��ǵ����û����롣
using namespace std;

map<char,bool> LetterUse;     //��������Ǹ�Ӣ����ĸ֮ǰ�Ƿ��ѱ���ӵ��û������δ��ӣ���boolֵΪ1������Ժ�boolֵΪ0
char mappingTable[26][2];

void initial()
{
	for (int i = 0; i <= 25; i++)
	{
		mappingTable[i][0] = 97 + i;
		mappingTable[i][1] = '\0';
		LetterUse[mappingTable[i][0]] = 1;
	}
}

//ʹ��һ���������ӣ�ɾȥ���е��ظ����֣���Ϊ�û����ǰ��Ĳ��֣�Ȼ���û���õ�����ĸ����ĸ���˳�����η����û����С�
void setTable(string str)
{
	int length = str.length();
	int mappingnum = 0;
	
	for (int i = 0; i <= length - 1; i++)
	{
		bool exist = false;
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
		if (str[i] < 'a' || str[i] > 'z')
			continue;

		for (int j = 0; j <= mappingnum - 1; j++)
		{
			if (mappingTable[j][1] == str[i])
				exist = true;
		}
		if (!exist)
		{
			mappingTable[mappingnum][1] = str[i];
			mappingnum++;
			LetterUse[str[i]] = 0;
		}
	}
	map<char,bool>::iterator iter;
	for (iter = LetterUse.begin(); iter != LetterUse.end(); iter++)
	{
		if (iter->second == 1)
		{
			mappingTable[mappingnum][1] = iter->first;
			iter->second = 0;
			mappingnum++;
		}
	}

	for (int i = 0; i <= 25; i++)
		cout << mappingTable[i][0]<<" ";
	cout << endl;
	for (int i = 0; i <= 25; i++)
		cout << mappingTable[i][1]<<" ";
	cout << endl;

}

void Enc(string str)
{
	int length = str.length();
	string result;
	int flag = 0;
	for (int i = 0; i <= length - 1; i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
		if (str[i] == ' ')
		{
			result += ' ';
			continue;
		}
		flag = 0;
		if (str[i] < 'a' || str[i] > 'z')
			continue;

		for (int j = 0; j <= 25; j++)
			if (mappingTable[j][0] == str[i])
			{
				flag = j;
				break;
			}
		result += mappingTable[flag][1];
	}
	cout << "The result is: " << result << endl << endl;
}

void Dec(string str)
{
	int length = str.length();
	string result;
	int flag = 0;
	for (int i = 0; i <= length - 1; i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
		if (str[i] == ' ')
		{
			result += ' ';
			continue;
		}
		flag = 0;
		if (str[i] < 'a' || str[i] > 'z')
			continue;

		for (int j = 0; j <= 25; j++)
			if (mappingTable[j][1] == str[i])
			{
				flag = j;
				break;
			}
		result += mappingTable[flag][0];
	}
	cout << "The result is: " << result << endl;
}

//����������Կ�������û�����������Ҫ���ܵ��ַ��������������Ҫ���ܵ��ַ�����
int main()
{
	initial();
	string keystring;
	cout << "please enter your key: ";
	getline(cin, keystring);
	setTable(keystring);
	string mystring;
	cout << "Please input the string you want to encrypt: ";
	getline(cin, mystring);
	Enc(mystring);
	mystring = { 0 };
	cout << "Please input the string you want to decrypt: ";
	getline(cin,mystring);
	Dec(mystring);
	system("pause");
	return 0;
}