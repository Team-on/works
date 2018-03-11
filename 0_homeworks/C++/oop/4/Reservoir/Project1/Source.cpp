#include <iostream>
#include <fstream>
#include <time.h>
#include <Windows.h>
#include <conio.h>

using namespace std;

enum ReservoirTypes{Sea = 1, Pool, Pryd};

class Reservoir{
private:
	char *name;

	int x, y, z;

	// 1 - Sea, 2 - Pool, 3 - Pryd
	int type;
public:
	explicit Reservoir(){
		name = nullptr;
		x = y = z = type = 0;
	}
	explicit Reservoir(char Name[], int X, int Y, int Z, int Type) {
		x = X;
		y = Y;
		z = Z;
		type = Type;
		name = new char[strlen(Name) + 1];
		strcpy(name, Name);
	}
	explicit Reservoir(Reservoir &cpy){
		Copy(cpy);
	}
	~Reservoir(){
		if (name != nullptr)
			delete[] name;
	}

	void Copy(Reservoir &cpy){
		if (name != nullptr)
			delete[] name;
		if (cpy.name != nullptr){
			name = new char[strlen(cpy.name) + 1];
			strcpy(name, cpy.name);
		}
		else{
			name = nullptr;
		}

		x = cpy.x;
		y = cpy.y;
		z = cpy.z;
		type = cpy.type;
	}

	long long V() const{
		return S() * z;
	}
	long long S() const{
		return x * y;
	}
	bool TypeCmp(Reservoir &second) const{
		if (type != second.type)
			return 0;
		return 1;
	}
	int SCmp(Reservoir &second) const{
		if (S() < second.S())
			return 1;
		if (S() > second.S())
			return -1;
		return 0;
	}

	void Print() const{
		if (type == Sea){
			cout << "Sea ";
		}
		else if (type == Pool){
			cout << "Pool ";
		}
		else if (type == Pryd){
			cout << "Pryd ";
		}
		cout << name << endl;
		cout << x << " " << y << " " << z << endl;
	}

	void DBSave(ofstream &fout){
		fout << name << endl;
		fout << x << " " << y << " " << z << " " << type << endl;
	}
	void DBRead(ifstream &fin){
		char tmp[200];
		fin.getline(tmp, 199);
		//fin.ignore();
		name = new char[strlen(tmp) + 1];
		strcpy(name, tmp);
		fin >> x >> y >> z >> type;
		fin.ignore();
	}
};

class Gidro{
private:
	Reservoir * res;
	int sizeCurr, sizeMax;

	char *GetLast(char str[], char sym = '\\'){
		for (int i = strlen(str) - 1; i >= 0; i--) 
			if (str[i] == sym) 
				return &str[i];
	}

public:
	Gidro(){
		res = nullptr;
		sizeMax = 0;
		sizeCurr = 0;
	}
	~Gidro(){
		if (res != nullptr)
			delete[] res;
	}

	void PushBack(Reservoir &Res){
		if (sizeCurr + 1 > sizeMax){
			Reservoir *tmp = new Reservoir[sizeMax + 3];
				for (int i = 0; i < sizeCurr; i++){
					tmp[i].Copy(res[i]);
				}
				if (res != nullptr)
					delete[] res;
				res = tmp;
				sizeMax += 3;
		}
		res[sizeCurr].Copy(Res);
		sizeCurr++;
	}

	//TODO:
	//DeleteById
	//Change res
	void DeleteById(int Id){
		for (int i = Id; i < sizeCurr - 1; i++)
			res[i] = res[i + 1];
		--sizeCurr;
	}

	void DBSave(char db[], char argv0[]){
		char path[_MAX_PATH];
		strcpy(path, argv0);
		char *p = GetLast(path);
		p[1] = '\0';
		strcat(p, db);
		ofstream fout(path);
		if (fout.is_open()){
			fout << sizeCurr << endl;
			for (int i = 0; i < sizeCurr; i++)
				res[i].DBSave(fout);
			fout.close();
		}
		else{
			cout << "Cant open " << path << endl;
		}
	}
	void DBRead(char db[], char argv0[]){
		char path[_MAX_PATH];
		strcpy(path, argv0);
		char *p = GetLast(path);
		p[1] = '\0';
		strcat(p, db);
		ifstream fin(path);
		if (fin.is_open()){
			fin >> sizeCurr;
			fin.ignore();
			sizeMax = sizeCurr;
			res = new Reservoir[sizeCurr];
			for (int i = 0; i < sizeCurr; i++)
				res[i].DBRead(fin);
			fin.close();
		}
		else{
			cout << "Cant read from " << path << endl;
		}
	}

