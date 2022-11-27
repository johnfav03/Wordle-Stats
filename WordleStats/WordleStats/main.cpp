#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Data {
	public:
		string words[2315];
		int freq[5][26];
		int freqTotal[26];
		Data() {
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 26; j++) {
					freq[i][j] = 0;
				}
			}
			for (int i = 0; i < 26; i++) {
				freqTotal[i] = 0;
			}
		}
};

int printData(Data data, char a[26], ostream& outs);
string evalWord(Data data, string word, int& val, int& valNon);

int main() {
	//Open an ifstream connected to the list of words
	ifstream ins;
	ins.open("wordsList.txt");
	if (ins.fail()) {
		cout << "failed" << endl;
		return 1;
	}

	//Opens an ofstream conncted to an empty txt file
	ofstream outs("wordsData.txt");

	//Initializes an array of chars containing the alphabet
	char chars[26];
	for (int i = 0; i < 26; i++) {
		chars[i] = 'a' + i;
	}

	//Initializes a Data object and fills frequency with 0s
	Data res;

	//Initializes an array of all the strings in wordsList.txt
	string input;
	int index = 0;
	while (ins >> input) {
		res.words[index] = input;
		index++;
	}

	for (string str : res.words) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 26; j++) {
				if (str[i] == chars[j]) {
					res.freq[i][j]++;
				}
			}
		}
	}

	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 5; j++) {
			res.freqTotal[i] += res.freq[j][i];
		}
	}

	printData(res, chars, outs);

	int stringSS[2315];
	int stringNSS[2315];
	int maxSS = 0;
	int maxNSS = 0;
	for (int i = 0; i < 2315; i++) {
		evalWord(res, res.words[i], stringSS[i], stringNSS[i]);
		if (stringSS[maxSS] < stringSS[i]) {
			maxSS = i;
		}
		if (stringNSS[maxNSS] < stringNSS[i]) {
			maxNSS = i;
		}
	}
	cout << "    Highest slot specific: " << res.words[maxSS] << " :: " << stringSS[maxSS] << endl;
	cout << "Highest non-slot specific: " << res.words[maxNSS] << " :: " << stringNSS[maxNSS] << endl << endl;


	int ss = 0;
	int nss = 0;
	while (true) {
		string word;
		cout << "Enter a word: ";
		cin >> word;
		cout << evalWord(res, word, ss, nss) << " has a slot specific efficiency of " << ss << endl;
		cout << "  has a non-slot specific efficiency of " << nss << endl << endl;
	}

	return 0;
}

int printData(Data data, char a[26], ostream& outs) {
	int numWidth = 4;

	outs << "char _1_  _2_  _3_  _4_  _5_ " << endl;
	for (int i = 0; i < 26; i++) {
		outs << a[i] << "   ";
		for (int j = 0; j < 5; j++) {
			outs << " " << data.freq[j][i] << " ";
			if (data.freq[j][i] < 100) {
				outs << " ";
				if (data.freq[j][i] < 10) {
					outs << " ";
				}
			}
		}
		outs << endl;
	}

	return 0;
}

string evalWord(Data data, string word, int& val, int& valNon) {
	int duplicate = 6;
	val = 0;
	valNon = 0;
	

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (i != j && word[i] == word[j]) {
				duplicate = j;
			}
		}
	}
	for (int i = 0; i < 5; i++) {
		val += data.freq[i][word[i] - 'a'];
		if (duplicate != i) {
			valNon += data.freqTotal[word[i] - 'a'];
		}
	}

	return word;
}