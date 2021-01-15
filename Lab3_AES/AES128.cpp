#include<iostream>
#include<bitset>

using namespace std;


//本代码实现了AES128位的加解密
//S盒和逆S盒是通过数学原理实现的，不是通过静态规定的


int S[16][16];

//下面注释的S盒和逆S盒可以用于检验
//static int S[16][16] = {
//	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
//	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
//	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
//	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
//	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
//	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
//	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
//	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
//	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
//	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
//	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
//	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
//	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
//	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
//	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
//	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
//};

int rS[16][16];
//static int rS[16][16] = {
//	0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
//	0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
//	0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
//	0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
//	0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
//	0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
//	0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
//	0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
//	0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
//	0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
//	0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
//	0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
//	0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
//	0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
//	0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
//	0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
//};


//最大公因数
long gcd(long a, long b)
{
	long tmp;
	while (b)
	{
		tmp = a;
		a = b;
		b = tmp % b;
	}
	return a;
}

//GF(2^8)的多项式乘法
int GfMulti(int a, int b)
{
	int tmp[8] = { 0 };
	int i;
	for (i = 0; i < 8; i++)
	{
		tmp[i] = (a << i) * ((b >> i) & 0x1);
	}

	tmp[0] = tmp[0] ^ tmp[1] ^ tmp[2] ^ tmp[3] ^ tmp[4] ^ tmp[5] ^ tmp[6] ^ tmp[7];

	return tmp[0];
}

//找到最高位
int findHigherBit(int val)
{
	int i = 0;
	while (val)
	{
		i++;
		val = val >> 1;
	}
	return i;
}

//GF(2^8)的多项式除法
int Gfdiv(int div_ed, int div, int* remainder)
{
	int r0 = 0;
	int  qn = 0;
	int bitCnt = 0;

	r0 = div_ed;

	bitCnt = findHigherBit(r0) - findHigherBit(div);
	while (bitCnt >= 0)
	{
		qn = qn | (1 << bitCnt);
		r0 = r0 ^ (div << bitCnt);
		bitCnt = findHigherBit(r0) - findHigherBit(div);
	}
	*remainder = r0;
	return qn;
}

//GF(2^8)多项式的扩展欧几里得算法
int externEuc(int a, int m)
{
	int r0, r1, r2;
	int  qn, v0, v1, v2, w0, w1, w2;
	r0 = m;
	r1 = a;
	v0 = 1;
	v1 = 0;
	w0 = 0;
	w1 = 1;
	while (r1 != 1)
	{
		qn = Gfdiv(r0, r1, &r2);
		v2 = v0 ^ GfMulti(qn, v1);
		w2 = w0 ^ GfMulti(qn, w1);
		r0 = r1;
		r1 = r2;
		v0 = v1;
		v1 = v2;
		w0 = w1;
		w1 = w2;
	}
	return w1;
}

//S盒字节变换
int byteTransformation(int a, int x)
{
	int tmp[8] = { 0 };

	for (int i = 0; i < 8; i++)
	{
		tmp[i] = (((a >> i) & 0x1) ^ ((a >> ((i + 4) % 8)) & 0x1) ^ ((a >> ((i + 5) % 8)) & 0x1) ^ ((a >> ((i + 6) % 8)) & 0x1) ^ ((a >> ((i + 7) % 8)) & 0x1) ^ ((x >> i) & 0x1)) << i;
	}
	tmp[0] = tmp[0] + tmp[1] + tmp[2] + tmp[3] + tmp[4] + tmp[5] + tmp[6] + tmp[7];
	return tmp[0];
}

//逆S盒字节变换
int invByteTransformation(int a, int x)
{
	int tmp[8] = { 0 };

	for (int i = 0; i < 8; i++)
	{
		tmp[i] = (((a >> ((i + 2) % 8)) & 0x1) ^ ((a >> ((i + 5) % 8)) & 0x1) ^ ((a >> ((i + 7) % 8)) & 0x1) ^ ((x >> i) & 0x1)) << i;
	}
	tmp[0] = tmp[0] + tmp[1] + tmp[2] + tmp[3] + tmp[4] + tmp[5] + tmp[6] + tmp[7];
	return tmp[0];
}

