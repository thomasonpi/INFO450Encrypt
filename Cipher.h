#include<iostream>
#include<string>
#include<time.h>
#include<stdlib.h>
#include<fstream>
using namespace std;

class Cipher{

		string key;
		int keyLen;
		int twistCount = 0;	
	public:
		Cipher();
		string encrypt(string strIn);
		string decrypt(string strIn);
		void setKey(string keyIn);
		void fileWrap(int menuPick, string fileName);
};
