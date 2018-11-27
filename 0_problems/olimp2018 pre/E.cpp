/*
Гра з палочками
Переможці International Olympiad in Informatics 2017 року Akshat і Malvika, завоювавши золото і срібло відповідно, захотіли трохи розважитися. Зараз вони зайняті грою на сітці, складеної з n горизонтальних і m вертикальних паличок. Точкою перетину на сітці називається будь-яка точка сітки, утворена перетином однієї з горизонтальних і однієї з вертикальних паличок. На сітці, показаній нижче, n = 3 і m = 3. Сітка утворена n + m = 6 паличками (вертикальні палички виділені зеленим кольором, а горизонтальні - червоним кольором). На сітці є n * m = 9 точок перетину, які пронумеровані від 1 до 9.


Правила гри дуже прості. Гравці ходять по черзі. Akshat завоював золото, тому він робить перший хід. На своєму ході гравець повинен вибрати будь-яку точку перетину, що залишилася, а потім видалити з сітки всі палички, які проходять через цю точку. Гравець програє, якщо не може зробити хід (на сітці не залишилося точок перетину). Припустимо, що обидва гравці грають оптимально. Хто переможе в грі?

Формат входных данных
Перший рядок містить два цілих числа через пробіл, n і m (1 ≤ n, m ≤ 100).

Формат результата
Виведіть "Akshat" або "Malvika" (без лапок), в залежності від того, хто переможе при оптимальній грі.

Примеры
*/

#include <iostream>
using namespace std;

int main() {
	int a, b;
	cin >> a >> b;

	if(a * b == 1)
		cout << "Akshat";

	else if ((a * b) % 2 == 0)
		cout << "Malvika";
	else 
		cout << "Akshat";
	 
	return 0;
}