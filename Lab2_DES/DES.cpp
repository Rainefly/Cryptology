#include<iostream>
#include<string.h>
#include<bitset>
using namespace std;

//书上所有表中的数字编号是从左往右读的，越往右越大，就跟普通的int型数组一样
//但是bitsets这个数据结构是从右往左读的，越往左越大，所以下面的代码中有很多这样的索引转换。

//以下为加密操作
//先是处理明文的表
//设置IP置换表
int IP[64] = 
{
	58,50,42,34,26,18,10,2, 60,52,44,36,28,20,12,4,
	62,54,46,38,30,22,14,6, 64,56,48,40,32,24,16,8,
	57,49,41,33,25,17, 9,1, 59,51,43,35,27,19,11,3,
	61,53,45,37,29,21,13,5, 63,55,47,39,31,23,15,7
};

//扩展矩阵E：把32位变成48位
int E[48] = 
{
	32, 1, 2, 3, 4, 5,  4, 5, 6, 7, 8, 9,
	 8, 9,10,11,12,13, 12,13,14,15,16,17,
	16,17,18,19,20,21, 20,21,22,23,24,25,
	24,25,26,27,28,29, 28,29,30,31,32, 1
};

// 尾置换表
int IP_1[] =
{ 
	40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41,  9, 49, 17, 57, 25 
};

//再是处理密钥所需的表
//第一次置换矩阵
int PC_1[56] = 
{
	57, 49, 41, 33, 25, 17,  9,  1, 58, 50, 42, 34, 26, 18,
	10,  2, 59, 51, 43, 35, 27, 19, 11,  3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,  7, 62, 54, 46, 38, 30, 22,
	14,  6, 61, 53, 45, 37, 29, 21, 13,  5, 28, 20, 12,  4
};

//第二次置换矩阵
int PC_2[48] = {
	14, 17, 11, 24,  1,  5,  3, 28, 15,  6, 21, 10,
	23, 19, 12,  4, 26,  8, 16,  7, 27, 20, 13,  2,
	41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
};

//密钥的循环左移表
int shiftBits[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };


//设置置换运算P
int P[32] = 
{
	16,7,20,21,29,12,28,17,  1,15,23,26, 5,18,31,10,
	 2,8,24,14,32,27, 3, 9, 19,13,30, 6,22,11, 4,25
};

