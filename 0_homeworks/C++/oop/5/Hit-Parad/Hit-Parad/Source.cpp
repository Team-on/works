#include <iostream>
#include <fstream>

using namespace std;



class Person{
public:
	int *marks;
	static int mCnt;
public:
	Person(){
		int m = mCnt;
		marks = new int[m];
	}
	~Person(){
		if (marks != nullptr)
			delete[] marks;
	}


	bool Same(Person &sec){
		int * inv = new int[mCnt];
		for (int i = 0; i < mCnt; i++)
			inv[marks[i]] = sec.marks[i];

		for (int i = 0; i < mCnt; i++)
			for (int j = i + 1; j < mCnt; j++)
			if (!(inv[i] > inv[j])){
				delete[] inv;
				return 0;
			}

		delete[] inv;
		return 1;
	}
	int Inversed(Person &sec){
		int * inv = new int[mCnt];
		int invCnt = 0;
		for (int i = 0; i < mCnt; i++)
			inv[marks[i]] = sec.marks[i];

		for (int i = 0; i < mCnt; i++)
			for (int j = i + 1; j < mCnt; j++)
				if (inv[i] > inv[j])
					++invCnt;

		/*for (int i = 0; i < mCnt; i++){
			int currPos = marks[i];
			for (int j = 0; j < mCnt; j++){
				if (currPos < j &&
					sec.marks[currPos] < sec.marks[j]
					)
					++invCnt;
			}
		}
		*/
		delete[] inv;
		return invCnt;
	}

};



class HitParad{
public:
	Person *viever;
	int pCnt;
public:
	HitParad(){
		viever = nullptr;
		pCnt = 0;
	}
	~HitParad(){
		if (viever != nullptr)
		delete[] viever;
	}

	void Read(char path[] = nullptr){
		if (viever != nullptr)
			delete[] viever;

		ifstream fin;
		if (path != nullptr)
			fin.open(path);
		if (fin.is_open()){
			if (fin.peek() == '#'){
				//char tmp[1];
				//fin.getline(tmp, 1);
			}
			else {
				fin >> pCnt >> Person::mCnt;
				viever = new Person[pCnt];
				for (int i = 0; i < HitParad::pCnt; i++){
					int idCurr;
					fin >> idCurr;
					--idCurr;
					for (int j = 0; j < Person::mCnt; j++){
						fin >> viever[idCurr].marks[j];
						viever[idCurr].marks[j] = viever[idCurr].marks[j] - 1;
					}
				}
			}
		}
		else{
			cin >> pCnt >> Person::mCnt;
			viever = new Person[pCnt];
			for (int i = 0; i < HitParad::pCnt; i++){
			int idCurr;
			cin >> idCurr;
			--idCurr;
			for (int j = 0; j < Person::mCnt; j++){
				cin >> viever[idCurr].marks[j];
				viever[idCurr].marks[j] = viever[idCurr].marks[j] - 1;
			}
		}
		}
	}

	int GetMostInversed(int id, int &invCnt, int print = 1, char path[] = nullptr){
		if (id < 0 || id >= HitParad::pCnt)
			return -2;
		int curr = 0, min = INT_MAX;
		int idSim = 0;

		ofstream fout;
		if (path != nullptr)
			fout.open(path);

		for (int i = 0; i < HitParad::pCnt; i++){
			if (i != id){
				curr = viever[id].Inversed(viever[i]);
				if (curr < min){
					min = curr;
					idSim = i;
				}
			
			if (print == 1)
				cout << i + 1 << ends << curr << endl;
			else if (print == 2)
				if (fout.is_open())
					fout << i + 1 << ends << curr << endl;
			}
		}
		invCnt = min;
		return idSim + 1;
	}
	int GetInversion(int id1, int id2){
		if ((id1 < 0 || id1 >= HitParad::pCnt) &&
			(id2 < 0 || id2 >= HitParad::pCnt)
			)
			return -2;
		return viever[id1].Inversed(viever[id2]);
	}

	void Same(){
		for (int i = 0; i < pCnt / 2; i++)
			for (int j = pCnt / 2; j < pCnt; j++)
				if (i != j && viever[i].Same(viever[j]))
					cout << i + 1 << ends << j + 1 << endl;
	}
};

int Person::mCnt = 0;

void main(int argc, char ** argv){

	HitParad cinema;

	cinema.Read("D:\\Timofei_Solonchuk\\Homeworks\\5\\Hit-Parad\\Debug\\input_1000_5.txt");

	//int cnt = 0, id;
	//cout << "ID: ";
	//cin >> id;
	//--id;
	//int tmp = cinema.GetMostInversed(id, cnt);
	//cout << endl << tmp << ends << cnt << endl;


	int id1, id2;
	//cout << "ID: ";
	//cin >> id1 >> id2;
	//--id1; --id2;

	for (int i = 0; i < cinema.pCnt / 2; i++)
	for (int j = cinema.pCnt / 2; j < cinema.pCnt; j++)
		if ( i != j && cinema.GetInversion(i, j) == 0)
			cout << i + 1 << ends << j + 1 << endl;
	//cinema.Same();
		
	

	



	system("pause");
}








