#include <iostream>
#include <Windows.h>
#include <ctime>
#include <iomanip>
using namespace std;

class Human{
	char *name;
	int age;
public:
	Human(){
		name = nullptr;
		age = 0;
	}
	Human(const char nameNew[]) : Human(nameNew, 0){ }
	Human(const char nameNew[],const int ageNew){
		name = nullptr;
		SetName(nameNew);
		SetAge(ageNew);
	}
	Human(Human &old) : Human(old.GetName(), old.GetAge()){ }

	~Human(){
		if (name = nullptr)
			delete[] name;
	}

	void SetName(const char nameNew[]){
		if (name != nullptr)
			delete[] name;
		name = new char[strlen(nameNew) + 1];
		strcpy(name, nameNew);
	}
	void SetAge(const int ageNew){
		if (ageNew > 0)
			age = ageNew;
	}

	char* GetName() const{
		return name;
	}
	int GetAge() const{
		return age;
	}

	void Print(){
		if(strlen(name) < 10)
			cout << "Name: " << name << "\t\t" << "Age: " << setw(5) << age;
		else
			cout << "Name: " << name << "\t" << "Age: " << setw(5) << age;
	}
};
class Flat{
	int floor;
	int comnatCnt;
	bool isHabited;
	Human *people;
	int peopleCnt;
public:
	Flat(){ 
		people = nullptr;
	}
	Flat(int floorNew, Human peopleNew[], int peopleCntNew, int comnatCntNew, bool isHabitedNew){
		comnatCnt = comnatCntNew;
		isHabited = isHabitedNew;
		peopleCnt = peopleCntNew;
		floor = floorNew;
		people = new Human[peopleCntNew];
		for (int i = 0; i < peopleCnt && i < 5; i++){
			Human *tmp = new Human (peopleNew[i]);
			people[i] = *tmp;
		}
	}
	Flat(int floorNew, int comnatCntNew, bool isHabitedNew){
		comnatCnt = comnatCntNew;
		isHabited = isHabitedNew;
		peopleCnt = 0;
		floor = floorNew;
		people = nullptr;
	}
	
	Flat(Flat &newf){
		comnatCnt = newf.comnatCnt;
		isHabited = newf.isHabited;
		peopleCnt = newf.peopleCnt;
		floor = newf.floor;
		people = new Human[peopleCnt];
		for (int i = 0; i < peopleCnt && i < 5; i++){
			Human *tmp = new Human(newf.people[i]);
			people[i] = *tmp;
		}
	}
	~Flat() {
		if (people != nullptr)
			delete[] people;
	}
	///*
	void PushBack(Human newHuman){
		Human *tmp = new Human[peopleCnt + 1];
		for (int i = 0; i < peopleCnt; i++){
			Human *tmptmp = new Human(people[i]);
			tmp[i] = *tmptmp;
		}
		tmp[peopleCnt] = newHuman;
		if (people != nullptr)
			delete[] people;
		people = tmp;
		peopleCnt++;
	}
	void Print(){
		cout << "Floor: " << floor << endl;
		cout << "Comnat: " << comnatCnt << endl;
		if (isHabited == 1){
			for (int i = 0; i < peopleCnt && i < 5; i++){
				people[i].Print();
				cout << endl;
			}
		}
	}
};
class BlocksOfFlat{
	Flat flat[50];
	bool isPanel;
	int flatCnt;
public:
	BlocksOfFlat(bool isPanelNew){
		isPanel = isPanelNew;
		flatCnt = 0;
	}

	void SetFlat(Flat flatNew){
		Flat *tmp = new Flat(flatNew);
		flat[flatCnt] = *tmp;
		++flatCnt;
	}

	void Print(){
		cout << ((isPanel) ? "\t\tPanel" :  "\t\tBrick" ) << endl;
	
		for (int i = 0; i < flatCnt && i < 10; i++){
			flat[i].Print();
			cout << endl;
		}
	}
};

void main(){
	srand(time(0));
	BlocksOfFlat house(rand() % 2);
	int currHight = rand() % 15 + 1;
	for (int i = 0; i < currHight; i++){
		if (rand() % 2){
			//Квартира з людьми

			int currNuman = rand() % 5 + 1;
			Flat newFlat(i / 2 + 1, rand() % 3 + 1, 1);
			for (int j = 0; j < currNuman; j++){
				//Генератор имен! 
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
				//Кінець генератора

				Human human(newName, rand() % 40 + 20);
				newFlat.PushBack(human);
			}
			house.SetFlat(newFlat);
		}
		else{
			//Пуста квартира
			Flat newFlat(i / 2 + 1, 0, 0, rand() % 3 + 1, 0);
			house.SetFlat(newFlat);
		}
	}

	house.Print();


	system("pause");
}

