//构建S盒
int S_BOX[8][4][16] = {
	{
		{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
		{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
		{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
		{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
	},
	{
		{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
		{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
		{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
		{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
	},
	{
		{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
		{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
		{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
		{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
	},
	{
		{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
		{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
		{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
		{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
	},
	{
		{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
		{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
		{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
		{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
	},
	{
		{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
		{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
		{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
		{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
	},
	{
		{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
		{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
		{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
		{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
	},
	{
		{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
		{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
		{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
		{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
	}
};

//输入密钥和子密钥设成全局变量
bitset<64> key;                // 输入的密钥是64位的，经过置换选择1后变成了56位，即64->56
bitset<48> subKey[16];         // 存放16轮子密钥


//填充 0 
void zeroFill(bitset<64> in, bitset<64> out, int inlen)
{
	int i;
	for (i = 0; i < 64; i++)
	{
		if (i < inlen)
		{
			out[63-i] = in[63-i];
		}
		if (i >= inlen)
		{
			out[63-i] = 0;
		}
	}
}

//左循环移位函数，注意这里是循环的，超出的位数要重新补到低位，而不是低位补0
bitset<28> leftShift(bitset<28> k, int shift)
{
	bitset<28> tmp = k;
	for (int i = 27; i >= 0; --i)
	{
		if (i - shift < 0)
			k[i] = tmp[i - shift + 28];
		else
			k[i] = tmp[i - shift];
	}
	return k;
}

//以下代码用以根据用户输入的64位密钥生成16个48位的子密钥
void generateKeys()
{
	bitset<56> NewKey;
	bitset<28> left;
	bitset<28> right;
	bitset<48> compressKey;
	// 去掉奇偶标记位，将64位密钥变成56位
	for (int i = 0; i < 56; ++i)
		NewKey[55 - i] = key[64 - PC_1[i]];    //根据PC_1表把64位置换成56位
	// 通过16轮迭代，得到每一次迭代的48位用作和明文F函数加密的子密钥
	for (int round = 0; round < 16; ++round)
	{
		for (int i = 28; i < 56; ++i)
			left[i - 28] = NewKey[i];
		for (int i = 0; i < 28; ++i)
			right[i] = NewKey[i];
		// 根据做循环移位表的位数左移
		left = leftShift(left, shiftBits[round]);
		right = leftShift(right, shiftBits[round]);
		// 压缩置换，把得到的新的56位比特串根据PC_2表得到48位子密钥
		for (int i = 28; i < 56; ++i)
			NewKey[i] = left[i - 28];
		for (int i = 0; i < 28; ++i)
			NewKey[i] = right[i];
		for (int i = 0; i < 48; ++i)
			compressKey[47 - i] = NewKey[56 - PC_2[i]];
		subKey[round] = compressKey;     //得到16轮子密钥
	}
}


//以下按照程序处理顺序来构造各个功能的函数

bitset<64> decToBin(const int in[8])
{
	bitset<64> out;
	for (int i = 0; i < 8; i++)
	{
		//高位和低位
		int high = in[i] / 16;
		int low = in[i] % 16;
		for (int j = 0; j < 4; j++)
		{
			out[63-(8 * i + 7 - j)] = low % 2;
			out[63-(8 * i + 3 - j)] = high % 2;
			low /= 2;
			high /= 2;
		}
	}
	cout << "64位形式为：" << endl;
	for (int i = 0; i <= 63; i++)
		cout << out[63-i];
	cout << endl;
	return out;
}

int* binToDec(bitset<64> in)
{
	int out[8];
	for (int i = 0; i < 8; i++)
	{
		out[i] = 16 * (in[63-8 * i] * 8 + in[63-8 * i - 1] * 4 + in[63-8 * i - 2] * 2 + in[63-8 * i - 3]) + (in[63-8 * i - 4] * 8 + in[63-8 * i - 5] * 4 + in[63-8 * i - 6] * 2 + in[63-8 * i - 7]);
	}
	for (int i = 0; i <= 7; i++)
		cout <<(hex)<<"0x"<<out[i] << " ";
	return out;
}

bitset<32> F(bitset<32> R, bitset<48> K)
{
	bitset<48> Rightexpand;
	// 对明文右串的扩展置换，即32 -> 48
	for (int i = 0; i < 48; ++i)
		Rightexpand[47 - i] = R[32 - E[i]];
		//Rightexpand[i] = R[E[i]];
	// 与密钥异或
	Rightexpand = Rightexpand ^ K;
	// 使用S_BOX置换表进行代换，得到F的输出
	bitset<32> output;
	int x = 0;   //x用来偏移output的下标
	for (int i = 0; i < 48; i = i + 6)    //每6个数为一组
	{
		int row = Rightexpand[47 - i] * 2 + Rightexpand[47 - i - 5];   //直接算出值
		int col = Rightexpand[47 - i - 1] * 8 + Rightexpand[47 - i - 2] * 4 + Rightexpand[47 - i - 3] * 2 + Rightexpand[47 - i - 4];
		int num = S_BOX[i / 6][row][col];
		bitset<4> binary(num);    //把S盒里面的值转化成4位二进制数
		//注意bitsets这个数据结构的索引[]是从右往左读的，越往左数越大
		output[31 - x] = binary[3];
		output[31 - x - 1] = binary[2];
		output[31 - x - 2] = binary[1];
		output[31 - x - 3] = binary[0];
		x += 4;
	}
	// 对S盒代换后得到的32位比特串进行P置换，得到32位比特串
	bitset<32> tmp = output;
	for (int i = 0; i < 32; ++i)
		output[31 - i] = tmp[32 - P[i]];
	return output;
}


bitset<64> encrypt(bitset<64>& plain)
{
	bitset<64> cipher;         //
	bitset<64> currentBits;    //初始置换后的64位输入
	bitset<32> left;           //左边的32位
	bitset<32> right;          //右边的32位
	bitset<32> newLeft;        //用于表示每一轮产生的新左部=right
	// 初始置换IP
	for (int i = 0; i < 64; ++i)
		currentBits[63 - i] = plain[64 - IP[i]];
		//currentBits[i] = plain[IP[i]];
	// 获取Li和Ri
	for (int i = 32; i < 64; ++i)
		left[i - 32] = currentBits[i];
	for (int i = 0; i < 32; ++i)
		right[i] = currentBits[i];
	// 进行迭代（共16轮）
	for (int round = 0; round < 16; round++)
	{
		newLeft = right;   //新左部直接等于旧的右部，即Li=Ri-1
		right = left ^ F(right, subKey[round]);     //新右部Ri=Li-1 xor F(Ri-1,Ki）<-这里注意，我用的并不是所谓Ki，加密到哪一轮我就使用哪一轮需要的子密钥
		left = newLeft;    //更新left的表示，用于下一轮迭代
	}
	// 左右交换L16和R16得到R16L16的64位比特串
	for (int i = 0; i < 32; ++i)
		currentBits[i] = left[i];        //把left的放在高位
	    //cipher[i]=left[i];
	for (int i = 32; i < 64; ++i)
		currentBits[i] = right[i - 32];  //把right的放在低位
	    //cipher[i]=right[i-32];
	// 用IP_1表实现逆初始置换
	//currentBits = cipher;
	for (int i = 0; i < 64; ++i)
		cipher[63 - i] = currentBits[64 - IP_1[i]];
	return cipher;
}



bitset<64> decrypt(bitset<64>& cipher)
{
	bitset<64> plaintext;
	bitset<64> currentBits;
	bitset<32> left;
	bitset<32> right;
	bitset<32> newLeft;
	// 初始置换IP
	for (int i = 0; i < 64; ++i)
		currentBits[63 - i] = cipher[64 - IP[i]];
	// 获取Li和Ri
	for (int i = 32; i < 64; ++i)
		left[i - 32] = currentBits[i];
	for (int i = 0; i < 32; ++i)
		right[i] = currentBits[i];
	// 进行迭代（共16轮），这里的子密钥和加密时使用的顺序相反
	for (int round = 0; round < 16; round++)
	{
		newLeft = right;
		right = left ^ F(right, subKey[15 - round]);
		left = newLeft;
	}
	// 左右交换L16和R16得到R16L16的64位比特串
	for (int i = 0; i < 32; ++i)
		currentBits[i] = left[i];
	for (int i = 32; i < 64; ++i)
		currentBits[i] = right[i - 32];
	// 用IP_1表实现逆初始置换
	//currentBits = plaintext;
	for (int i = 0; i < 64; ++i)
		plaintext[63 - i] = currentBits[64 - IP_1[i]];
	// 返回明文
	return plaintext;
}

int main()
{
	int type;
	cout << "Using DES Code:" << endl << "Input 1 to Encode and 0 to Decode,if you want to exit,input 2: ";

	while (true)
	{
		cin >> type;
		if (type == 1)
		{
			int intxt[8], inkey[8];
			int* outtxt;
			bitset<64> bitintxt,bitouttxt;
			cout << "***********现在是加密模式************" << endl << "请输入密钥（hex）："<<endl;
			for (int i = 0; i <= 7; i++)
				cin >> (hex) >> inkey[i];
			key = decToBin(inkey);
			cout << "请输入明文（hex）：" << endl;
			for (int i = 0; i <= 7; i++)
				cin >> (hex) >> intxt[i];
			bitintxt = decToBin(intxt);
			generateKeys();
			bitouttxt = encrypt(bitintxt);
			cout << "下面输出64位密文：" << endl;
			for (int i = 0; i <= 63; i++)
				cout << bitouttxt[63 - i];
			cout << endl;
			cout << "密文的十六进制形式为：" << endl;
			outtxt = binToDec(bitouttxt);
			cout << endl << endl << "Input 1 to Encode and 0 to Decode,if you want to exit,input 2: ";
			continue;
		}

		if (type == 0)
		{
			int intxt[8], inkey[8];
			int* outtxt;
			bitset<64> bitintxt, bitouttxt;
			cout << "***********现在是解密模式************" << endl << "请输入密钥（hex）："<<endl;
			for (int i = 0; i <= 7; i++)
				cin >> (hex) >> inkey[i];
			key = decToBin(inkey);
			cout << "请输入密文（hex）：" << endl;
			for (int i = 0; i <= 7; i++)
				cin >> (hex) >> intxt[i];
			bitintxt = decToBin(intxt);
			generateKeys();
			bitouttxt = decrypt(bitintxt);
			cout << "下面输出64位明文：" << endl;
			for (int i = 0; i <= 63; i++)
				cout << bitouttxt[63 - i];
			cout << endl;
			cout << "明文的十六进制形式为：" << endl;
			outtxt = binToDec(bitouttxt);
			cout << endl << endl << "Input 1 to Encode and 0 to Decode,if you want to exit,input 2: ";
			continue;
		}
		if (type == 2)
		{
			cout << endl << "It is over!" << endl;
			break;
		}
	}
	system("pause");
	return 0;
}