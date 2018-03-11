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
	
	// получение размера массива(количество элементов, которые выделена память);
	int GetSize() const {
		return sizeMax;
	}
	
	//установка  размера  массива
	//(если параметр size больше предыдущего размера массива, то выделяется дополнительный блок памяти, если нет, то «лиш -
	//	ние» элементы теряются и память освобождается); параметр grow определяет для какого количества элементов необходи -
	//	мо выделить память, если количество элементов превосходит текущий  размер  массива.Например, SetSize(5, 5);  означает,
	//	что при добавлении 6 - го элемента размер массива становится равным 10, при добавлении 11 - го - 15 и т.д.
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

	//получение последнего допустимого индекса в массиве.Например, если при размере массива 10, вы добавляете в него 4 элемента, то функция вернет 3;
	int GetUpperBound() const {
		return sizeCurr - 1 == -1 ? 0 : sizeCurr - 1 ;
	}

	//массив пуст ?
	bool IsEmpty() const {
		return sizeMax == 0;
	}

	//FreeExtra - удалить  «лишнюю»  память(выше  последнего  допустимого индекса);
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

	//RemoveAll  – удалить все;
	void RemoveAll() {
		sizeCurr = sizeMax = 0;
		delete[] arr;
		arr = nullptr;
	}

	//получение определенного элемента(по индексу);
	T GetAt(int pos) const {
		if (pos < 0 )
			return arr[0];
		if(pos >= sizeCurr)
			return arr[sizeCurr - 1];
		return arr[pos];
	}

	//установка нового значения для определенного элемента(индекс  элемента  должен  быть  меньше  текущего  размера массива);
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

	//для реализации двух предыдущих функций;
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

	//получения адреса массива с данными;
	T *GetData() const {
		return arr;
	}

	friend ostream& operator<<(ostream& out, ArrayTemplate <T>& arr) {
		for (int i = 0; i <= arr.GetUpperBound(); ++i)
			out << arr[i] << ' ';
		return out;
	}
};

