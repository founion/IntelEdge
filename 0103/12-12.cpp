#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Words
{
	ifstream fin;
	vector<string> wordVector;
	bool exist(string word);
	void search(string word);
public:
	Words();
	~Words();
	void gamerun();
};

Words::Words() {
	fin.open("words.txt");
	if (!fin) {
		cout << "열기 오류";
		exit(0);
	}

	string word;
	while (getline(fin, word)) {
		wordVector.push_back(word);
	}
	cout << "... words.txt 파일 로딩 완료" << endl;
}

Words::~Words() {
	fin.close();
}

bool Words::exist(string word) {
	for (int i = 0; i < wordVector.size(); i++) {
		if (word == wordVector[i]) return true;
	}
	return false;
}

void Words::search(string word) {
	int len = word.length();
	for (int i = 0; i < wordVector.size(); i++) {
		if (len == wordVector[i].size()) {
			if (word == wordVector[i]) continue;;
			
			for (int j = 0; j < len; j++) {
				string fTmp = word;
				string sTmp = wordVector[i];
				fTmp[j] = '*';
				sTmp[j] = '*';
				if (fTmp == sTmp) cout << wordVector[i] << endl;
			}
		}
	}
}

void Words::gamerun() {
	cout << "검색을 시작합니다. 단어를 입력해 주세요." << endl;
	while (true) {
		cout << "단어>> ";
		string word;
		getline(cin, word);
		
		if (word == "exit") {
			cout << "종료합니다.";
			return;
		}
		if (!exist(word)) cout << "단어 없음. 다시 입력해 주세요." << endl;
		search(word);
	}
}

int main() {
	Words w;
	w.gamerun();
}