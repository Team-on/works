#include "Inc.h"
#include "Person.h"


template <typename T>
void ArrPushBack(T *&arr, usi &size) {
	T *tmp = new T[size + 1];

	for (usi i = 0; i < size; i++)
		tmp[i] = arr[i];
	
	arr = tmp;
	++size;
}
template <typename T>
void ArrDeleteByIndex(T *&arr, usi &size, const usi &index) {
	usi j = 0;
	T *tmpArr = new T[j];

	for (int i = 0; i < size; i++) {
		if (i != index) {
			ArrPushBack(tmpArr, j);
			tmpArr[j - 1] = arr[i];
		}
	}
	arr = tmpArr;
	size = j;
}



void main() {
	usi prsSize = 0;
	Person *prs = new Person[prsSize];

	int menu;
	do {
		Person::GetCnt();
		cout << "[1] - Add" << endl;
		cout << "[2] - Del" << endl;
		cout << "[3] - Rename" << endl;
		cout << "[4] - Show" << endl;
		cout << "[0] - Exit" << endl;
		do {
			cin >> menu;
		} while (menu < 0 || menu > 4);
		system("cls");

		switch (menu) {
		case 1:
		{
			char name[32], surname[32];
			int age;
			ArrPushBack(prs, prsSize);

			cout << "Name: ";
			cin >> name;
			cout << "Surname: ";
			cin >> surname;
			cout << "Age: ";
			cin >> age;

			prs[prsSize - 1].GetAll(name, surname, age);
			system("cls");
		}
		break;
		case 2:
		{
			int ID;
			for (usi i = 0; i < prsSize; i++) {
				cout << "ID: " << i + 1 << endl;
				prs[i].Show();
				cout << endl;
			}
			cout << endl << "Input ID(0 - exit): " << endl;
			do {
				cin >> ID;
			} while (ID < 0 || ID >= prsSize);
			
			if (ID != 0) {
				ID--;
				ArrDeleteByIndex(prs, prsSize, ID);
			}

			system("cls");
		}
		break;
		case 3:
		{
			int ID;
			for (usi i = 0; i < prsSize; i++) {
				cout << "ID: " << i + 1 << endl;
				prs[i].Show();
				cout << endl;
			}
			cout << endl << "Input ID(0 - exit): " << endl;
			do {
				cin >> ID;
			} while (ID < 0 || ID >= prsSize);

			if (ID != 0) {
				ID--;
				char name[32], surname[32];
				cout << "New name: ";
				cin >> name;
				cout << "New surname: ";
				cin >> surname;
				prs[ID].Rename(name, surname);
			}

			system("cls");
		}
		break;
		case 4:
			for (usi i = 0; i < prsSize; i++) {
				prs[i].Show();
				cout << endl;
			}
		break;
		}

	} while (menu != 0);

}

