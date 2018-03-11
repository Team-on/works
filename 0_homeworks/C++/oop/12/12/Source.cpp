#include <iostream>
#include <Windows.h>
using namespace std;

template <typename T>
struct ListNode {
	T v;
	ListNode *n;

	ListNode() {
		n = nullptr;
	}
	ListNode(T V) {
		n = nullptr;
		v = V;
	}

	operator T() {
		return v;
	}
};
template <typename T>
class List {
	ListNode <T> *root;

	ListNode <T> * GetTail() const {
		ListNode <T> *p = root;
		for (; p->n != nullptr; p = p->n);
		return p;
	}
public:
	List() {
		root = nullptr;
	}
	List(T v) {
		root = new ListNode<T>;
		root->v = v;
	}
	~List() {
		DelAll();
	}

	ListNode <T> * GetV(T v) const {
		int cnt = 0;
		for (ListNode <T> *p = root; p != nullptr; p = p->n, ++cnt) 
			if (p->v == v)
				return p;	
		return root;
	}
	ListNode <T> * GetHead() const {
		return root;
	}

	void Print() const{
		for (ListNode <T> *p = root; p != nullptr; p = p->n)
			cout << p->v << ' ';
	}

	void AddHead(T v) {
		ListNode <T> * rn = new ListNode <T>(v);
		rn->n = root;
		root = rn;
	}
	void AddHead(ListNode <T> *v) {
		ListNode <T> * rn = new ListNode <T>(v->v);
		rn->n = root;
		root = rn;
	}
	void AddTail(T v) {
		ListNode <T> *p = root;
		for (; p->n != nullptr; p = p->n);
		p->n = new ListNode <T>(v);
	}

	void DelHead() {
		ListNode <T> *tmp = root;
		root = root->n;
		delete tmp;
	}
	void DelTail() {
		ListNode <T> *p = root;
		for (; p->n->n != nullptr; p = p->n);
		delete p->n;
		p->n = nullptr;
	}
	void DelAll() {
		while (root != nullptr)
			DelHead();
	}

	void AddBefore(ListNode <T> *pos, T val) {
		ListNode <T> *p = root, *tmp;
		for (; p != nullptr, p->n != pos; p = p->n);
		tmp = p->n;
		p->n = new ListNode <T>(val);
		p->n->n = tmp;
	}
	void AddAfter(ListNode <T> *pos, T val) {
		ListNode <T> *p = root, *tmp;
		for (; p != nullptr, p != pos; p = p->n);
		tmp = p->n;
		p->n = new ListNode <T>(val);
		p->n->n = tmp;
	}
	void DelAt(ListNode <T> *pos) {
		ListNode <T> *tmp = root;
		for (; tmp->n != pos; tmp = tmp->n);
		tmp->n = pos->n;
		delete pos;
	}

	int Replace(T valOld, T valNew) {
		int cnt = -1;
		for (ListNode <T> *p = root; p != nullptr; p = p->n) {
			if (p->v == valOld) {
				p->v = valNew;
				++cnt;
			}
		}
		return (cnt == -1)?-1:cnt + 1;
	}

	void Reverse() {
		ListNode <T> *curr = root;
		List <T> *newList = new List<T>;
		int size = 0;
		for (; curr != nullptr; curr = curr->n) {
			newList->AddHead(curr->v);
		}
		DelAll();
		*this = *newList;
	}

	void operator=(ListNode <T> * Head) {
		DelAll();
		root = Head;
	}

	ListNode <T> * Clone() {
		ListNode <T> *listCurr, *listHead;
		listCurr = listHead = new ListNode <T>;
		for (ListNode <T> *p = root; p != nullptr; p = p->n) {
			listCurr->n = new ListNode <T>;
			listCurr = listCurr->n;
			listCurr->v = p->v;
		}
		if (listCurr != listHead) {
			ListNode <T> * rezult = listHead->n;
			delete listHead;
			return rezult;
		}
		delete listHead;
		return nullptr;
	}
	ListNode <T> * operator+(List & rhs) {
		ListNode <T> *listPart1, *listRez;
		listRez = listPart1 = Clone();		
		for (; listPart1->n != nullptr; listPart1 = listPart1->n);
		listPart1->n = rhs.Clone();
		return listRez;
	}
	ListNode <T> * operator*(List & rhs) {
		ListNode <T> *part1, *listRez, *prev, *rroot;
		prev = listRez = part1 = Clone();

		for (; part1 != nullptr; part1 = part1->n) {
			bool found = 0;
			for (rroot = rhs.GetHead(); rroot != nullptr; rroot = rroot->n) {
				if (part1->v == rroot->v) {
					found = 1;
					break;
				}
			}
			if (!found) {
				if (listRez == part1) {
					listRez = prev = part1->n;
				}
				else {
					prev->n = part1->n;
					prev = part1;
				}
			}
		}


		return listRez;
	}
};

