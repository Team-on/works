#include "Header.h"

#include "Figures.h"
#include "EquationRoots.h"

char * FindLast(char *str, char sym) {
	for (int i = strlen(str) - 1; i >= 0; --i)
		if (str[i] == sym)
			return &str[i];
	return nullptr;
}

class FileRead {
protected:
	ifstream in;
public:
	FileRead(){}
	FileRead(const char * path) : in(path) { }
	~FileRead() {
		if(in.is_open())
			in.close();
	}

	virtual void SetFile(const char * path) {
		if (in.is_open())
			in.close();
		in.open(path);
	}

	virtual void Display(){
		if (in.is_open()) 
			while (in.peek() != EOF) 
				cout << (char) in.get();
	}
};
class FileAscii : public FileRead {
public:
	FileAscii() { }
	FileAscii(const char * path) : FileRead(path) { }
	
	void Display() {
		if (in.is_open())
			while (in.peek() != EOF)
				cout << in.get() << ' ';
	}
};
class FileBin : public FileRead {
private:
	char *path;

	char xorChar(char a, char b) {
		if (a == b)
			return '0';
		return '1';
	}
public:
	FileBin() {
		path = nullptr;
	}
	FileBin(const char * path) : FileRead(path) {
		this->path = new char[strlen(path) + 1];
		strcpy(this->path, path);
	}
	~FileBin() {
		if (path != nullptr)
			delete[] path;
	}

	void SetFile(const char * path) {
		if (in.is_open())
			in.close();
		if (this->path != nullptr)
			delete[] this->path;

		this->path = new char[strlen(path) + 1];
		strcpy(this->path, path);
		in.open(path);
	}

	void Display() {
		if (in.is_open()) 
			while (in.peek() != EOF) {
				char str[9];
				itoa(in.get(), str, 2);
				cout << str << ' ';
			}
	}

	bool Crypr(const char *key) {
		if (!in.is_open())
			return 0;
		
		char *path = new char[strlen(this->path) + 4];
		strcpy(path, this->path);
		char *p = FindLast(path,'.');
		strcpy(p, "crp.txt");
		
		ofstream out(path);
		if (!out.is_open()) {
			delete[] path;
			return 0;
		}

		char keyPos = 0;
		in.seekg(0);
		while (in.peek() != EOF) {
			char str[9] = { 0 };
			itoa(in.get(), str, 2);
			if (strlen(str) < 7) {
				int i = strlen(str);
				while (i < 7) {
					for (char j = 6; j >= 0; --j)
						str[j] = str[j - 1];
					str[0] = '0';
					++i;
				}
			}

			for (char i = 0; i < strlen(str); ++i) {
				str[i] = xorChar(str[i], key[keyPos++]);
				if (keyPos == strlen(key))
					keyPos = 0;
			}
	
			out << str;
		}

		out.close();
		delete[] path;
		return 1;
	}
	bool UnCrypr(const char *key) {
		if (!in.is_open())
			return 0;

		char *path = new char[strlen(this->path) + 3];
		strcpy(path, this->path);
		char *p = FindLast(path, '.');
		strcpy(p, "un.txt");

		ofstream out(path);
		if (!out.is_open()) {
			delete[] path;
			return 0;
		}

		char keyPos = 0;
		in.seekg(0);

		while (in.peek() != EOF) {
			char str[9] = {0};
			for (char i = 0; i < 7; ++i)
				in >> str[i];
			
			if (strcmp(str, "0000000") == 0)
				break;

			for (char i = 0; i < strlen(str); ++i) {
				str[i] = xorChar(str[i], key[keyPos++]);
				if (keyPos == strlen(key))
					keyPos = 0;
			}
			
			char sym = 0;
			for (char i = 0; i < 7; ++i) {
				sym = sym * 2 + str[i] - '0';
			}

			out << sym;
		}

		out.close();
		delete[] path;
		return 1;
	}
};

/*
—оздайте иерархию классов по работе с файлами. Ѕазовый
класс умеет открывать файл и отображать его содержи-
мое в консоль, первый класс потомка открывает файл
и†отображает содержимое в виде ASCII-кодов символов,
расположенных в файле, второй класс потомка открывает
файл и показывает его содержимое в двоичном виде и т.д.
ƒл€ отображени€ содержимого файла в базовом классе
определена виртуальна€ функци€
Х	 void Display(const char * path);
Х	 path Ч путь к файлу.
ѕотомки создают свою реализацию виртуальной функции.

Ўифруванн€ дл€ FileBin
*/

