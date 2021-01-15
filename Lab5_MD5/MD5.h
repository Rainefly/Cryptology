#pragma once
#ifndef CLION_WORK_MD5_H
#define CLION_WORK_MD5_H

class MD5
{
public:
    unsigned int count[2];
    unsigned int state[4];   //4个32位bit的状态寄存器ABCD
    unsigned char buffer[64];  //缓冲区（64*8=512bit）
};

// 定义第1-4轮的基本逻辑函数
#define F(x,y,z) ((x & y) | (~x & z))
#define G(x,y,z) ((x & z) | (y & ~z))
#define H(x,y,z) (x^y^z)
#define I(x,y,z) (y ^ (x | ~z))

// 循环左移函数
#define ROTATE_LEFT(x,n) ((x << n) | (x >> (32-n)))

// 定义第1-4轮的压缩函数
#define FF(a,b,c,d,x,s,T) \
          { \
          a += F(b,c,d) + x + T; \
          a = ROTATE_LEFT(a,s); \
          a += b; \
          }
#define GG(a,b,c,d,x,s,T) \
          { \
          a += G(b,c,d) + x + T; \
          a = ROTATE_LEFT(a,s); \
          a += b; \
          }
#define HH(a,b,c,d,x,s,T) \
          { \
          a += H(b,c,d) + x + T; \
          a = ROTATE_LEFT(a,s); \
          a += b; \
          }
#define II(a,b,c,d,x,s,T) \
          { \
          a += I(b,c,d) + x + T; \
          a = ROTATE_LEFT(a,s); \
          a += b; \
          }


void MD5Init(MD5* context);
void MD5Packet_Refresh(MD5* context, unsigned char* input, unsigned int inputlen);
void MD5Trans(MD5* context, unsigned char digest[16]);
void MD5Encrypt(unsigned int state[4], unsigned char block[64]);
void MD5Int_to_char(unsigned char* output, unsigned int* input, unsigned int len);
void MD5Char_to_int(unsigned int* output, unsigned char* input, unsigned int len);

#endif
