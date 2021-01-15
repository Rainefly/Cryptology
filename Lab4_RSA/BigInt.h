#pragma once
#ifndef __BIGINT_H__
#define __BIGINT_H__

#include<iostream>
#include<string>
using namespace std;

const int max = 1025;
class BigInte 
{
private:
	bool num[max];          // 只能存0和1，且开的空间尽量小
public:
	bool sign;              //用来存储该大整数的符号
	BigInte();              //初始化，全部位置0
	BigInte(int in);        //十进制转二进制的存储
	BigInte(string in);     //十六进制转二进制的存储
	BigInte(string in,int a);  //按照ascii输入字符  
	void GeneRandom(int n); //生成随机数，传入的n表示随机数的位数
	void leftMove(int i);   //左移，传入的n表示左移的位数
	void make(int i, bool a); //置位，传入的参数依次表示：置位的位数和置位的值
	void out();               //按十六进制输出结果
	void Sign_Change();       //符号改变
	BigInte abs();            //取绝对值
	bool operator[](int i);

	//以下为友元函数的定义，即对一些运算符进行重载
	friend BigInte operator+(BigInte a, BigInte b);
	friend BigInte operator-(BigInte a, BigInte b);
	friend BigInte operator*(BigInte a, BigInte b);
	friend BigInte operator/(BigInte a, BigInte b);
	friend BigInte operator%(BigInte a, BigInte b);
	friend bool operator>(BigInte a, BigInte b);
	friend bool operator==(BigInte a, BigInte b);
	friend bool operator!=(BigInte a, BigInte b);

	//以下是基于基本运算实现的一些更复杂的运算
	BigInte mod(BigInte a, BigInte b, BigInte c);          //取余
	BigInte exp(BigInte x, BigInte y);                     //先指数乘，再取模，即result=（*this）^x (mod y)
	BigInte inv(BigInte x);                                //求x对y的逆元，即result* x = 1(mod y)
};

#endif