template <typename T>
struct ListNodeDouble {
	T val;
	ListNodeDouble *next;
	ListNodeDouble *prev;

	ListNodeDouble() {
		next = prev = nullptr;
	}
	ListNodeDouble(T V) {
		next = prev = nullptr;
		val = V;
	}
	ListNodeDouble(ListNodeDouble <T> &rhs) {
		next = rhs.next;
		prev = rhs.prev;
		val = rhs.val;
	}
	operator T() {
		return val;
	}
};
template <typename T>
class ListDouble {
	ListNodeDouble <T> *head;
	ListNodeDouble <T> *tail;
public:
	ListDouble() {
		head = tail = nullptr;
	}
	ListDouble(T V) {
		head = tail = new ListNodeDouble <T>(V);	
	}
	ListDouble(ListDouble &rhs) {
		head = rhs.Clone();
	}
	~ListDouble() {
		DelAll();
	}

	void AddHead(T val) {
		if (head != nullptr) {
			ListNodeDouble <T> *headNew = new ListNodeDouble <T>(val);
			headNew->next = head;
			head->prev = headNew;
			head = headNew;
		}
		else {
			tail = head = new ListNodeDouble <T>(val);
		}
	}
	ListNodeDouble <T> * GetHead() const {
		return head;
	}
	void AddTail(T val) {
		ListNodeDouble <T> *tailNew = new ListNodeDouble <T>(val);
		if (tail != nullptr) {
			tailNew->prev = tail;
			tail->next = tailNew;
			tail = tailNew;
		}
		else {
			head = tail = tailNew;
		}
	}
	void Print() const {
		for (ListNodeDouble <T> * p = head; p != nullptr; p = p->next)
			cout << p->prev << ' ' << p->val << ' ' << p << ' ' << p->next << ' ' << endl;
		//for (ListNodeDouble <T> * p = head; p != nullptr; p = p->next)
			//cout << p->val << ' ';
	}
	
	void DelHead() {
		if (head != tail){
			ListNodeDouble <T> *headNew = head->next;
			delete head;
			head = headNew;
			head->prev = nullptr;
		}
		else {
			delete head;
			head = tail = nullptr;
		}
	}
	void DelTail() {
		if (head != tail) {
			ListNodeDouble <T> *tailNew = tail->prev;
			delete tail;
			tail = tailNew;
			tail->next = nullptr;
		}
		else {
			delete head;
			head = tail = nullptr;
		}
	}
	void DelAll() {
		while (head != nullptr)
			DelHead();
	}

	void AddBefore(ListNodeDouble <T> *pos, T value) {
		ListNodeDouble <T> * node = new ListNodeDouble <T>(value);
		node->next = pos;
		node->prev = pos->prev;
		pos->prev->next = node;
		pos->prev = node;
	}
	void AddAfter(ListNodeDouble <T> *pos, T value) {
		//AddBefore(pos->next, value);
		ListNodeDouble <T> * node = new ListNodeDouble <T>(value);
		node->next = pos->next;
		node->prev = pos;
		pos->next->prev = node;
		pos->next = node;
	}
	void DelPos(ListNodeDouble <T> *pos) {
		pos->next->prev = pos->prev;
		pos->prev->next = pos->next;
		delete pos;
	}
	ListNodeDouble <T> * FindFirst(T value) {
		for (ListNodeDouble <T> *p = head; p != nullptr; p = p->next)
			if (p->val == value)
				return p;
	}
	ListNodeDouble <T> * FindFirst(int pos, bool posFind) {
		for (ListNodeDouble <T> *p = head; p != nullptr; p = p->next, --pos)
			if (pos == 0)
				return p;
		return 0;
	}
	int FindReplace(T valueOld, T valueNew) {
		int cnt = -1;

		for (ListNodeDouble <T> *p = head; p != nullptr; p = p->next)
			if (p->val == valueOld) {
				p->val = valueNew;
				++cnt;
			}

		return (cnt == -1) ? -1 : cnt + 1;;
	}

	void Reverse() {
		for (ListNodeDouble <T> *p = head; p != nullptr; p = p->prev )
			swap(p->next, p->prev);
		swap(head, tail);
	}

