//#include <iostream>
//#include <fstream>
//#include <Windows.h>
//using namespace std;
//
//#include <stdio.h>
//#include <curl.h>
//
//#include "Menu.h"
//
//#include "Tree.h"
//#include "Dictionary.h"
//
//void main(int argCnt, char *argVal[]) {
//	//setlocale(0, "RUS");
//	SetConsoleCP(1251);
//	SetConsoleOutputCP(1251);
//
//	Tree <DictionaryWord> tree;
//	//Зчитка з файла
//	{
//		char PATH[_MAX_PATH];
//		strcpy(PATH, argVal[0]);
//		for (int i = strlen(PATH) - 1, cnt = 0; i >= 0; --i) {
//			if (PATH[i] == '\\')
//				++cnt;
//			if (cnt == 2) {
//				strcpy(&PATH[i], "\\dictionaryMy.txt");
//				break;
//			}
//		}
//		
//		ifstream fin(PATH);
//		if (fin.is_open()) {
//			DictionaryWord tmp;
//			while (tmp.ParseDictionaryMy(fin))
//				tree.Add(tmp);
//		}
//		else {
//			cout << "Cant open: " << PATH << endl;
//			system("pause");
//			return;
//		}
//	}
//
//	int menu;
//	do {
//		menu = MenuMode(
//		"Show dic",
//		"Translate word",
//		"Translate text",
//		"Top 3",
//		"UnTop 3",
//		"Exit",
//		""
//		);
//		switch (menu) {
//		case 0:
//			tree.ShowLRoR(); cout << endl;
//			system("pause");
//		break;
//		case 1:
//		{
//			char word[64];
//			cout << "Word: ";
//			cin.getline(word, 63);
//			TreeNode <DictionaryWord>* rez;
//			if ((rez = tree.Find(word)) != nullptr)
//				cout << rez->value << endl;
//			else
//				cout << "Cant find " << word << endl;
//			system("pause");
//		}
//		break;
//		case 2:
//		{
//			//cout << "Input full path to text: ";
//			//char PATH[_MAX_PATH];
//			//cin.getline(PATH, _MAX_PATH - 1);
//
//			CURL *curl;
//			CURLcode res;
//
//			curl_global_init(CURL_GLOBAL_DEFAULT);
//
//			curl = curl_easy_init();
//			if (curl) {
//				curl_easy_setopt(curl, CURLOPT_URL, "https://translate.google.com/?hl=en&tab=TT#en/uk/good%20morning");
//
//				/* Perform the request, res will get the return code */
//				res = curl_easy_perform(curl);
//				/* Check for errors */
//				if (res != CURLE_OK)
//					fprintf(stderr, "curl_easy_perform() failed: %s\n",
//						curl_easy_strerror(res));
//
//				/* always cleanup */
//				curl_easy_cleanup(curl);
//			}
//
//			curl_global_cleanup();
//
//			system("pause");
//		}
//		break;
//		case 3:
//		{
//			DictionaryWord * rez = nullptr;
//			rez = tree.Top3();
//			for (int i = 0; i < 3; ++i)
//				cout << ' ' << rez[i] << endl;
//			delete[] rez;
//			system("pause");
//		}
//		break;
//		case 4:
//		{
//			DictionaryWord * rez = nullptr;
//			rez = tree.UnTop3();
//			for (int i = 0; i < 3; ++i)
//				cout << ' ' << rez[i] << endl;
//			delete[] rez;
//			system("pause");
//		}
//		break;
//		case 5:
//			goto SAVE_AND_EXIT;
//		case -1:
//			return;
//		}
//
//		
//	} while (1);
//
//SAVE_AND_EXIT:
//	//Save file
//	{
//		char PATH[_MAX_PATH];
//		strcpy(PATH, argVal[0]);
//		for (int i = strlen(PATH) - 1, cnt = 0; i >= 0; --i) {
//			if (PATH[i] == '\\')
//				++cnt;
//			if (cnt == 2) {
//				strcpy(&PATH[i], "\\dictionaryMy.txt");
//				break;
//			}
//		}
//
//		ofstream fout(PATH);
//		if (fout.is_open()) {
//			tree.SaveDic(fout);
//			//cout << "Save dic.";
//		}
//		else {
//			cout << "Cant open: " << PATH << endl;
//			system("pause");
//			return;
//		}
//
//	}
//
//	/*
//	Переклад тексту, в кінець топ 3 слів. Все що можу перекласти - заміна, інше - оставити
//	*/
//	system("pause");
//}