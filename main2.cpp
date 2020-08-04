#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
//#include <sys/types.h>
//#include <unistd.h>
//#include <stdlib.h>

using namespace std;

int main(){

	bool isValid = false;
	const int MAX_COMMAND_SIZE = 80;
	char character;
	std::string inputBuffer;
	std::string exit = "exit";
	std::string word;
	vector<string> args;
	int index = -1;
	int fileIndex = -1;
	int charIndex = -1;
	std::string inputData;
	char commandInput[MAX_COMMAND_SIZE];
	const char* commandInputPointer = commandInput;

	cout << "$ ";
	std::getline (std::cin, inputBuffer);
	while(inputBuffer != exit) {
		stringstream ss(inputBuffer);
		while(ss >> word){
			index++;
			args.push_back(word);
			if(word == ">" || word == "<" || word == "|" || word == "&"){
				character = word[0];
				charIndex = index;
				fileIndex = index;
				fileIndex++;
				isValid = true;
			}
		}

		if(isValid){
			isValid = false;
			ofstream outfile;
			ifstream infile;
			string line;
			switch(character){
					case '>':
						for(int i = 1; i < charIndex; i++){
							inputData.append(args[i]);
							inputData.append(" ");
						} 
						commandInputPointer = inputData.c_str();
						outfile.open(args[fileIndex].c_str());
						outfile << inputData;
						outfile.close();
						cout << character;
						break;
					case '<':
						infile.open(args[fileIndex].c_str());
						while ( getline (infile,line) )
						{
						  cout << line << '\n';
						}
						infile.close();
						cout << character;
						break;
					case '|':
						cout << character;
						break;
					case '&':
						cout << character;
						break;
			}
			index = -1;
			fileIndex = -1;
			charIndex = -1;
			character = '\0';
			inputData.clear();
			word.clear();
			args.clear();
			inputBuffer.clear();
			cout << "$ ";
			std::getline (std::cin, inputBuffer);
		}
		else{
			isValid = false;
			index = -1;
			fileIndex = -1;
			charIndex = -1;
			character = '\0';
			inputData.clear();
			word.clear();
			args.clear();
			inputBuffer.clear();
			cout << "Error inputting command" << endl << "$ ";
			std::getline (std::cin, inputBuffer);
		}
	}
	return 0;
	//exit(0);
}