	void operator=(ListNodeDouble <T> * rhs) {
		DelAll();
		if (rhs != nullptr) {
			head = rhs;
			for (; rhs->next != nullptr; rhs = rhs->next);
			tail = rhs;
		}
	}
	ListNodeDouble <T> * Clone() {
		ListNodeDouble <T> *listCurr = new ListNodeDouble <T>;
		ListNodeDouble <T> *p = head;
		for (; p->next != nullptr; p = p->next) {
			listCurr->val = p->val;
			listCurr->next = new ListNodeDouble <T>;
			listCurr->next->prev = listCurr;
			listCurr = listCurr->next;
		}	
		listCurr->val = p->val;
		for (; listCurr->prev != nullptr; listCurr = listCurr->prev);
		return listCurr;
	}
	ListNodeDouble <T> * operator+(ListDouble <T> & rhs) {
		ListNodeDouble <T> *list;
		list = Clone();
		for (; list->next != nullptr; list = list->next);
		list->next = rhs.Clone();
		for (; list->prev != nullptr; list = list->prev);
		return list;
	}
	ListNodeDouble <T> * operator*(ListDouble <T> & rhs) {
		ListNodeDouble <T> *list = nullptr, *del = nullptr;
		list = Clone();
		for (; list->next != nullptr; list = list->next) {
			bool found = 0;
			if (del != nullptr) {
				delete del;
				del = nullptr;
			}
			for (ListNodeDouble <T> *tmp = rhs.GetHead(); tmp != nullptr; tmp = tmp->next) {
				if (tmp->val == list->val) {
					found = 1;
					break;
				}
			}
			if (!found) {
				if(list->next != nullptr)
					list->next->prev = list->prev;
				if (list->prev != nullptr)
					list->prev->next = list->next;
				del = list;
			}
		}
		if (del != nullptr)
			delete del;

		for (ListNodeDouble <T> *tmp = rhs.GetHead(); tmp != nullptr; tmp = tmp->next) {
			if (tmp->val == list->val) 
				break;
			if (tmp->next == nullptr) {
				if (list->prev != nullptr)
					list->prev->next = nullptr;
				del = list;
				list = list->prev;
				delete del;
			}
		}

		if (list == nullptr)
			return nullptr;

		for (; list->prev != nullptr; list = list->prev);
		return list;
	}
};

template <typename T>
class StackList {
	List <T> list;
public:
	void Push(T p) {
		list.AddHead(p);
	}
	T Pop(){
		T tmp = *(list.GetHead());
		list.DelHead();
		return tmp;
	}
	bool isEmpty() {
		return list.GetHead() == nullptr;
	}
};

template <typename T>
class QueueDList {
	ListDouble <T> list;
public:
	void Push(T p) {
		list.AddTail(p);
	}
	T Pop() {
		T tmp = *(list.GetHead());
		list.DelHead();
		return tmp;
	}
	bool isEmpty() {
		return list.GetHead() == nullptr;
	}
};

template <typename T>
class Array {
	ListDouble <T> list;
	int size;
public:
	Array() :size(0) {
		
	}

	void SetSize(int Size) {
		if (Size > size) {
			size = Size;
			for (int i = 0; i < size; ++i)
				list.AddTail(0);
		}
		else if (size > Size) {
			for (int i = 0; i < size - Size; ++i)
				list.DelTail();
			size = Size;
		}
	}
	int GetSize() const {
		return size;
	}
	int GetUpperBound() const{
		return (size - 1) == -1 ? 0 : size - 1;
	}
	bool IsEmpty() const {
		return size == 0;
	}

	void RemoveAll() {
		list.DelAll();
		size = 0;
	}

	ListNodeDouble <T> * GetData() const{
		return list.GetHead();
	}

	T& GetAt(int pos){
		return (list.FindFirst(pos, 1))->val;
	}
	T& SetAt(int pos, T value){
		return (((list.FindFirst(pos, 1))->val) = value);
	}
	T& operator[](int pos) {
		return GetAt(pos);
	}

	void Add(T val) {
		list.AddTail(val);
		++size;
	}
	void InsertAt(int pos, T val){
		list.AddBefore(list.FindFirst(pos, 1), val);
		++size;
	}
	void RemoveAt(int pos) {
		list.DelPos(list.FindFirst(pos, 1));
		--size;
	}

	friend ListNodeDouble <T> * Append(Array& arr1, Array& arr2) {
		ListNodeDouble <T> * listTmp;
		listTmp = arr1.list + arr2.list;
		return listTmp;
	}

	Array <T> & operator=(Array <T> &rhs) {
		if (this == &rhs)
			return *this;
		RemoveAll();
		SetSize(rhs.GetSize());
		for (int i = 0; i < GetSize(); ++i) {
			operator[](i) = rhs.operator[](i);
		}
		return *this;
	}
	Array <T>& operator=(ListNodeDouble <T> *rhs) {
		RemoveAll();
		list = rhs;
		for (ListNodeDouble <T> * i = rhs; i != nullptr; i = i->next, ++size);
		return *this;
	}
	friend ostream& operator<<(ostream& out, Array <T>& arr) {
		for (int i = 0; i < arr.GetSize(); ++i)
			out << arr.GetAt(i) << ' ';
		return out;
	}
};

