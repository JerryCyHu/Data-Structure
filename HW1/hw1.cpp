#include<iostream>
#include<cmath>      
#include<cstdlib>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

int flushLeft(int width, vector<string> content, string outputName) {
	ofstream file;
	file.open(outputName, ofstream::out | ofstream::trunc);
	for (int i = 1; i <= width+4; i++) {
		cout << '-';//doc
		cout << flush;
		file << '-';
	}
	cout << endl;//doc
	file << endl;
	//cout << width << endl;
	bool stillThisLine = true;
	int longitudeOfCurrentLine = 0;
	int indexOfContent = 0;
	int currentIndex = 0;
	while (indexOfContent < content.size()) {
		//cout << indexOfContent;
		stillThisLine = true;
		longitudeOfCurrentLine = 0;
		//indexOfContent--;
		while (stillThisLine)
		{
			longitudeOfCurrentLine += content[indexOfContent].length() + 1;
			if (longitudeOfCurrentLine > width + 1) {
				longitudeOfCurrentLine -= content[indexOfContent].length() + 2;
				indexOfContent--;
				if (longitudeOfCurrentLine > 0) {
					//add the words into that line
					cout << "| ";//doc
					cout << flush;
					file << "| ";
					for (int i = currentIndex; i <= indexOfContent; i++) {
						if (i < indexOfContent) {
							cout << content[i] << ' ';//doc
							cout << flush;
							file << content[i] << ' ';
						}
						else
						{
							cout << content[i];//doc
							cout << flush;
							file << content[i];
						}

					}
					int restSpace = width - longitudeOfCurrentLine;
					for (int i = 1; i <= restSpace; i++) {
						cout << ' ';//doc
						cout << flush;
						file << ' ';
					}
					cout << " |" << endl;//doc
					cout << flush;
					file << " |" << endl;
					currentIndex = indexOfContent + 1;
				}
				else {
					cout << "width is too short.";
					return 0;
				}
				stillThisLine = false;
			}
			indexOfContent++;
		}
	}
	for (int i = 1; i <= width+4; i++) {
		cout << '-';//doc
		file << '-';
	}
	//cout << longitudeOfCurrentLine << endl << indexOfContent << endl;
	file.close();
	return 0;
}

int flushRight(int width, vector<string> content, string outputName) {
	ofstream file;
	file.open(outputName, ofstream::out | ofstream::trunc);
	for (int i = 1; i <= width + 4; i++) {
		cout << '-';//doc
		cout << flush;
		file << '-';
	}
	cout << endl;//doc
	file << endl;
	//cout << width << endl;
	bool stillThisLine = true;
	int longitudeOfCurrentLine = 0;
	int indexOfContent = 0;
	int currentIndex = 0;
	while (indexOfContent < content.size()) {
		//cout << indexOfContent;
		stillThisLine = true;
		longitudeOfCurrentLine = 0;
		//indexOfContent--;
		while (stillThisLine)
		{
			longitudeOfCurrentLine += content[indexOfContent].length() + 1;
			if (longitudeOfCurrentLine > width + 1) {
				longitudeOfCurrentLine -= content[indexOfContent].length() + 2;
				indexOfContent--;
				if (longitudeOfCurrentLine > 0) {
					//add the words into that line
					cout << "| ";//doc
					cout << flush;
					file << "| ";
					//fullfill Space
					int restSpace = width - longitudeOfCurrentLine;
					for (int i = 1; i <= restSpace; i++) {
						cout << ' ';//doc
						cout << flush;
						file << ' ';
					}
					for (int i = currentIndex; i <= indexOfContent; i++) {
						if (i < indexOfContent) {
							cout << content[i] << ' ';//doc
							cout << flush;
							file << content[i] << ' ';
						}
						else
						{
							cout << content[i];//doc
							cout << flush;
							file << content[i];
						}

					}
					cout << " |" << endl;//doc
					cout << flush;
					file << " |" << endl;
					currentIndex = indexOfContent + 1;
				}
				else {
					cout << "width is too short.";
				}
				stillThisLine = false;
			}
			indexOfContent++;
		}
	}
	for (int i = 1; i <= width + 4; i++) {
		cout << '-';//doc
		file << '-';
	}
	//cout << longitudeOfCurrentLine << endl << indexOfContent << endl;
	file.close();
	return 0;
}

int lastLineForFJ(int width, vector<string> content, string outputName) {
	ofstream file;
	file.open(outputName, ios_base::app | ios_base::out);
	bool stillThisLine = true;
	int longitudeOfCurrentLine = 0;
	int indexOfContent = 0;
	int currentIndex = 0;
	while (indexOfContent < content.size()) {
		//cout << indexOfContent;
		stillThisLine = true;
		longitudeOfCurrentLine = 0;
		//indexOfContent--;
		while (stillThisLine)
		{
			longitudeOfCurrentLine += content[indexOfContent].length() + 1;
			if (longitudeOfCurrentLine > width + 1) {
				longitudeOfCurrentLine -= content[indexOfContent].length() + 2;
				indexOfContent--;
				if (longitudeOfCurrentLine > 0) {
					//add the words into that line
					//cout << '|';//doc
					//cout << flush;
					//file << '|';
					for (int i = currentIndex; i <= indexOfContent; i++) {
						if (i < indexOfContent) {
							cout << content[i] << ' ';//doc
							cout << flush;
							file << content[i] << ' ';
						}
						else
						{
							cout << content[i];//doc
							cout << flush;
							file << content[i];
						}

					}
					int restSpace = width - longitudeOfCurrentLine;
					for (int i = 1; i <= restSpace; i++) {
						cout << ' ';//doc
						cout << flush;
						file << ' ';
					}
					cout << " |" << endl;//doc
					cout << flush;
					file << " |" << endl;
					currentIndex = indexOfContent + 1;
				}
				else {
					cout << "width is too short!!";
					return 0;
				}
				stillThisLine = false;
			}
			indexOfContent++;
		}
	}
	for (int i = 1; i <= width + 4; i++) {
		cout << '-';//doc
		file << '-';
	}
	file.close();
	return 0;
}