int main(int argc, char ** argv) {
	atexit([]() {
		cout << "\nEND...";
		_getch();
	});
	srand(time(0));

	//----------------------------- FileRead ----------------------------------------
	/*
	char PATH[_MAX_PATH];
	strncpy(PATH, argv[0], _MAX_PATH);
	char *p = FindLast(PATH, '\\');
	strcpy(p + 1, "text.txt");

	FileRead *fr[] = { new FileRead(),  new FileAscii(), new FileBin() };
	const unsigned short frSize = sizeof(fr) / sizeof(fr[0]);

	for(int i = 0; i < frSize; ++i)
		fr[i]->SetFile(PATH);

	for (int i = 0; i < frSize; ++i) {
		fr[i]->Display();
		cout << endl;
	}
	
	FileBin *fBin = (FileBin*) fr[2];

	char pass[40];
	cout << "Input password (0 and 1): ";
	cin.getline(pass, 39);
	fBin->Crypr(pass);

	cout << "Input password (0 and 1): ";
	cin.getline(pass, 39);
	strcpy(p + 1, "textcrp.txt");
	fBin->SetFile(PATH);
	fBin->UnCrypr(pass);

	for(char i = 0; i < 3; ++i)
		delete fr[i];
	*/

	//----------------------------- EquationRoots --------------------------------------
	/*
	EquationBasic *Eq[2] = { new LinearEquation, new SqrEquation };

	for (char i = 0; i < 2; ++i) {
		Eq[i]->CinValue();
		EquationRoots rezult = Eq[i]->GetRoot();
		cout << "Roots: ";
		rezult.Show();
		cout << endl << endl;
	}

	for (char i = 0; i < 2; ++i)
		delete Eq[i];
	*/

	//----------------------------- Shape ----------------------------------------
	/*
	unsigned short shapeArrSize = 10;
	Shape **shapeArr = new Shape*[shapeArrSize];

	for (unsigned short i = 0; i < shapeArrSize; ++i) {
		char fig = rand() % 4;
		if (fig == 0) {
			Square *tmp = new Square;
			tmp->SetLeftUpPoint({rand() % 10, rand() % 10});
			tmp->SetSide(rand() % 10 + 1);
			shapeArr[i] = tmp;
		}
		else if (fig == 1) {
			Rectangle *tmp = new Rectangle;
			tmp->SetLeftUpPoint({ rand() % 10, rand() % 10 });
			tmp->SetSide({ rand() % 10 + 1, rand() % 10 + 1 });
			shapeArr[i] = tmp;
		}
		else if (fig == 2) {
			Ellipse *tmp = new Ellipse;
			tmp->SetLeftUpPoint({ rand() % 10, rand() % 10 });
			tmp->SetSide({ rand() % 10 + 1, rand() % 10 + 1 });
			shapeArr[i] = tmp;
		}
		else {
			Circle *tmp = new Circle;
			tmp->SetCenter({ rand() % 10, rand() % 10 });
			tmp->SetR(rand() % 10 + 1);
			shapeArr[i] = tmp;
		}
	}

	ofstream fout("shape.txt");
	if (!fout.is_open()) {
		cout << "Cant open shape.txt (write)\n";
		exit(EXIT_FAILURE);
	}

	fout << shapeArrSize << endl;

	for (unsigned short i = 0; i < shapeArrSize; ++i)
		shapeArr[i]->Save(fout);
	fout.close();
	for (unsigned short i = 0; i < shapeArrSize; ++i)
		delete shapeArr[i];
	delete[] shapeArr;

	Shape **shapeArrCopy = nullptr;

	{
		ifstream fin("shape.txt");

		fin >> shapeArrSize; fin.ignore();

		shapeArrCopy = new Shape*[shapeArrSize];

		unsigned short i = 0;
		for (; !fin.eof(); ++i) {
			char currShape[33];
			fin.getline(currShape, 32);

			if (!strcmp(currShape, "Square:")) {
				Square *tmp = new Square;
				tmp->Load(fin);
				shapeArrCopy[i] = tmp;
			}
			else if (!strcmp(currShape, "Rectangle:")) {
				Rectangle *tmp = new Rectangle;
				tmp->Load(fin);
				shapeArrCopy[i] = tmp;
			}
			else if (!strcmp(currShape, "Circle:")) {
				Circle *tmp = new Circle;
				tmp->Load(fin);
				shapeArrCopy[i] = tmp;
			}
			else if (!strcmp(currShape, "Ellipse:")) {
				Ellipse *tmp = new Ellipse;
				tmp->Load(fin);
				shapeArrCopy[i] = tmp;
			}
			fin.ignore();
		}

		fin.close();
	}

	for (unsigned short i = 0; i < shapeArrSize; ++i)
		shapeArrCopy[i]->Show();
	
	for (unsigned short i = 0; i < shapeArrSize; ++i)
		delete shapeArrCopy[i];
	delete[] shapeArrCopy;
	*/

	return EXIT_SUCCESS;
}


