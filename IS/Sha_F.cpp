#include <bits/stdc++.h>
#include"ShaCon.h"
#include<stdint.h>
using namespace std;
int_64  Message[80];
string myString;
int_64 regC[8];

void separator(string getBlock)
{
	int chunknum = 0;

	for (unsigned int i=0; i<getBlock.length();i+=64,chunknum++) {

		Message[chunknum]=BintoDec(getBlock.substr(i, 64));
	}

	for (int g = 16; g<80; g++) {

		int_64  WordA = RorR(Message[g - 2], 19)^ RorR(Message[g - 2], 61)^ SR(Message[g - 2], 6);
		int_64  WordB = Message[g - 7];
		int_64  WordC = RorR(Message[g - 15], 1)^ RorR(Message[g - 15], 8)^ SR(Message[g - 15], 7);
        int_64  WordD = Message[g - 16];
		int_64  T = WordA + WordB + WordC + WordD;
		Message[g] = T;
	}
}
string padding()
{
    stringstream fixedstream;

	for (int i = 0; i < myString.size(); i++) {
		fixedstream << bitset<8>(myString[i]);
	}

	string s1024;
	s1024 = fixedstream.str();
	int orilen = s1024.length();
	int block_num=ceil((float)(orilen+16+1)/128);
	int tobeadded;
	int modded = orilen % 1024;
    tobeadded = block_num*1024 - modded;
	s1024 += "1";

	for (int y=0;y<tobeadded-129;y++) {
		s1024 += "0";
	}
	string lengthbits
		= std::bitset<128>(orilen).to_string();
	s1024 += lengthbits;
	return s1024;


}

void Func(int K)
{
	int_64 T1 = regC[7] + Ch(regC[4], regC[5], regC[6]) + sigmaE(regC[4]) + Message[K] + k[K];
	int_64 T2 = sigmaA(regC[0]) + maj(regC[0], regC[1], regC[2]);

            regC[7]=regC[6];//h=g
			regC[6]=regC[5];//g=f
			regC[5]=regC[4];//f=e
			regC[4]=regC[3]+T1;//e=d+t1
			regC[3]=regC[2];//d=c
			regC[2]=regC[1];//c=b
			regC[1]=regC[0];//b=a
			regC[0]=T1+T2;//a=t1+t2
}
string SHA512()
{
    string s1024=padding();
    int blocksnumber = s1024.length() / 1024;

	int chunknum = 0;

	string Blocks[blocksnumber];
	for (int i = 0; i < s1024.length();i += 1024,chunknum++) {
		Blocks[chunknum] = s1024.substr(i, 1024);
	}
	for (int letsgo = 0;letsgo < blocksnumber;letsgo++) {
		separator(Blocks[letsgo]);
        int count = 0;
        for(int i=0;i<8;i++)
            {
                regC[i]=reg[i];
            }

        for(int i=0;i<80;i++)
            {
            Func(i);
            }

        for (int j = 0; j < 8; j++)
            {
                reg[j] = reg[j]+regC[j];
            }

	}

	stringstream output;
	for(int i=0;i<8;i++)
	{output << decimaltohex(reg[i]);}


	 return output.str();
}

int main()
{
    cin>>myString;
    cout<<"SHA : "<<SHA512();

	return 0;
}

