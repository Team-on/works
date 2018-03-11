#ifndef _EQUATIONS_ROOTS_H_
#define _EQUATIONS_ROOTS_H_

#include "Header.h"

/*
������� ����������� ������� ����� � ����������� ����-
���� � ����� ���������. ������� ����������� ������:
����� �������� ��������� � ����� ���������� ���������.
���������� ������� ���������� ������ ���������.
*/

struct EquationRoots {
	double * roots;
	unsigned short size;

	EquationRoots();
	EquationRoots(const EquationRoots & rhs);
	~EquationRoots();

	void Show() const;
};

class EquationBasic {
public:
	virtual void CinValue() = 0;
	virtual EquationRoots GetRoot() = 0;
};

class LinearEquation : public EquationBasic {
	double a, b;
public:
	// a * x + b = 0
	void GetValue(double A, double B);
	void CinValue();

	EquationRoots GetRoot();
};

class SqrEquation : public EquationBasic {
	double a, b, c;
public:
	//a * x^2 + b * x + c = 0
	void GetValue(double A, double B, double C);
	void CinValue();

	EquationRoots GetRoot();
};

#endif