//S盒产生
void s_box_gen(void)
{
	int i, j;
	int s_box_ary[16][16] = { 0 };

	//初始化S盒
	for (i = 0; i < 0x10; i++)
	{
		for (j = 0; j < 0x10; j++)
		{
			s_box_ary[i][j] = ((i << 4) & 0xF0) + (j & (0xF));
		}
	}

	//求在GF(2^8)域上的逆，0映射到自身
	for (i = 0; i < 0x10; i++)
	{
		for (j = 0; j < 0x10; j++)
		{
			if (s_box_ary[i][j] != 0)
			{
				s_box_ary[i][j] = externEuc(s_box_ary[i][j], 0x11B);
			}
		}
	}

	//对每个字节做变换
	for (i = 0; i < 0x10; i++)
	{
		for (j = 0; j < 0x10; j++)
		{
			s_box_ary[i][j] = byteTransformation(s_box_ary[i][j], 0x63);
			S[i][j] = s_box_ary[i][j];
		}
	}

	//这里可以输出S盒，用于和最上面的静态S盒结果进行检验
	//printf("\r\n\r\n    0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F");
	//for (i = 0; i < 0x10; i++)
	//{
	//	printf("\r\n%2x", i);
	//	for (j = 0; j < 0x10; j++)
	//	{
	//		printf(" %2x", S[i][j]);
	//	}
	//}
	//cout << endl;
}


//逆S盒产生
void inv_s_box_gen(void)
{
	int i, j;
	int s_box_ary[16][16] = { 0 };
	int b = 0, bb = 0;

	//初始化S盒
	for (i = 0; i < 0x10; i++)
	{
		for (j = 0; j < 0x10; j++)
		{
			s_box_ary[i][j] = ((i << 4) & 0xF0) + (j & (0xF));
		}
	}
	//对每个字节做变换
	for (i = 0; i < 0x10; i++)
	{
		for (j = 0; j < 0x10; j++)
		{
			s_box_ary[i][j] = invByteTransformation(s_box_ary[i][j], 0x05);
		}
	}

	//求在GF(2^8)域上的逆，0映射到自身
	for (i = 0; i < 0x10; i++)
	{
		for (j = 0; j < 0x10; j++)
		{
			if (s_box_ary[i][j] != 0)
			{
				s_box_ary[i][j] = externEuc(s_box_ary[i][j], 0x11B);
				rS[i][j] = s_box_ary[i][j];
			}
		}
	}

	//这里可以输出逆S盒，用于和最上面的静态逆S盒进行检验
	//printf("\r\n\r\n    0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F");
	//for (i = 0; i < 0x10; i++)
	//{
	//	printf("\r\n%2x", i);
	//	for (j = 0; j < 0x10; j++)
	//	{
	//		printf(" %2x", rS[i][j]);
	//	}
	//}
	//cout << endl;
}


//轮常量
static int rC[10] = {
	0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1b,0x36
};

//AES的乘法运算（在GF(2^8)中）
int aesMult(int a, int b)
{
	int thr = b & 0x8;  //b&1000
	int sec = b & 0x4;  //b&0100
	int fir = b & 0x2;  //b&0010
	int firstMod = b % 2;    //b&0001
	int res = 0;

	if (thr)
	{
		int temp = a;
		for (int i = 1; i <= 3; ++i) 
		{
			temp = temp << 1;    //总共移3位
			if (temp >= 256)
			{
				temp = temp ^ 0x11b;   //x^8+x^4+x^3+x+1
			}
		}
		temp = temp % 256;
		res = res ^ temp;
	}
	if (sec)
	{
		int temp = a;
		for (int i = 1; i <= 2; ++i)
		{
			temp = temp << 1;     //总共移2位
			if (temp >= 256)
			{
				temp = temp ^ 0x11b;
			}
		}
		temp = temp % 256;
		res = res ^ temp;
	}
	if (fir)
	{
		int temp = a;
		temp = temp << 1;         //总共移1位
		if (temp >= 256)
		{
			temp = temp ^ 0x11b;
		}
		temp = temp % 256;
		res = res ^ temp;
	}
	if (firstMod)
	{
		res = res ^ a;          //不用移位
	}
	return res;
}

