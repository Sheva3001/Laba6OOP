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
	int length(); // ����� ������
	void addToHead(T elem); // ���������� � ������
	void addByIterator(int it, T elem); // ���������� � ��������
	void deleteFromHead(); // �������� � ������ ������
	void deleteByIterator(int it); // �������� ����� ��������� ��������
	void mergeList(MyList<T>& MList); // ������� �������
	void mergeSortList(MyList<T>& MList); // ������� ��������������� �������
	void printList(); // ������ ������
	void createFromTail(); // �������� � ������
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
	if (it == 0) { // ������
		addToHead(elem);
		delete p;
		pNode = 0;
	}
	else if ((it < length() - 1) && (it > 0)) { // �� ������ � �� ���������
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
	else if (it == length()) { // ���������
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
	if (it == 0) // ������
		deleteFromHead();
	else if ((it < length() - 1) && (it > 0)) { // �� ������ � �� ���������
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
	else if (it == length() - 1) { // ���������
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
	Node<T>* p = TList; //������ ��������� �� ������ ��-� ������� ������
	Node<T>* q = MList.TList;
	Node<T>* pNode;
	if (p->data < q->data) { //���������� ������ ��-�� (��� ������, � �������� ������ ��-� ������ ����� "�������", � ���� ����� ����������� ��-�� �� ������� ������)
		pNode = p; //������ ��������������� ��������� �� ������� �������
		MList.TList = TList; //��������� �� ��� ������ ������ ��������� �� �������
	}
	else {
		pNode = q;
		swap(p, q);
		TList = MList.TList;
	}
	while ((p->next != NULL) && (q->next != NULL)) { //���� ���� �������� ���� ��������� �� �������� �� ��������� �������� ������ �� �������
		if (p->next->data > q->data) {           //���� ������� �� "��������" ������, ������� ����� ����� ��-�� �� ���. ��������� "�", ������, ��� �������
			pNode = q;                       //������� ������ �� ������� ����� ��������� "q", �� ��-� "q" ����������� ����� p � p->next,
			q = p->next;                     //� ��������� p ��������� �� p->next
			p->next = pNode;                 //���� �� ������� "p->next" ������, ��� "q", �� "p" �������������� �� "p->next" � ���� �����������
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
	if (q->next == NULL) {   //����� �����, ���� � ��� ������� ���� ��-� �� ������� ������, �� ���������� ��� � ��������� � ������ �����
		if (p->next->data > q->data) {
			pNode = p->next;
			p->next = q;
			q->next = pNode;
		}
		else {
			p->next->next = q;
		}

	}
	if (p->next == NULL) { //���� � ��� ���������� ������� ������ � �� ������ �������� ������ ������ ��-�� �� ������������ ������� ������� ������ � ����� "��������"
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
	cout << "������� ���-�� ���������: ";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		T elem;
		cout << endl << "������� �������: ";
		cin >> elem;
		addByIterator(i, elem);
	}
}