#include<bits/stdc++.h>

using namespace std;

string mainText, encryptedText, decryptedText;
char table[26][26];


void encryption(int number)
{
int i;
	for(i=0; i<mainText.size();i++)
	{
		encryptedText+= mainText[i]+number;
		number++;
	}

	cout <<"The encrypted test: " << encryptedText;
}
void decryption(int number)
{
int i;
	for(i=0; i<mainText.size();i++)
	{
		decryptedText+=encryptedText[i]-number;
		number++;
	}

	cout <<"The decrypted test: " << decryptedText;
}


int main()
{
	cout << "Enter the text: ";
	getline(cin , mainText);
	int number=1;


	 encryption(number);
	 cout<<'\n';
    decryption(number);
 }
