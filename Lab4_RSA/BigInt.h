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
	bool num[max];          // ֻ�ܴ�0��1���ҿ��Ŀռ価��С
public:
	bool sign;              //�����洢�ô������ķ���
	BigInte();              //��ʼ����ȫ��λ��0
	BigInte(int in);        //ʮ����ת�����ƵĴ洢
	BigInte(string in);     //ʮ������ת�����ƵĴ洢
	BigInte(string in,int a);  //����ascii�����ַ�  
	void GeneRandom(int n); //����������������n��ʾ�������λ��
	void leftMove(int i);   //���ƣ������n��ʾ���Ƶ�λ��
	void make(int i, bool a); //��λ������Ĳ������α�ʾ����λ��λ������λ��ֵ
	void out();               //��ʮ������������
	void Sign_Change();       //���Ÿı�
	BigInte abs();            //ȡ����ֵ
	bool operator[](int i);

	//����Ϊ��Ԫ�����Ķ��壬����һЩ�������������
	friend BigInte operator+(BigInte a, BigInte b);
	friend BigInte operator-(BigInte a, BigInte b);
	friend BigInte operator*(BigInte a, BigInte b);
	friend BigInte operator/(BigInte a, BigInte b);
	friend BigInte operator%(BigInte a, BigInte b);
	friend bool operator>(BigInte a, BigInte b);
	friend bool operator==(BigInte a, BigInte b);
	friend bool operator!=(BigInte a, BigInte b);

	//�����ǻ��ڻ�������ʵ�ֵ�һЩ�����ӵ�����
	BigInte mod(BigInte a, BigInte b, BigInte c);          //ȡ��
	BigInte exp(BigInte x, BigInte y);                     //��ָ���ˣ���ȡģ����result=��*this��^x (mod y)
	BigInte inv(BigInte x);                                //��x��y����Ԫ����result* x = 1(mod y)
};

#endif
