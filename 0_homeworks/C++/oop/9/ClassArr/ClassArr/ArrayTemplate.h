#pragma once

#include <ostream>
using namespace std;

template <typename T>
class ArrayTemplate{
	T *arr;
	int sizeCurr, sizeMax;
public:
	ArrayTemplate() {
		arr = nullptr;
		sizeCurr = sizeMax = 0;
	}
	ArrayTemplate(const ArrayTemplate <T>&rhs) {
		sizeCurr = rhs.sizeCurr;
		sizeMax = rhs.sizeMax;
		arr = new T[rhs.sizeMax];
		for (int i = 0; i < sizeCurr; ++i)
			arr[i] = rhs.arr[i];
	}
	~ArrayTemplate() {
		if (arr != nullptr)
			delete[] arr;
	}
	
	// ��������� ������� �������(���������� ���������, ������� �������� ������);
	int GetSize() const {
		return sizeMax;
	}
	
	//���������  �������  �������
	//(���� �������� size ������ ����������� ������� �������, �� ���������� �������������� ���� ������, ���� ���, �� ���� -
	//	��� �������� �������� � ������ �������������); �������� grow ���������� ��� ������ ���������� ��������� �������� -
	//	�� �������� ������, ���� ���������� ��������� ����������� �������  ������  �������.��������, SetSize(5, 5);  ��������,
	//	��� ��� ���������� 6 - �� �������� ������ ������� ���������� ������ 10, ��� ���������� 11 - �� - 15 � �.�.
	void SetSize(int size, int grow = 1) {
		if (size < sizeMax) {
			T* tmp = new T[size + grow];
			for (int i = 0; i < sizeCurr; ++i)
				tmp[i] = arr[i];
			delete[] arr;
			arr = tmp;
			sizeCurr = (size > sizeCurr ? sizeCurr : size);
			sizeMax = size + grow;
		}
		else {
			T* tmp = new T[size + grow];
			for (int i = 0; i < sizeCurr; ++i)
				tmp[i] = arr[i];
			delete[] arr;
			arr = tmp;
			sizeMax = size + grow;
		}
	}

	//��������� ���������� ����������� ������� � �������.��������, ���� ��� ������� ������� 10, �� ���������� � ���� 4 ��������, �� ������� ������ 3;
	int GetUpperBound() const {
		return sizeCurr - 1 == -1 ? 0 : sizeCurr - 1 ;
	}

	//������ ���� ?
	bool IsEmpty() const {
		return sizeMax == 0;
	}

	//FreeExtra - �������  ��������  ������(����  ����������  ����������� �������);
	void FreeExtra() {
		if (sizeMax > sizeCurr) {
			T *tmp = new T[sizeCurr];
			for (int i = 0; i < sizeCurr; i++)
				tmp[i] = arr[i];
			delete[] arr;
			arr = tmp;
			sizeMax = sizeCurr;
		}
	}

	//RemoveAll  � ������� ���;
	void RemoveAll() {
		sizeCurr = sizeMax = 0;
		delete[] arr;
		arr = nullptr;
	}

	//��������� ������������� ��������(�� �������);
	T GetAt(int pos) const {
		if (pos < 0 )
			return arr[0];
		if(pos >= sizeCurr)
			return arr[sizeCurr - 1];
		return arr[pos];
	}

	//��������� ������ �������� ��� ������������� ��������(������  ��������  ������  ����  ������  ��������  ������� �������);
	void SetAt(int pos, T val) {
		if (pos < 0){
			arr[0] = val;
			return;
		}
		if (pos >= sizeCurr) {
			arr[sizeCurr - 1] = val;
			return;
		}
		arr[pos] = val;
	}

	//��� ���������� ���� ���������� �������;
	T& operator[](int pos) {
		//if (pos < 0)
		//	return arr[0];
		//if (pos >= sizeCurr)
		//	return arr[sizeCurr - 1];
		return arr[pos];
	}

	ArrayTemplate& operator=(ArrayTemplate& rhs) {
		if (this == &rhs)
			return *this;

		delete[] arr;
		arr = new T[rhs.sizeMax];
		for (int i = 0; i < rhs.sizeCurr; ++i)
			arr[i] = rhs.arr[i];
		sizeMax = rhs.sizeMax;
		sizeCurr = rhs.sizeCurr;

		return *this;
	}
	ArrayTemplate Append(ArrayTemplate& second) {
		ArrayTemplate <T> rezult;
		for (int i = 0; i < sizeCurr; ++i)
			rezult.Add(operator[](i));
		for (int i = 0; i < second.sizeCurr; ++i)
			rezult.Add(second[i]);
		return rezult;
	}

	void InsertAt(T el, int pos) {
		if (sizeCurr + 1 > sizeMax - 1)
			SetSize(sizeMax);
		for (int i = sizeCurr - 1; i >= pos; --i)
			arr[i + 1] = arr[i];
		arr[pos] = el;
		++sizeCurr;
	}

	void RemoveAt(int pos) {
		if (pos < sizeCurr) {
			for (int i = pos; i < sizeCurr - 1; ++i)
				arr[i] = arr[i + 1];
			--sizeCurr;
		}
	}

	void Add(T el) {
	if (sizeCurr + 1 > sizeMax - 1)
		SetSize(sizeMax);
	arr[sizeCurr++] = el;
		
	}

	//��������� ������ ������� � �������;
	T *GetData() const {
		return arr;
	}

	friend ostream& operator<<(ostream& out, ArrayTemplate <T>& arr) {
		for (int i = 0; i <= arr.GetUpperBound(); ++i)
			out << arr[i] << ' ';
		return out;
	}
};