//密钥扩展
void keyExpansion(int key[4][4], int w[11][4][4])
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; j++)
		{
			w[0][i][j] = key[j][i];   //key读进来的时候是竖着存的，现在要横着存

		}
	}
	for (int i = 1; i < 11; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			int temp[4];
			if (j == 0)    //即mod4==0
			{
				//先进行字节为单位的循环左移位
				temp[0] = w[i - 1][3][1];  
				temp[1] = w[i - 1][3][2];
				temp[2] = w[i - 1][3][3];
				temp[3] = w[i - 1][3][0];
				for (int k = 0; k < 4; ++k)
				{
					int m = temp[k];
					int row = m / 16;
					int col = m % 16;
					temp[k] = S[row][col];     //根据行号列号到S盒中取值
					if (k == 0)
					{
						//与轮常量异或
						//（看表可以得到，轮函数每次改变的只是4字节中的第一个字节，所以只要对第一个字节操作就可以了）
						temp[k] = temp[k] ^ rC[i - 1];       
					}
				}
			}
			else     //mod4!=0
			{
				temp[0] = w[i][j - 1][0];
				temp[1] = w[i][j - 1][1];
				temp[2] = w[i][j - 1][2];
				temp[3] = w[i][j - 1][3];
			}
			//通过上面的操作，可得到不同的temp
			//mod!=4时，下面的结果为：W[i]=W[i-4]⨁W[i-1] 
			//mod==4时，下面的结果为：W[i-4]⨁T(W[i-1]) 
			for (int x = 0; x < 4; x++)
			{
				w[i][j][x] = w[i - 1][j][x] ^ temp[x];
			}
		}
	}
}

void byteSub(int in[4][4], int type)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int temp = in[i][j];
			int row = temp / 16;
			int col = temp % 16;
			if (type == 1)
			{
				in[i][j] = S[row][col];
			}
			if (type == 0)
			{
				in[i][j] = rS[row][col];
			}
		}
	}
}

// 行移位，Nb=4时用三角的方式实现移位结果
void shiftRow(int in[4][4], int type) {
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (type == 1)
			{
				int temp = in[i][0];
				in[i][0] = in[i][1];
				in[i][1] = in[i][2];
				in[i][2] = in[i][3];
				in[i][3] = temp;
			}
			else    //type == 0
			{
				int temp = in[i][3];
				in[i][3] = in[i][2];
				in[i][2] = in[i][1];
				in[i][1] = in[i][0];
				in[i][0] = temp;
			}
		}
	}
}

void mixCol(int in[4][4], int type)
{
	for (int i = 0; i < 4; i++)
	{
		int t0 = in[0][i];
		int t1 = in[1][i];
		int t2 = in[2][i];
		int t3 = in[3][i];
		if (type == 1)
		{
			in[0][i] = aesMult(t0, 2) ^ aesMult(t1, 3) ^ t2 ^ t3;
			in[1][i] = t0 ^ aesMult(t1, 2) ^ aesMult(t2, 3) ^ t3;
			in[2][i] = t0 ^ t1 ^ aesMult(t2, 2) ^ aesMult(t3, 3);
			in[3][i] = aesMult(t0, 3) ^ t1 ^ t2 ^ aesMult(t3, 2);
		}
		else //type==0
		{
			in[0][i] = aesMult(t0, 14) ^ aesMult(t1, 11) ^ aesMult(t2, 13) ^ aesMult(t3, 9);
			in[1][i] = aesMult(t0, 9) ^ aesMult(t1, 14) ^ aesMult(t2, 11) ^ aesMult(t3, 13);
			in[2][i] = aesMult(t0, 13) ^ aesMult(t1, 9) ^ aesMult(t2, 14) ^ aesMult(t3, 11);
			in[3][i] = aesMult(t0, 11) ^ aesMult(t1, 13) ^ aesMult(t2, 9) ^ aesMult(t3, 14);
		}
	}
}