int fullJustify(int width, vector<string> content, string outputName) {
	ofstream file;
	file.open(outputName, ofstream::out | ofstream::trunc);
	bool stillThisLine = true;
	int longitudeOfCurrentLine = 0;
	int indexOfContent = 0;
	int currentIndex = 0;
	int restSpace = 0;
	int spaceSize = 0;
	for (int i = 1; i <= width + 4; i++) {
		cout << '-';//doc
		file << '-';
	}
	cout << endl;
	file << endl;
	while (indexOfContent < content.size()) {
		//cout << indexOfContent;
		stillThisLine = true;
		longitudeOfCurrentLine = 0;
		restSpace = 0;//how Many
		spaceSize = 0;//how big
		//indexOfContent--;
		cout << "| ";
		file << "| ";
		while (stillThisLine)
		{
			longitudeOfCurrentLine += content[indexOfContent].length();
			if ((indexOfContent-currentIndex) > 0) {
				//cout << "i-c" << indexOfContent - currentIndex;
				if ((width - longitudeOfCurrentLine) / (indexOfContent-currentIndex) <= 0)
				{
					stillThisLine = false;
					longitudeOfCurrentLine -= content[indexOfContent].length();
					indexOfContent--;
					restSpace = width - longitudeOfCurrentLine;
					int numOfMoreSpaceToBeAdded;
					//cout << indexOfContent - currentIndex;
					if ((indexOfContent - currentIndex) > 0) {
						spaceSize = restSpace / (indexOfContent - currentIndex);
						numOfMoreSpaceToBeAdded = restSpace % (indexOfContent - currentIndex);
					}
					else
					{
						spaceSize = restSpace;
						numOfMoreSpaceToBeAdded = 0;
					}
					string spaces = "";
					string advancedSpaces  = "";
					for (int i = 1; i <= spaceSize; i++) {
						spaces.append(" ");
					}
					advancedSpaces = spaces;
					advancedSpaces.append(" ");
					for (int i = currentIndex; i <= indexOfContent; i++)
					{
						if (i == indexOfContent&&indexOfContent-currentIndex!=0) {
							cout << content[i];
							file << content[i];
						}
						else if (numOfMoreSpaceToBeAdded > 0) {
							cout << content[i] << advancedSpaces;
							file << content[i] << advancedSpaces;
							numOfMoreSpaceToBeAdded--;
						}
						else
						{
							cout << content[i] << spaces;
							file << content[i] << spaces;
						}
					}
					currentIndex = indexOfContent + 1;
					
				}
			}
			//////////////////////
			else if(content[indexOfContent].length()>width){
				cout << "Space is too short.";
				
				return 0;
			}
			//////////////////
			indexOfContent++;
			if (indexOfContent >= content.size()) {
				file.close();
				vector<string> v;
				for (int i = currentIndex; i < indexOfContent; i++)
				{
					v.push_back(content[i]);
				}
				
				lastLineForFJ(width, v, outputName);
				return 0;
			}
		}
		cout << " |" << endl;
		file << " |" << endl;
	}
	//cout << longitudeOfCurrentLine << endl << indexOfContent << endl;
	return 0;
}


int main(int argc, char* argv[]) {
	string inputFileName = argv[1];
	string outputFileName = argv[2];
	int widthOfTheText = atoi(argv[3]);
	string format = argv[4];
	ifstream directionOfFile(inputFileName.c_str());
	string content((istreambuf_iterator<char>(directionOfFile)),
		istreambuf_iterator<char>());
	vector<string> contentDictionary;
	string word = "";
	int q = 0;
	if (widthOfTheText <= 1) {
		cout << "Width is too short.";
	}
	else {
		for (string::iterator i = content.begin(); i != content.end(); i++)
		{
			if (content[q] != ' ' && content[q] != '\n') {
				word += content[q];
				if (word.length() == widthOfTheText + 1)
				{
					word.erase(word.length() - 2, 2);
					q -= 2;
					i -= 2;
					word += "-";
					contentDictionary.push_back(word);
					word = "";
				}
			}
			else {
				if (word != "") {
					contentDictionary.push_back(word);
					word = "";
				}
			}
			q++;
		}
		///////////////////////////////////////////
		if (format == "full_justify")
		{
			fullJustify(widthOfTheText, contentDictionary, outputFileName);
		}
		else if (format == "flush_right")
		{
			flushRight(widthOfTheText, contentDictionary, outputFileName);
		}
		else if (format == "flush_left")
		{
			flushLeft(widthOfTheText, contentDictionary, outputFileName);
		}
	}
	return 0;
}