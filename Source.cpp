#include "MyList.h"
#include <iostream>
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	MyList<string> A; MyList<string> B;
	int number = 0; int iterator = 0; string value;
	cout << "============== Список №1 ==============" << endl;
	A.createFromTail();
	cout << "============== Список №2 ==============" << endl;
	B.createFromTail();
	int command = -1;
	while (command != 0) {
		cout << "============== Выберите действие ==============" << endl
			<< "1. Добавление по итератору" << endl
			<< "2. Удаление по итератору" << endl
			<< "3. Слияние списков" << endl
			<< "4. Слияние упорядоченных списков" << endl
			<< "5. Печать списка" << endl
			<< "0. Выход" << endl
			<< "==============================================" << endl;
		cin >> command;
		switch (command)
		{
		case 1:
			cout << "Введите номер списка, итератор и значение:" << endl;
			cin >> number; cin >> iterator; cin >> value;
			if (number == 1) {
				A.addByIterator(iterator, value);
				A.printList();
			}
			else if (number == 2) {
				B.addByIterator(iterator, value);
				B.printList();
			}
			break;
		case 2:
			cout << "Введите номер списка и итератор:" << endl;
			cin >> number; cin >> iterator;
			if (number == 1) {
				A.deleteByIterator(iterator);
				A.printList();
			}
			else if (number == 2) {
				B.deleteByIterator(iterator);
				B.printList();
			}
			break;
		case 3:
			cout << "Выберите порядок слияния:" << endl
				<< "1. 1 - 2" << endl
				<< "2. 2 - 1" << endl;
			cin >> number;
			if (number == 1) {
				A.mergeList(B);
				A.printList();
			}
			else if (number == 2) {
				B.mergeList(A);
				B.printList();
			}
			break;
		case 4:
			A.mergeSortList(B);
			A.printList();
			break;
		case 5:
			cout << "Введите номер списка:" << endl;
			cin >> number;
			if (number == 1) {
				A.printList();
			}
			else if (number == 2) {
				B.printList();
			}
			break;
		}
	}
	return 0;
}