/* !namehere! 12.6.19
 * P. Thomason INFO450
 *
 * This one collects user input (menu choice, key, and file path)
 * and passes them to the methods of Cipher as needed.
 */
#include<iostream>
#include<string>
#include<fstream>
#include <time.h>
#include<stdlib.h>
#include"Cipher.h"
using namespace std;


int main(){

	Cipher myCipher;
	string  key, filePath;
	int menuPick = 0;

	cout << "1 to encrypt a file, 2 to decrypt a file, 3 to exit:  ";
	cin >> menuPick;
	cin.ignore();

	while (menuPick !=3){
	//move to constructor
	cout << "Key please (any char, any length):  ";
        getline(cin, key);
	myCipher.setKey(key);

	cout << "where is the file please: ";
	getline(cin, filePath);

	myCipher.fileWrap(menuPick,filePath);	

	cout << "1- encrypt, 2- decrypt, 3- exit: ";
	cin >> menuPick;
	cin.ignore();
	}

	cout << "goodbye!" <<endl;	
	cout << endl;
	return 0;

}
