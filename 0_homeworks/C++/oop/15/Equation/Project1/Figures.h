#ifndef _FIGURES_H_
#define _FIGURES_H_

#include "Header.h"
#include "coord.h"

/*
—оздайте абстрактный класс Shape дл€ рисовани€ плоских
фигур. ќпределите виртуальные методы:
Х	 Show() Ч вывод на экран информации о фигуре,
Х	 Save() Ч сохранение фигуры в файл,
Х	 Load() Ч считывание фигуры из файла.
ќпределите производные классы:
Х	 Square Ч квадрат, который характеризуетс€ коорди-
натами левого верхнего угла и длиной стороны;
Х	 Rectangle Ч пр€моугольник с заданными координатами
верхнего левого угла и размерами;
Х	 Circle Ч окружность с заданными координатами цен-
тра и радиусом;
Х	 Ellipse Ч эллипс с заданными координатами верхнего
угла описанного вокруг него пр€моугольника со сто-
ронами, параллельными ос€м координат, и размерами
этого пр€моугольника.
—оздайте массив фигур, сохраните фигуры в файл, загру-
зите в другой массив и отобразите информацию о†каждой
из фигур.
*/

class Shape {
public:
	virtual void Show() = 0;
	virtual void Save(ofstream &out) = 0;
	virtual void Load(ifstream &in) = 0;
};

class Square : public Shape {
	coord leftUpPoint;
	short side;
public:
	Square();

	void SetLeftUpPoint(coord LeftUpPoint);
	void SetSide(short Side);

	void Show() const;

	void Save(ofstream &out) const;
	void Load(ifstream &in);
};

class Rectangle : public Shape {
protected:
	coord leftUpPoint;
	coord side;
public:
	void SetLeftUpPoint(coord LeftUpPoint);
	void SetSide(coord Side);

	void Show() const;

	void Save(ofstream &out) const;
	void Load(ifstream &in);
};

class Circle : public Shape {
	coord center;
	short r;
public:
	Circle();

	void SetCenter(coord Center);
	void SetR(short R);

	void Show() const;

	void Save(ofstream &out) const;
	void Load(ifstream &in);
};

class Ellipse : public Rectangle {
public:
	void Show() const;

	void Save(ofstream &out) const;
};

#endif