//#include<iostream>
//#include<string>
//
//using namespace std;
//
////�������ʵ�ֵ�����λ�������û�������λ����ĵļӽ��ܣ�
////Ҳ����ʵ����λ����Ĺ�����������λ����1-25����������˹�ʶ���ĸ����ʿɶ����ô����ѱ�ע�ͣ�����ʹ�ÿ��Խ��ע�ͣ�
//void enc(string str, int offset)
//{
//    //int length = strlen(str);
//    int length = str.length();
//
//    string result;
//
//    for (int i = 0; i <= length - 1; i++)
//    {
//        if (str[i] >= 'A' && str[i] <= 'Z')
//        {
//            str[i] = str[i] + 32;
//        }
//        if (str[i] == ' ')
//        {
//            result += ' ';
//            continue;
//        }
//        if (str[i] >= 'a' && str[i] <= 'z')
//        {
//            int finvalue = (str[i]-97 + offset) % 26+97;
//            char ans = (char)finvalue;
//            result = result + ans;
//        }
//    }
//
//    cout << "There's the enc result: " << result << endl;
//}
//
//void dec(string str, int offset)    //��Ϊ�����ִ�Сд������ͳһ����Сд��ĸ�������;
//{
//    int length = str.length();
//
//    string result;
//
//    for (int i = 0; i <= length - 1; i++)
//    {
//        if (str[i] >= 'A' && str[i] <= 'Z')
//        {
//            str[i] = str[i] + 32;
//        }
//        if (str[i] == ' ')
//        {
//            result += ' ';
//            continue;
//        }
//
//        if (str[i] >= 'a' && str[i] <= 'z')
//        {
//            //int tempvalue = table[str[i]];
//            //int finvalue = (tempvalue + 26 - offset) % 26;    //����Ҫ�ǵ�+26��ȡģ���Ա��ϵõ���������������
//            //char ans = 'a' + finvalue;
//            //result = result + ans;
//            int finvalue = (str[i] - 97 + 26 - offset) % 26 + 97;
//            char ans = (char)finvalue;
//            result += ans;
//        }
//    }
//    cout << "There's the dec result:" << result << endl;
//}
//
////������λ�㷨�Ĺ����㷨�� ����ʣ�µ�25�����������һ�飻
////void dec(char* str)       //��Ϊ�����ִ�Сд������ͳһ����Сд��ĸ�������;
////{
////    int length = strlen(str);
////
////    string result;
////
////    for (int j = 1; j <= 25; j++)
////    {
////        result = { 0 };
////        for (int i = 0; i <= length - 1; i++)
////        {
////            if (str[i] >= 'A' && str[i] <= 'Z')
////                str[i] = str[i] + 32;
////            if (str[i] >= 'a' && str[i] <= 'z')
////            {
////                int finvalue = (str[i] - 97 + 26 - j) % 26 + 97;
////                char ans = (char)finvalue;
////                result += ans;
////            }
////            else
////                result += " ";
////        }
////        cout << "Now the offset is: " << j << endl;
////        cout << "Now the dec result is: " << result << endl << endl;
////    }
////}
//
//
//int main()
//{
//    int choice = 0;
//    string mystring;
//    int length = 0;
//    int flag = 1;
//    while (flag)
//    {
//        cout << "Please enter the function you want to use: (0 Encrypt;1 Decrypt) " << endl;
//        cin >> choice;
//        cin.ignore();    //cin��getlineͬʱʹ�õ�ʱ����Ҫ����һ��cin��״̬������cin��һֱ�����ļ�������״̬�������getline�޷����룻
//        if (choice == 0)
//        {
//            cout << "please enter the string you want to encrypt: ";
//            getline(cin,mystring);
//            //cin.clear();
//            cout << "please enter the encrypt length you want to use: ";
//            cin >> length;
//            //cin.clear();
//            enc(mystring, length);
//            cout << endl;
//        }
//        else
//        {
//            cout << "please enter the string you want to decrypt: ";
//            getline(cin,mystring);
//            //cin.clear();
//            cout << "please enter the decrypt length you want to use: ";
//            cin >> length;
//            //cin.clear();
//            dec(mystring, length);
//            //dec(mystring);
//            cout << endl;
//        }
//        cout << "Do you want to continue? 0: Break;1: Continue; " << endl;
//        cin >> flag;
//        cin.ignore();
//    }
//
//    system("pause");
//    return 0;
//}