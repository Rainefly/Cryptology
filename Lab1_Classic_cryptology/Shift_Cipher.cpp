//#include<iostream>
//#include<string>
//
//using namespace std;
//
////这个程序实现的是移位密码在用户输入移位数后的的加解密；
////也可以实现移位密码的攻击，即将移位数从1-25遍历输出，人工识别哪个单词可读（该代码已被注释，如需使用可以解除注释）
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
//void dec(string str, int offset)    //因为不区分大小写，所以统一按照小写字母来处理的;
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
//            //int finvalue = (tempvalue + 26 - offset) % 26;    //这里要记得+26再取模，以保障得到的余数是正数；
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
////这是移位算法的攻击算法， 即把剩下的25种情况都遍历一遍；
////void dec(char* str)       //因为不区分大小写，所以统一按照小写字母来处理的;
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
//        cin.ignore();    //cin和getline同时使用的时候，需要清理一下cin的状态，否则cin会一直处在文件结束的状态，后面的getline无法读入；
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