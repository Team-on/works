#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>

#include <conio.h>

#include <string>
#include <map>

#include <algorithm>

using namespace std;

class Dictionary {
	map <string, string> words;
	
public:

	bool Load(const string &loadPath) {
		ifstream in(loadPath);
		if (!in.is_open())
			return 0;

		pair <string, string> tmp;
		string str;
		while (!in.eof()) {
			getline(in, str);

			tmp.second = str.substr(33);

			str = str.substr(0, 32);
			str.erase(str.find_last_not_of(" \t") + 1, str.length());
			str.erase(0, str.find_first_not_of(" \t"));
			tmp.first = str;

			words.emplace(tmp);	
		}

		in.close();
		return 1;
	}

	bool Save(const string &savePath) const {
		ofstream out(savePath);
		if (!out.is_open())
			return 0;

		string rez = GetAllDictionary();
		out << rez;

		out.close();
		return 1;
	}

	void SetPair(const std::pair<string, string> &dicWord) {
		words[dicWord.first] = dicWord.second;
	}

	const std::map<string, string>::iterator GetPair(const string &lang1) {
		return Find(lang1);
	}

	void Change(std::map<string, string>::iterator wordBefore, const std::pair<string, string> wordAfter) {
		words.erase(wordBefore);
		words.erase(wordAfter.first);
		words[wordAfter.first] = wordAfter.second;
	}

	void Delete(const std::map<string, string>::iterator &word) {
		words.erase(word);
	}

	string GetAllDictionary() const {
		string rez = "";

		for (auto &i : words) {
			rez += i.first;
			for (int j = i.first.length(); j <= 32; ++j)
				rez += ' ';
			rez += i.second + '\n';
		}

		rez.resize(rez.length() - 1);
		rez.shrink_to_fit();

		return rez;
	}
	
private:
	std::map<string, string>::iterator Find(const string &lang1) {
		if (words.find(lang1) == words.end())
			throw exception("Key not found");
		return words.find(lang1);
	}
};

int main(int argc, char ** argv) {
	setlocale(NULL, "RUS");
	atexit([]() {cout << "\n......\nEND...\n......"; _getch(); });

	string DB_PATH = argv[0];
	DB_PATH.resize(DB_PATH.find_last_of('\\') + 1);
	DB_PATH += "dictionary.db";
	DB_PATH.shrink_to_fit();

	Dictionary dictionary;

	dictionary.Load(DB_PATH);

	/*
	dictionary.SetPair({ "hello",  "Привет" });
	dictionary.SetPair({ "hell",   "Ад"     });
	dictionary.SetPair({ "praise", "Слава"  });
	dictionary.SetPair({ "star",   "Звезда" });
	*/

	dictionary.SetPair({ "One",   "1" });
	dictionary.SetPair({ "Two",   "2" });
	dictionary.SetPair({ "Three", "3" });
	dictionary.SetPair({ "For",   "4" });

	try {
		dictionary.Delete(dictionary.GetPair("star"));
	}
	catch (exception) {}

	try {
		dictionary.Change(
			dictionary.GetPair("hell"),
			{ "Hell", "Ад___" }
		);
	}
	catch (exception) {}

	dictionary.Save(DB_PATH);

	cout << dictionary.GetAllDictionary() << endl;

	return EXIT_SUCCESS;
}