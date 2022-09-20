#include<bits/stdc++.h>

using namespace std;

string mainText, encryptedText, decryptedText;


void encryption(int number)
{
int i;
	for(i=0; i<mainText.size();i++)
	{

            encryptedText+= mainText[i]+number;

	}

	cout <<"The encrypted test: " << encryptedText;
}
void decryption(int number)
{
int i;
	for(i=0; i<mainText.size();i++)
	{

          decryptedText+=encryptedText[i]-number;

	}

	cout <<"The decrypted test: " << decryptedText;
}


int main()
{
	cout << "Enter the text: ";
	getline(cin,mainText);
	int number;
	cout <<"Enter the number: ";
	cin >> number;

	 encryption(number);
	 cout<<'\n';
	 decryption(number);

}
