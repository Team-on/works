# Fake3D
 Малювання 3D фігур 2D лініями.

## API
 * **Point3D** - координата в 3 вимірах. Треба для формування всіх інших фігур.
 * **Line3D** - Лінія у просторі
	* **static CalcValues(out double c1, out double q1, out double r1, out double c2, out double q2, out double r2, double a, double b, double c)** - порахувати коєфіцієнти для повороту
	* **Recalc2DLine(double c1, double q1, double r1, double c2, double q2, double r2)** - приймає коєфіцієнти і повертає лінію
 * **Cube3D** - Задається 2 точками і створює лінії які формуватимуть паралелепіпед
 
## План
 * Клас для коєфіцієнтів
 * Менеджер для ліній
 
## Зроблено на
 * С#
 * WPF