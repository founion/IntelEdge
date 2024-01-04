#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void fileRead(vector<string>& v, ifstream& fin) {
	string line;
	while (getline(fin, line)) {
		v.push_back(line);
	}
}

void search(vector<string>& v, string word = "=") {
	int index = v[2].find(word);
	if (index != -1) {
		string str = v[2].substr(index + 2, 4);
		if (str.compare("1521") == 0) v[2].replace(index + 2, 4, "3306");
		else if (str.compare("3306") == 0) v[2].replace(index + 2, 4, "1521");
		for (int i = 0; i < v.size(); i++) cout << v[i] << endl;
	}
}

int main() {
	vector<string> wordVector;
	ifstream fin("c:\\temp\\php.ini");
	if (!fin) {
		cout << "열기 오류";
		return 0;
	}
	fileRead(wordVector, fin);
	fin.close();

	string word = "=";
	search(wordVector, word);

}
	