#include <bits/stdc++.h>
#include"table.h"
using namespace std;
unsigned char keys[176];

void keyExpansion(unsigned char *key)
{

    int i;
    for (i=0;i<16;i++)
        keys[i] = key[i];
        //cout<<i;

    for(i;i<176;i=i+4)
    {
        unsigned char word[4];
        for (int j=0;j<4;j++)
           {
               word[j]=keys[i-4+j];
           }

        if ((i%16)==0)
        {
            unsigned char temp;

            temp = word[0];
            word[0] = word[1];
            word[1] = word[2];
            word[2] = word[3];
            word[3] = temp;
            for (int l=0;l<4;l++)
                {
                    word[l] = substituteBox[word[l]];
                }

            word[0]=word[0]^rconst[(i/16)-1];
        }
        for (int k=0;k<4;k++)
            {
                keys[i+k]=word[k]^keys[i-16+k];
            }
    }
}

unsigned char* addRoundKey(int round, unsigned char *st)
{
    int i;
    for (i=0;i<16;i++)
        {
            st[i]=st[i]^keys[round*16+i];
        }
        return st;
}

unsigned char* substituteByte(unsigned char *st)
{
    int i;
    for (i=0;i<16;i++)
       {
           st[i]=substituteBox[st[i]];
       }
       return st;
}

unsigned char*  shiftRow(unsigned char *st)
{
    unsigned char temp[16];
    int i;

    temp[0] = st[0];
    temp[1] = st[5];
    temp[2] = st[10];
    temp[3] = st[15];
    temp[4] = st[4];
    temp[5] = st[9];
    temp[6] = st[14];
    temp[7] = st[3];
    temp[8] = st[8];
    temp[9] = st[13];
    temp[10] = st[2];
    temp[11] = st[7];
    temp[12] = st[12];
    temp[13] = st[1];
    temp[14] = st[6];
    temp[15] = st[11];
    for (i=0;i<16;i++)
    {
            st[i]=temp[i];
    }
    return st;
}

unsigned char* mixColumn(unsigned char *st)
{
    unsigned char temp[16];
    int i;
    for (i=0;i<16;i++)
    {
        if (i%4==0)
            temp[i] = Table2[st[i]] ^ Table3[st[i+1]] ^ st[i+2] ^ st[i+3];
        if (i%4==1)
            temp[i] = Table2[st[i]] ^ Table3[st[i+1]] ^ st[i+2] ^ st[i-1];
        if (i%4==2)
            temp[i] = Table2[st[i]] ^ Table3[st[i+1]] ^ st[i-1] ^ st[i-2];
        if (i%4==3)
            temp[i] = Table2[st[i]] ^ Table3[st[i-3]] ^ st[i-1] ^ st[i-2];
    }
    for (i=0;i<16;i++)
        {
            st[i] = temp[i];
        }
        return st;
}


int main()
{
    //read input
    freopen("aes.txt","r",stdin);
    string text;
    string key;
    getline(cin,text);
    getline(cin,key);

    unsigned char* a = (unsigned char*) text.c_str();
    unsigned char* b = (unsigned char*) key.c_str();
    int i;
    cout << "Plain Text: ";
    cout<<text<<endl;
    for (i=0;i<16;i++)
    {
        printf("%X ", a[i]);
    }
    cout<<endl;

    //key expansion
    keyExpansion(b);
    //encryption
    a=addRoundKey(0,a);
    for (i=1;i<=9;i++)
    {
        a=substituteByte(a);
        a=shiftRow(a);
        a=mixColumn(a);
        a=addRoundKey(i,a);
    }
    a=substituteByte(a);
    a=shiftRow(a);
    a=addRoundKey(10,a);


    cout << "Cypher Text: ";
    for (i=0;i<16;i++)
    {
        printf("%X ", a[i]);
    }
}
