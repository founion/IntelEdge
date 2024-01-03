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
		cout << "���� ����";
		exit(0);
	}

	string word;
	while (getline(fin, word)) {
		wordVector.push_back(word);
	}
	cout << "... words.txt ���� �ε� �Ϸ�" << endl;
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
	cout << "�˻��� �����մϴ�. �ܾ �Է��� �ּ���." << endl;
	while (true) {
		cout << "�ܾ�>> ";
		string word;
		getline(cin, word);
		
		if (word == "exit") {
			cout << "�����մϴ�.";
			return;
		}
		if (!exist(word)) cout << "�ܾ� ����. �ٽ� �Է��� �ּ���." << endl;
		search(word);
	}
}

int main() {
	Words w;
	w.gamerun();
}