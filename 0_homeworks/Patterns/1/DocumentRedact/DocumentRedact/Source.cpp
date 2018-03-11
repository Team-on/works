#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

enum DocumentType{id_Text, id_jpg, id_DOC_END};

class ADocumentRedactor {
protected:
	string path;
public:
	virtual void Create(string &path) = 0;
	virtual void Open(string &path) = 0;
	virtual void Save() = 0;
	virtual void SaveAs(string& newName) = 0;
	virtual void Print(ostream &out) = 0;
	virtual void Close() = 0;
	virtual ~ADocumentRedactor() {};

	static ADocumentRedactor* CreateDocument(DocumentType id);
};

class TextRedactor : public ADocumentRedactor {
	fstream file;
public:
	void Create(string &path) {
		/*bool rez;
		ofstream out(path);
		rez = out.is_open();
		out.close();
		return rez;*/
		cout << "TextRedactor::Create" << endl;
	}
	void Open(string &path) {
		//file.open(path);
		//return file.is_open();
		cout << "TextRedactor::Open" << endl;
	}
	void Save() {
		cout << "TextRedactor::Save" << endl;
	}
	void SaveAs(string& newName) {
		cout << "TextRedactor::SaveAs" << endl;
	}
	void Print(ostream &out) {
		//file.seekg(0);
		//while(!file.eof())
		//	out << file.get();
		cout << "TextRedactor::Print" << endl;
	}
	void Close() {
		//file.close();
		//return !file.is_open();
		cout << "TextRedactor::Close" << endl;
	}
	~TextRedactor() {
		//file.close();
	}
};

class JPGRedactor : public ADocumentRedactor {
public:
	void Create(string &path) {
		/*bool rez;
		ofstream out(path);
		rez = out.is_open();
		out.close();
		return rez;*/
		cout << "JPGRedactor::Create" << endl;
	}
	void Open(string &path) {
		//file.open(path);
		//return file.is_open();
		cout << "JPGRedactor::Open" << endl;
	}
	void Save() {
		cout << "JPGRedactor::Save" << endl;
	}
	void SaveAs(string& newName) {
		cout << "JPGRedactor::SaveAs" << endl;
	}
	void Print(ostream &out) {
		//file.seekg(0);
		//while(!file.eof())
		//	out << file.get();
		cout << "JPGRedactor::Print" << endl;
	}
	void Close() {
		//file.close();
		//return !file.is_open();
		cout << "JPGRedactor::Close" << endl;
	}
	~JPGRedactor() {
		//file.close();
	}
};

ADocumentRedactor* ADocumentRedactor::CreateDocument(DocumentType id) {
	switch (id){
	case id_Text:
		return new TextRedactor;
	case id_jpg:
		return new JPGRedactor;
	default:
		throw exception("Unknown id in ADocumentRedactor::CreateDocument");
	}
}

/*
Спроектировать универсальный каркас многодокументного
редактора. Редактор должен представлять основные функции ра-
боты с документом:
1. Создание.
2. Открытие.
3. Сохранение.
4. Сохранение под новым именем.
5. Печать.
6. Закрытие.
Предложенный объектно-ориентированный дизайн каркаса
редактора должен без изменений использоваться для разработки
редакторов документов различных типов.
*/
int main(int argc, char ** argv) {
	srand(time(NULL));
	atexit([]() {system("pause"); });
	vector <ADocumentRedactor*> documents;
	for(char i = 0; i < 20; ++i)
		documents.push_back(ADocumentRedactor::CreateDocument( DocumentType(rand() % DocumentType::id_DOC_END)) );
	for (auto &i : documents)
		i->Save();

	return EXIT_SUCCESS;
}