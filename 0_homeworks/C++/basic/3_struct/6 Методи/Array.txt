
int* FoundInMtx(char arr[22][22], char fnd) {
	int *pos = new int[2];
	pos[0] = pos[1] = -1;

	for (usi i = 0; i < 22; i++)
		for (usi j = 0; j < 22; j++)
			if (fnd == arr[i][j]) {
				pos[0] = i;
				pos[1] = j;
				return pos;
			}
#include <iostream>
#include <ctime>
#include "Array.h"
using std::cout;
using std::cin;
using std::endl;
using std::ends;
#define usi unsigned short int

template <typename T>
class Array{
private:
	unsigned short int size;
	T* arr;
public:
	Array(const usi &s) {
		size = s;
		arr = new T[s];
		for (usi i = 0; i < size; i++)
			arr[i] = 0;
	}
	~Array() {
		delete[] arr;
	}

	void Set(usi pos, T zn) {
		if (pos >= 0 && pos < size) {
			arr[pos] = zn;
		}
	}
	T Get(usi pos) {
		if (pos >= 0 && pos < size)
			return arr[pos];
		return 0;
	}

	void Rand(const T &left = 0, const T &right = 10) {
		for (usi i = 0; i < size; i++)
			arr[i] = rand() % (abs(left) + abs(right)) + left;
	}
	void Print() {
		for (usi i = 0; i < size; i++)
			cout << arr[i] << ends;
		cout << endl;
	}

	T Sum() {
		int sum = 0;
		for (usi i = 0; i < size; i++)
			sum += arr[i];
		return sum;
	}
	T Min() {
		int min = 0;
		for (usi i = 1; i < size; i++)
			if (arr[min] > arr[i])
				min = i;
		return min;
	}
	T Max(){
		int max = 0;
		for (usi i = 1; i < size; i++)
			if (arr[max] < arr[i])
				max = i;
		return max;
	}

};

void main(){
	srand(time(0));
	Array <int> arr(20);
	//arr.Print();
	//arr.Rand();
	for(usi i = 0; i < 20; i++)
		arr.Print();

	cout << "Min: " << arr.Get( arr.Min() ) << endl;
	cout << "Max: " << arr.Get( arr.Max() ) << endl;
	cout << "Sum: " << arr.Sum() << endl;
}
	return pos;
}

//таку же для всіх інпутів.
int PlayerInputBattle(int scene, Mob player, char arr[22][22]) {
	
	return 1;
}

//0 - Живий, 1 - мертвий, 2 - втік
int BattleField(Mob &player, Mob &enemy) {
	char arr[22][22];
	for (usi i = 0; i < 22; i++) {
		for (usi j = 0; j < 22; j++) {
			arr[i][j] == ' ';
		}
	}
	//Y X
	usi posPlayer[2] = { 11, 11 };
	//Y X
	usi posEnemy[2];
	for (usi i = 0; i < 22; i++)
		for (usi j = 0; j < 22; j++)
			if (i == 0 || j == 0 || i == 21 || j == 21)
				arr[i][j] = ':';
	
	do {
		posEnemy[0] = rand() % 20 + 1;
		posEnemy[1] = rand() % 20 + 1;
	} while (posEnemy[0] == 11 && posEnemy[1] == 11);
	arr[posPlayer[0]][posPlayer[1]] = '@';
	arr[posEnemy[0]][posEnemy[1]] = 'G';

	char input;
	while (player.HPCurrent > 0 && enemy.HPCurrent > 0) {
		for (usi i = 0; i < 22; i++) {
			for (usi j = 0; j < 22; j++) {
				cout << arr[i][j] << ends;
			}
			cout << endl;
		}

REPEAT_INPUT_MAN:
		cout << ">";
		input = getch();
		cout << input << endl;

		switch (input) {
		case 'w': case 'a': case 's': case 'd':
		{
			if (arr[posPlayer[0] - 1][posPlayer[1]] == ' ') {
				arr[posPlayer[0]][posPlayer[1]] = ' ';
				posPlayer[0]--;
				arr[posPlayer[0]][posPlayer[1]] = '@';

			}
			cout << posPlayer[0] << ends << posPlayer[1] << endl;
		}
		break;
		case '?':
			cout << "(wasd) - рух" << endl;
			cout << "Вибрати атаку по замовчуванню" << endl;
			cout << "ijkl атака по замовчуванню в Н сторону " << endl;
			cout << "ИД скила - использовать скил. А потім ijkl" << endl;
			goto REPEAT_INPUT_MAN;
		}

		
	}

	
	return 0;
}