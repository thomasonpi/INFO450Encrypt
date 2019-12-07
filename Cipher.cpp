/* Cipher.cpp  12.6.19
 * P. Thomason
 * INFO 450
 *
 *the Cipher class handles all of the de/encrypt and includes a file wrapper
 * for file i/o
 */
#include<iostream>
#include<string>
#include<time.h>
#include<stdlib.h>
#include"Cipher.h"
using namespace std;

// constructor seeds rand to prevent calling more than once
// and getting repeat values
Cipher::Cipher(){
	
	srand(time(NULL));
}
// encrypt takes in a string, translates each char as appropriate (see 
// header). adjusts if needed to ensure output is a printing char. if plain
// text was " " inserts a keyLen  string of random characters. increments 
// the twist counter, adjusting if needed to prevent revealing plaintext
// returns encrypted string    
string Cipher::encrypt(string strIn){

	
	string out;	
	int temp = 0, temp2 =0, random;
	for(int i = 0; i<strIn.length(); i++){
		temp = int(strIn[i]);
		//de cout << temp <<  char(temp);
		temp2 = temp -(keyLen - twistCount);
		if(temp2 < 32 ) temp2 += 94;
		//de cout << temp2 << char(temp2);
		out += char(temp2);
		if (temp == 32){//generates some random noise
		
			for (int j = 0; j<keyLen; j++){
			random = rand() % 94 + 32;
			out += char(random);
			}
		}
		//de cout << char(temp2);
	}
	twistCount++;
	if (twistCount == keyLen -1) twistCount = 0;
	return out;
}
//decrypt takes a string in, reverses translation of each character. finds 
//random bits and skips over them. increments twist count to stay in sync
//with encrypt adjusts if needed. returns decrypted string 
string Cipher::decrypt(string strIn){

	
	string decrypt;
	int temp, temp2;

	for(int i = 0; i < strIn.length(); i++){
		temp = int(strIn[i]);
		temp2 = temp + (keyLen - twistCount);
		if(temp2 > 125) temp2 -= 94;
		decrypt += char(temp2);
		if (temp2 == 32) i += keyLen;//skips over noise block
	}
	twistCount++;
	if(twistCount == keyLen -1) twistCount = 0;
	return decrypt;
}
//set key takes string and sets as key for a given Cipher object, generates 
//keyLen from key
void Cipher::setKey(string keyIn){
	
	key = keyIn;
	keyLen = key.length();
	
}
//fileWrap handles file i/o and calls de/encrypt takes an int to say 
//which and a string for the file path. does some stuff if the file isn't
// there/doesn't open (which needs to be moved!). calls de/encrypt passing 
// each line. writes modified lines over original file.
void Cipher::fileWrap(int menuPick, string fileName){
	int pick;
	ifstream file;
	file.open(fileName);
	while (!file){
	
		cout << "**something's gone wrong!**"<<endl;
		cout << "it could be: the file doesn't exist, "
			<<"or the path is incorrect, "
			<<"or anything really..."<<endl;
		cout <<"enter 1 to try a new file path, 2 to create a file "
			<< "or 3 to quit: " ;
		cin >> pick;
		cin.ignore();

		switch(pick){
			case 1:
				cout << "enter a new file path: ";
				cin >> fileName;
				break;
			case 2:{
				if (menuPick == 2){
					cout<<"first we must encrypt"
						<<endl;
					menuPick = 1;
				}       
				cout <<"let's make a file! "<<endl;
				cout <<"press enter twice when done"<<endl;
				ofstream file2;
				file2.open(fileName);
				string lineIn;
				do{
					cout << ": ";
					getline(cin, lineIn);
					file2 << lineIn << endl;
				}while(!lineIn.empty() );
				
				file2.close();
				cout << "saved file at "<< fileName << endl;
				break;}
			case 3:
				cout << "sorry it didn't work out!"<< endl;
				exit (EXIT_FAILURE);
		}
		file.open(fileName);
	}
	// count lines in file to size temp strings	
	string checker;
	int lineCount = 0;
	while (getline(file, checker)) lineCount++;

	file.clear();
	file.seekg(0, ios::beg);
	string temp [lineCount+1];
	string temp2 [lineCount+1];


	int i = 0;
	switch (menuPick){
		case 1:
			
			while(file.good()){
			       getline(file, temp[i]);
				temp2[i] = encrypt(temp[i]);
				i++;
			}
		//de	for(int j=0; j<i; j++) cout << temp[j]<<endl;
		//de	for(int j=0; j<i; j++) cout << temp2[j]<<endl;
			break;
		case 2:

			while(file.good()){
			       getline(file, temp[i]);
				temp2[i] = decrypt(temp[i]);
				i++;
			}
		//de	for(int j=0; j<i; j++) cout << temp[j]<<endl;
		//de	for(int j=0; j<i; j++) cout << temp2[j]<<endl;
			break;
	}
	file.close();
	ofstream fileOut;
	fileOut.open(fileName, ios::trunc);
	for (int j =0; j<i; j++) fileOut << temp2[j] << endl;
	file.close();
	cout << "done!" << endl;
	twistCount = 0; //reset twister for next time
}