void main() {
	Array <int> arr;

	cout << "Start:\n";
	cout << "IsEmpty " << arr.IsEmpty() << endl;
	cout << "GetSize " << arr.GetSize() << endl;
	cout << "GetUpperBound " << arr.GetUpperBound() << endl << endl;

	arr.SetSize(5);
	cout << "Set size 5" << endl;
	cout << "IsEmpty " << arr.IsEmpty() << endl;
	cout << "GetSize " << arr.GetSize() << endl;
	cout << "GetData " << arr.GetData() << endl;
	cout << "GetUpperBound " << arr.GetUpperBound() << endl;

	for (int i = 0; i < arr.GetSize(); ++i)
		arr[i] = i + 1;
	cout << arr << endl << endl;

	Array <int> arrTmp;
	arrTmp.SetSize(10);
	for (int i = 0; i < arrTmp.GetSize(); ++i)
		arrTmp[i] = 100 - i;
	arr = arrTmp;

	cout << "After = \n";
	cout << "GetSize " << arr.GetSize() << endl;
	cout << "GetUpperBound " << arr.GetUpperBound() << endl;
	cout << "GetData " << arr.GetData() << endl;
	cout << arr << endl << endl;

	cout << "Insert A5 5 -> Remove At 5\n";
	arr.InsertAt(5, 1251);
	cout << arr << endl;
	arr.RemoveAt(5);
	cout << arr << endl << endl;

	cout << "Append\n";
	arr = Append(arr, arrTmp);
	cout << "GetSize " << arr.GetSize() << endl;
	cout << "GetUpperBound " << arr.GetUpperBound() << endl;
	cout << "GetData " << arr.GetData() << endl;
	cout << arr << endl << endl;

	/*
	ListDouble <int> l1, l2, l3;

	for (int i = 0; i <= 5; ++i)
		l1.AddHead(i);
	l2 = l1.Clone();
	l1.Print(); cout << endl;
	l2.Print(); cout << endl;
	l1.DelHead(); l1.DelHead(); l1.DelTail();
	l1.Print(); cout << endl;
	l2.Print(); cout << endl;

	l3 = l1 + l2;
	l3.Print(); cout << endl;

	l3 = l1 * l2;
	l3.Print(); cout << endl;

	l1.DelAll(); l2.DelAll();
	for (int i = 0; i <= 5; ++i) {
		l1.AddHead(i);
		l2.AddHead(i);
	}
	l3 = l1 * l2;
	l3.Print(); cout << endl;

	l1.DelAll(); l2.DelAll();
	for (int i = 0; i <= 5; ++i) {
		l1.AddHead(i);
		l2.AddHead(-i);
	}
	l3 = l1 * l2;
	l3.Print(); cout << endl;

	l1.DelAll(); l2.DelAll();

	l1.DelAll(); l2.DelAll();
	for (int i = 5; i >= 0; --i) {
		l1.AddHead(i);
		l2.AddHead(-i);
	}
	l3 = l1 * l2;
	l3.Print(); cout << endl;

	l1.DelAll(); l2.DelAll();
	for (int i = 5; i >= 1; --i) {
		l1.AddHead(i);
		l2.AddHead(-i);
	}
	l3 = l1 * l2;
	l3.Print(); cout << endl;
	*/

	/*
	QueueDList <char> queue;
	for (char i = 'a'; i <= 'z'; ++i) 
		queue.Push(i);
	while (!queue.isEmpty())
		cout << queue.Pop();
	cout << endl;

	StackList <char> stack;
	for (char i = 'a'; i <= 'z'; ++i)
		stack.Push(i);

	while (!stack.isEmpty())
		cout << stack.Pop();
	cout << endl;
	*/
	/*
	List <int> l1, l2, l3;

	for (int i = 0; i <= 5; ++i) {
		l1.AddHead(i);
		l2.AddHead(i);
	}
	l2.AddHead(152);
	l1.Print(); cout << endl;
	l2.Print(); cout << endl;
	l3 = l1 + l2;
	l3.Print(); cout << endl;
	l3 = l1 * l2;
	l3.Print(); cout << endl;
	*/

	/*
	ListDouble <int> ld(0);

	for (int i = 1; i < 5; ++i)
		ld.AddTail(i);
	ld.Print();	cout << endl;
	ld.Reverse();
	ld.Print();	cout << endl;
	
	ld.DelAll();
	*/
	/*
	List <int> l;
	for (int i = 0; i < 3; ++i)
		l.AddHead(0);
	for (int i = 0; i < 3; ++i) 
		l.AddTail(i + 1);
	
	l.Print(); cout << endl;
	l.AddBefore(l.GetV(1), -13);  	l.AddAfter(l.GetV(1), 13);
	l.Replace(0, 16);
	l.Print(); cout << endl;
	l.Reverse();
	l.Print(); cout << endl;
	*/
	system("pause");
}