void addRoundKey(int in[4][4], int key[4][4])
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; j++)
		{
			in[i][j] = in[i][j] ^ key[j][i];
		}
	}
}

void encodeAES(int in[4][4], int key[4][4])
{
	int type = 1;
	int subKey[11][4][4];
	keyExpansion(key, subKey);
	addRoundKey(in, subKey[0]);     //轮密钥加
	for (int i = 1; i <= 10; ++i)
	{
		byteSub(in, type);
		shiftRow(in, type);
		if (i != 10)      //最后一次计算不需要列混合
		{
			mixCol(in, type);
		}
		addRoundKey(in, subKey[i]);
	}
}

void decodeAES(int in[4][4], int key[4][4])
{
	int type = 0;
	int subKey[11][4][4];
	keyExpansion(key, subKey);
	addRoundKey(in, subKey[10]);    //轮密钥加，和加密是反过来的
	for (int i = 9; i >= 0; --i)
	{
		byteSub(in, type);   //type值取0，即实现了Invbytesub
		shiftRow(in, type);
		//下面和书上有点不一样，书上的解密是先mixcol，但是我这里先进行轮密钥加；
		//因为我在传入明文和密钥的时候按照列存储，而生成拓展的子密钥时为了处理方便，又转化到行存储了，所以在addRoundKey函数里面有一个行列转化的地方；
		//这个小小的行列转化使得我需要先进行addRoundKey的逆操作才可以传入正确的参数到mixCol，但程序逻辑和结果不受影响。
		addRoundKey(in, subKey[i]);        //subkey与加密相反
		if (i != 0)
		{
			mixCol(in, type);
		}
	}
}

int main()
{
	// AES中数据在数组中的填充应优先填充列，之后填充行
	// 比如对于S0----S15（K0-----K15）
	// 填充后的矩阵为
	// S0 S4 S8  S12
	// S1 S5 S9  S13
	// S2 S6 S10 S14
	// S3 S7 S11 S15

	//先生成S盒和逆S盒
	s_box_gen();
	inv_s_box_gen();
	int type;
	cout << "Now start AES encode & decode" << endl;
	while (true)
	{
		cout << "You can input 0 to decode, 1 to encode and 2 to exit: ";
		cin >> type;
		if (type == 0)
		{
			int txt[4][4];
			int key[4][4];
			cout << "Now it is DECODE MODE" << endl << "Please input your cipher(hex & 128bit): ";
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					cin >> (hex) >> txt[j][i];
				}
			}
			cout << "Please input your ownKey(hex & 128bit): ";
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					cin >> (hex) >> key[j][i];
				}
			}
			decodeAES(txt, key);
			cout << "Here is the message(hex & 128bit): ";
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					cout << "0x";
					if (txt[j][i] < 16)
						cout << "0";
					cout << (hex) << txt[j][i] << " ";
				}

			}
			cout << endl;
			continue;
		}

		if (type == 1)
		{
			int txt[4][4];
			int key[4][4];
			cout << "Now it is ENCODE MODE" << endl << "Please input your message( hex & 128bit): ";
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					cin >> (hex) >> txt[j][i];
				}
			}
			cout << "Please input your ownKey(hex & 128bit): ";
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					cin >> (hex) >> key[j][i];
				}
			}
			encodeAES(txt, key);
			cout << "Here is the cipher(hex & 128bit): ";
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					//cout << "0x";
					//if (txt[j][i] < 16)
					//	cout << "0";
					//cout << (hex) << txt[j][i] << " ";
					if (txt[j][i] < 16)
						cout << "0";
					cout << (hex) << txt[j][i];
				}

			}
			cout << endl;
			continue;
		}

		if (type == 2)
		{
			cout << "The program is going to close!";
			cout << endl;
			break;
		}
	}
	system("pause");
	return 0;
}
