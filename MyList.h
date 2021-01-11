#pragma once
#include <iostream>
using namespace std;

template<typename T>
struct Node {
	T data;
	Node* next;
	int index;
};

template<typename T>
class MyList {
	Node<T>* TList;
public:
	MyList() :TList(nullptr) {};
	MyList(const Node<T>& obj);
	bool isEmpty();
	int length(); // Длина списка
	void addToHead(T elem); // Добавление в начало
	void addByIterator(int it, T elem); // Добавление в середину
	void deleteFromHead(); // удаление с начала списка
	void deleteByIterator(int it); // Удаление после заданного элемента
	void mergeList(MyList<T>& MList); // Слияние списков
	void mergeSortList(MyList<T>& MList); // Слияние отсортированных списков
	void printList(); // Печать списка
	void createFromTail(); // Создание с хвоста
};

template<typename T>
inline MyList<T>::MyList(const Node<T>& obj) {
	this->TList->data = obj->data;
	this->TList->index = obj->index;
}

template<typename T>
inline bool MyList<T>::isEmpty() {
	return TList == 0;
}

template<typename T>
inline int MyList<T>::length() {
	Node<T>* pNode = TList;
	int count = 0;
	while (pNode) {
		count++;
		pNode = pNode->next;
	}
	return count;
}

template<typename T>
inline void MyList<T>::addToHead(T elem) {
	Node<T>* p = new Node<T>;
	p->data = elem;
	p->index = 0;
	p->next = TList;
	TList = p;
	p = p->next;
	while (p) {
		p->index++;
		p = p->next;
	}
}

template<typename T>
inline void MyList<T>::addByIterator(int it, T elem) {
	Node<T>* p = new Node<T>;
	Node<T>* pNode = TList;
	p->data = elem;
	p->index = it;
	if (it == 0) { // Первый
		addToHead(elem);
		delete p;
		pNode = 0;
	}
	else if ((it < length() - 1) && (it > 0)) { // Не первый и не последний
		while (pNode->index + 1 <= it) {
			if (pNode->index + 1 == it) {
				p->next = pNode->next;
				pNode->next = p;
				pNode = p->next;
			}
			else if (pNode->index + 1 < it)
				pNode = pNode->next;
		}
	}
	else if (it == length()) { // Последний
		while (pNode) {
			if (pNode->next == 0) {
				pNode->next = p;
				p->next = 0;
				pNode = 0;
			}
			else {
				pNode = pNode->next;
			}
		}
	}
	while (pNode) {
		pNode->index++;
		pNode = pNode->next;
	}
}

template<typename T>
inline void MyList<T>::deleteFromHead() {
	Node<T>* pNode = TList;
	if (TList->next == 0)
		TList = 0;
	else {
		TList = TList->next;
		pNode->next = 0;
		delete pNode;
		Node<T>* p = TList;
		while (p) {
			p->index--;
			p = p->next;
		}
	}
}

template<typename T>
inline void MyList<T>::deleteByIterator(int it) {
	Node<T>* pNode = TList;
	Node<T>* qNode;
	if (it == 0) // Первый
		deleteFromHead();
	else if ((it < length() - 1) && (it > 0)) { // Не первый и не последний
		while (pNode) {
			if (pNode->index + 1 == it) {
				qNode = pNode->next;
				pNode->next = qNode->next;
				qNode->next = 0;
				delete qNode;
				pNode = pNode->next;
			}
			else if (pNode->index > it) {
				pNode->index--;
				pNode = pNode->next;
			}
			else
				pNode = pNode->next;
		}
	}
	else if (it == length() - 1) { // Последний
		while (pNode) {
			if (pNode->index + 1 == it) {
				qNode = pNode->next;
				pNode->next = 0;
				delete qNode;
				pNode = 0;
			}
			else
				pNode = pNode->next;
		}
	}
}

template<typename T>
inline void MyList<T>::printList() {
	Node<T>* p = TList;
	cout << "______________________________________" << endl;
	while (p) {
		cout << p->data << endl;
		p = p->next;
	}
	cout << "______________________________________" << endl;
}

template<typename T>
inline void MyList<T>::mergeList(MyList<T>& MList) {
	Node<T>* p = TList;
	bool check = 0;
	while (p) {
		if ((p->next == 0)&&(!check)) {
			p->next = MList.TList;
			check = 1;
		}
		if (p->next != 0)
			if ((p->next->index != p->index + 1) && (check))
				p->next->index = p->index + 1;
		p = p->next;
	}
	MList.TList = TList;
}

template<typename T>
inline void MyList<T>::mergeSortList(MyList<T>& MList) {
	Node<T>* p = TList; //Ставим указатели на первый эл-т каждого списка
	Node<T>* q = MList.TList;
	Node<T>* pNode;
	if (p->data < q->data) { //Сравниваем первые эл-ты (тот список, у которого первый эл-т меньше будет "главным", к нему будут добавляться эл-ты из другого списка)
		pNode = p; //Ставим вспомогательный указатель на меньший элемент
		MList.TList = TList; //Указатели на оба списка теперь указывают на главный
	}
	else {
		pNode = q;
		swap(p, q);
		TList = MList.TList;
	}
	while ((p->next != NULL) && (q->next != NULL)) { //Этот цикл работает пока указатель не окажется на последнем элементе одного из списков
		if (p->next->data > q->data) {           //Если элемент из "главного" списка, который стоит после эл-та на кот. указатель "р", больше, чем элемент
			pNode = q;                       //второго списка на котором стоит указатель "q", то эл-т "q" вставляется между p и p->next,
			q = p->next;                     //а указатель p переходит на p->next
			p->next = pNode;                 //Если же элемент "p->next" меньше, чем "q", то "p" переставляется на "p->next" и цикл повторяется
			pNode = pNode->next;
			p->next->next = q;
			swap(q, pNode);
			p = p->next;
			pNode = p;
		}
		else {
			pNode = pNode->next;
			p = p->next;
		}
	}
	if (q->next == NULL) {   //После цикла, если у нас остаётся один эл-т из второго списка, мы сравниваем его и вставляем в нужное место
		if (p->next->data > q->data) {
			pNode = p->next;
			p->next = q;
			q->next = pNode;
		}
		else {
			p->next->next = q;
		}

	}
	if (p->next == NULL) { //Если у нас закончился главный список и во втором осталось больше одного эл-та мы присоединяем остаток второго списка в конец "главного"
		p->next = q;
	}
	p = TList;
	while (p) {
		if (p->next != 0)
			if (p->next->index != p->index + 1)
				p->next->index = p->index + 1;
		p = p->next;
	}
}

template<typename T>
inline void MyList<T>::createFromTail() {
	Node<T>* tail = TList;
	int n;
	cout << "Введите кол-во элементов: ";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		T elem;
		cout << endl << "Введите элемент: ";
		cin >> elem;
		addByIterator(i, elem);
	}
}