	void Print(){
		for (int i = 0; i < sizeCurr; i++){
			cout << i << " ";
			res[i].Print(); cout << endl;
			cout << "S: " << res[i].S() << endl;
			cout << "V: " << res[i].V() << endl;
			cout << "------------------" << endl;
		}
	}

	bool TypeCmp(Reservoir &res1, Reservoir &res2){
		return res1.TypeCmp(res2);
	}
	int SCmp(Reservoir &res1, Reservoir &res2){
		return res1.SCmp(res2);
	}

	Reservoir * GetResI(int i){
		if (i >= 0 && i < sizeCurr)
			return &res[i];
		return nullptr;
	}
};


void main(int argc, char **argv){
	srand(time(NULL));
	Gidro water;

	water.DBRead("gidro", argv[0]);

	char menu;
	do{
		cout << "[1, a] - Add rand" << endl;
		cout << "[2, p] - Print" << endl;
		cout << "[3, s] - S cmp" << endl;
		cout << "[4, t] - Type cmp" << endl;
		cout << "[0, e] - Exit & Save" << endl;
		menu = getch();
		menu = tolower(menu);
		system("cls");

		switch (menu){

		case '3': case 's':
		case '4': case 't':
		{
			int id1, id2;
			cout << "ID 1: "; cin >> id1;
			cout << "ID 2: "; cin >> id2;

			Reservoir *res1 = water.GetResI(id1), *res2 = water.GetResI(id2);

			if (res1 == nullptr || res2 == nullptr){
				cout << "Cant foud id ";
				if (res1 == nullptr)
					cout << id1 << " ";
				if (res2 == nullptr)
					cout << id2 << " ";
				cout << endl;
				break;
			}

			if (menu == '3' || menu == 's'){
				int result = water.SCmp(*res1, *res2);
				cout << (result?((result == 1)?"S1 < S2":"S1 > S2"):"S1 == S2") << endl;
			}
			if (menu == '4' || menu == 't'){
				bool result = water.TypeCmp(*res1, *res2);
				cout << (result ? "Same type" : "Different type") << endl;
			}
			
		}
		break;
		case '2': case 'p':
			water.Print();
		break;
		case '1': case 'a':
			int size = rand() % 5 + 2;
			for (int i = 0; i < size; i++){
				char golosni[] = "aaaeeeiiouyy";
				char prigolosni[] = "bbbcdddffgghjkllmmmnnnppqrrssstttvwxz";
				char newName[40] = "";
				char nameLenght = rand() % 10 + 2;
				bool isprigolosna = 1;
				for (int i = 0; i < nameLenght; i++) {
					if (isprigolosna == 1) {
						if (rand() % 100 < 10) {
							strncat(newName, &prigolosni[rand() % 37], 1);
							strncat(newName, &prigolosni[rand() % 37], 1);
							i++;
						}
						else {
							strncat(newName, &prigolosni[rand() % 37], 1);
						}
						isprigolosna = 0;
					}
					else {
						if (rand() % 100 < 10) {
							strncat(newName, &golosni[rand() % 12], 1);
							strncat(newName, &golosni[rand() % 12], 1);
							i++;
						}
						else {
							strncat(newName, &golosni[rand() % 12], 1);
						}
						isprigolosna = 1;
					}
				}
				newName[0] = toupper(newName[0]);
				int type = rand() % 3 + 1;
				if (type == Sea){
					Reservoir n(newName, rand() % 9000 + 1000, rand() % 9000 + 1000, rand() % 2000 + 1000, type);
					water.PushBack(n);
				}
				else if (type == Pool){
					Reservoir n(newName, rand() % 100 + 50, rand() % 100 + 500, rand() % 10 + 1, type);
					water.PushBack(n);
				}
				else if (type == Pryd){
					Reservoir n(newName, rand() % 50 + 10, rand() % 50 + 10, rand() % 5 + 1, type);
					water.PushBack(n);
				}
			}
		break;
		}

	} while (menu != '0' && menu != 'e');

	water.DBSave("gidro", argv[0]);
	system("pause");
}







