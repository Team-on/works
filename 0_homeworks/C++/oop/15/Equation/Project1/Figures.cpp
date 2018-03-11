#include "Figures.h"

//--------------------------------------- Square -----------------------------------
Square::Square() : side(0) {}

void Square::SetLeftUpPoint(coord LeftUpPoint) {
	leftUpPoint = LeftUpPoint;
}
void Square::SetSide(short Side) {
	side = Side;
}

void Square::Show() const {
	cout << "Square\n";
	cout << "\tLeft up corner: " << leftUpPoint << endl;
	cout << "\tSide: " << side << endl;
}

void Square::Save(ofstream &out) const {
	out << "Square:\n" << leftUpPoint.x << " " << leftUpPoint.y << " " << side << "\n";
}
void Square::Load(ifstream &in) {
	in >> leftUpPoint.x >> leftUpPoint.y >> side;
}

//--------------------------------------- Rectangle -----------------------------------
void Rectangle::SetLeftUpPoint(coord LeftUpPoint) {
	leftUpPoint = LeftUpPoint;
}
void Rectangle::SetSide(coord Side) {
	side = Side;
}

void Rectangle::Show() const {
	cout << "Rectangle\n";
	cout << "\tLeft up corner: " << leftUpPoint << endl;
	cout << "\tSide x: " << side.x << endl;
	cout << "\tSide y: " << side.y << endl;
}

void Rectangle::Save(ofstream &out) const {
	out << "Rectangle:\n" << leftUpPoint.x << " " << leftUpPoint.y << " " << side.x << " " << side.y << "\n";
}
void Rectangle::Load(ifstream &in) {
	in >> leftUpPoint.x >> leftUpPoint.y >> side.x >> side.y;
}

//--------------------------------------- Circle -----------------------------------
Circle::Circle() : r(0) {}

void Circle::SetCenter(coord Center) {
	center = Center;
}
void Circle::SetR(short R) {
	r = R;
}

void Circle::Show() const {
	cout << "Circle\n";
	cout << "\tCenter: " << center << endl;
	cout << "\tR: " << r << endl;
}

void Circle::Save(ofstream &out) const {
	out << "Circle:\n" << center.x << " " << center.y << " " << r << "\n";
}
void Circle::Load(ifstream &in) {
	in >> center.x >> center.y >> r;
}

//--------------------------------------- Ellipse -----------------------------------
void Ellipse::Show() const {
	cout << "Ellipse\n";
	cout << "\tLeft up corner: " << leftUpPoint << endl;
	cout << "\tSide x: " << side.x << endl;
	cout << "\tSide y: " << side.y << endl;
}

void Ellipse::Save(ofstream &out) const {
	out << "Ellipse:\n" << leftUpPoint.x << " " << leftUpPoint.y << " " << side.x << " " << side.y << "\n";
}