/*
Не A+B
Журі захотіло запропонувати задачу на знаходження суми двох чисел. Але в результаті магнітної бурі у програмі перевірки задачі щось зламалось. Усю ніч програмний комітет намагався зрозуміти, що відбулось, і, нарешті, зрозумів. Тепер програма перевірки плутає вердикти, тобто замість "Wrong Answer" система виводить "OK" і навпаки. Весь інший час журі витратило на виправлення цієї помилки, але так і не зуміло виправити її.

Тепер вам потрібно розв'язати трохи іншу задачу про суму двох чисел.

Формат входных данных
У першому і єдиному рядку записано два числа — A та B, які по модулю не перевищують 50.

Формат результата
У першому та єдиному рядку виведіть одне число, яке не дорівнює сумі A та B. Число не повинно перевищувати 100 по модулю.
*/

#include <iostream>
using namespace std;

int main() {
	int a, b;
	cin >> a >> b;
	cout << ~(a + b) % 100;
	return 0;
}