#ifndef _FIGURES_H_
#define _FIGURES_H_

#include "Header.h"
#include "coord.h"

/*
�������� ����������� ����� Shape ��� ��������� �������
�����. ���������� ����������� ������:
�	 Show() � ����� �� ����� ���������� � ������,
�	 Save() � ���������� ������ � ����,
�	 Load() � ���������� ������ �� �����.
���������� ����������� ������:
�	 Square � �������, ������� ��������������� ������-
������ ������ �������� ���� � ������ �������;
�	 Rectangle � ������������� � ��������� ������������
�������� ������ ���� � ���������;
�	 Circle � ���������� � ��������� ������������ ���-
��� � ��������;
�	 Ellipse � ������ � ��������� ������������ ��������
���� ���������� ������ ���� �������������� �� ���-
������, ������������� ���� ���������, � ���������
����� ��������������.
�������� ������ �����, ��������� ������ � ����, �����-
���� � ������ ������ � ���������� ���������� �������
�� �����.
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