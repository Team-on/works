/*
Гарний рік
Здається, ще зовсім недавно настав новий 2013 рік. А чи знали Ви цікавий факт про те, що 2013 рік є першим роком після далекого 1987 року, в якому всі цифри різні? 
Тепер Вам пропонується розв’язати наступне завдання: заданий номер року y, знайдіть найменший номер року, який строго більше заданого і в якому всі цифри різні.

Формат входных данных
У єдиному рядку задано ціле число y (1000 ≤ y ≤ 9000) - номер року.

Формат результата
Виведіть єдине ціле число - мінімальний номер року, який строго більше y, та у якому всі цифри різні. Гарантується, що відповідь існує.
*/

#include <iostream>
using namespace std;

int main() {
	int r, a1, a2, a3, a4;
	cin >> r;

	while (true) {
		++r;

		a1 = r / 1000;
		a2 = r / 100 % 10;
		a3 = r / 10 % 10;
		a4 = r % 10;

		if (
			a1 != a2 && a1 != a3 && a1 != a4 &&
			a2 != a3 && a2 != a4 &&
			a3 != a4
			)
			break;
	}

	cout << r;
	return 0;
}