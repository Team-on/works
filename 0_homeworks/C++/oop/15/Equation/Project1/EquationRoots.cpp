#include "EquationRoots.h"

//-------------------------------- EquationRoots ----------------------------------------
EquationRoots::EquationRoots() {
	roots = nullptr;
	size = 0;
}
EquationRoots::EquationRoots(const EquationRoots & rhs) {
	if (!rhs.roots || !rhs.size) {
		roots = nullptr;
		size = 0;
	}
	size = rhs.size;
	roots = new double[size];
	for (unsigned short i = 0; i < size; ++i) {
		roots[i] = rhs.roots[i];
	}
}
EquationRoots::~EquationRoots() {
	if (roots != nullptr)
		delete[] roots;
}

void EquationRoots::Show() const {
	for (unsigned short i = 0; i < size; ++i)
		cout << roots[i] << ' ';
}

//-------------------------------- LinearEquation ----------------------------------------
// a * x + b = 0
void LinearEquation::GetValue(double A, double B) {
	a = A;
	b = B;
}

void LinearEquation::CinValue() {
	cout << "a * x + b = 0\n";
	cout << "a:";	do { cin >> a; } while (!a);
	cout << "b:";	cin >> b;
}

EquationRoots LinearEquation::GetRoot() {
	EquationRoots rezult;

	rezult.size = 1;
	rezult.roots = new double[1];
	rezult.roots[0] = b / a;

	return rezult;
}

//-------------------------------- SqrEquation ----------------------------------------
//a * x^2 + b * x + c = 0
void SqrEquation::GetValue(double A, double B, double C) {
	a = A;
	b = B;
	c = C;
}

void SqrEquation::CinValue() {
	cout << "ax^2 + bx + c = 0\n";
	cout << "a:";	do { cin >> a; } while (!a);
	cout << "b:";	cin >> b;
	cout << "c:";	cin >> c;
}

EquationRoots SqrEquation::GetRoot() {
	EquationRoots rezult;


	double d = sqrt(b * b - 4 * a * c);

	rezult.size = 2;
	rezult.roots = new double[2];
	rezult.roots[0] = (-b - d) / (2 * a);
	rezult.roots[1] = (-b + d) / (2 * a);

	return rezult;
}