/*
Завдання 2. “Кондиціонер” (100 балів)

У класі, де навчається Петрик, установили кондиціонер нового типу. Цей кондиціонер відрізняється особливою простотою в управлінні. У кондиціонера є всього лише два керованих параметри: бажана температура і режим роботи. Кондиціонер може працювати в наступних чотирьох режимах:
- «freeze» - охолодження. У цьому режимі кондиціонер може тільки зменшувати температуру. Якщо температура в кімнаті і так не більше бажаної, то він вимикається.
- «heat» - нагрів. У цьому режимі кондиціонер може тільки збільшувати температуру. Якщо температура в кімнаті і так не менше бажаної, то він вимикається.
- «auto» - автоматичний режим. У цьому режимі кондиціонер може як збільшувати, так і зменшувати температуру в кімнаті до бажаної.
- «fan» - вентиляція. У цьому режимі кондиціонер здійснює тільки вентиляцію повітря і не змінює температуру в кімнаті.
Кондиціонер досить потужний, тому при налаштуванні на правильний режим роботи він за годину доводить температуру в кімнаті до бажаної. Потрібно написати програму, яка по заданій температурі в кімнаті troom, установленими на кондиціонері бажаної температурі tcond і режиму роботи визначає температуру, яка встановиться в кімнаті через годину.

Вимоги до програми
Програма повинна зчитувати вхідні дані із файлу TASK2.DAT. У першому рядку вхідного файлу є два цілих числа troom і tcond, розділених рівно одним пропуском (-50 ≤ troom ≤ 50 , -50 ≤ tcond ≤ 50). У другому рядку є одне слово, записане малими літерами латинського алфавіту – режим роботи кондиціонера.
Результат виконання програми повинен записуватися у вихідний файл TASK2.REZ. Для кожного окремого тесту в одному рядку вказується одне ціле число – температуру, яка встановиться в кімнаті через годину.

Приклади

TASK2.DAT														TASK2.REZ
-----------------------------------------------------------		----------------
 10 20 															20
 heat
-----------------------------------------------------------     ----------------
 10 20 															10
 freeze

Пояснення до прикладів:
У першому прикладі кондиціонер знаходиться в режимі нагріву. Через годину він нагріє кімнату до бажаної температури 20 градусів. У другому прикладі кондиціонер знаходиться в режимі охолодження. Оскільки температура в кімнаті нижча, ніж бажана, кондиціонер самостійно вимикається і температура в кімнаті не поміняється.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
	ifstream fin;
	ifstream check;
	ofstream fout;

	string s;
	int curr, want, an;

	fin.open("TASK2.DAT", ios_base::in);
	check.open("TASK2.REZ", ios_base::in);
	fout.open("TASK22.REZ", ios_base::trunc);


	fin >> curr >> want;
	fin.ignore();
	getline(fin, s);

	an = curr;
	if (s == "heat") {
		if (want > curr)
			an = want;
	}
	else if (s == "freeze") {
		if (want < curr)
			an = want;
	}
	else if (s == "auto") {
		an = want;
	}


	cout << an << endl;
	fout << an << endl;

	check >> an;
	cout << an << endl;

	fin.close();
	fout.close();
	check.close();

	cin >> curr;
	return 0;
}
