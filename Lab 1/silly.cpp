#include<iostream>
#include<cmath>      
#include<cstdlib>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

int multiply(int howmany, char* numArray[]) {
	int sum = 1;
	for (int i = 1; i < howmany; i++) {
		sum *= atoi(numArray[i]);
	}
	cout << "product of integers: " << sum;
	return 0;
}

int sorting(int howmany, char* wordsArray[]) {
	//cout << howmany;
	vector<string> words;
	for (int i = 0; i < howmany; i++) {
		int sizeOfWords = words.size();
		//cout << sizeOfWords;
		for (int q = 0; q <= sizeOfWords; q++) {
			if (sizeOfWords == 0) {
				words.push_back(wordsArray[i]);
				break;
			}
			else if (wordsArray[i][0] < words[q][0]) {
				words.insert(words.begin() + q, wordsArray[i]);
				break;
			}
			else if(q == sizeOfWords -1 && wordsArray[i][0] >= words[q][0])
			{
				words.push_back(wordsArray[i]);
				break;
			}
		}
	}
	for (int i = 1; i < words.size(); i++) {
		//cout << flush;
		cout << words[i] << ' ';
	}
	cout << endl;
	return 0;
}

int main(int argc, char* argv[]) {
	//vector<string> words;
	//vector<int> numbers;
	//for (int i = 0; i < argc; i++)
	//{
	//	if (argv[i])
	//}
	sorting(argc, argv);
	return 0;
}