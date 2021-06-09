#include <iostream>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <vector>
#include <list>
#include <forward_list>
#include <algorithm>

#include <chrono>

#include "DoubleLinkedList.h"
#include "SingleLinkedList.h"

#include "btree.h"

#include "HashList.h"

using namespace std;

void UnitTest_DoubleLinkedList();
void UnitTest_SingleLinkedList();

void test_bst();

void test_HashList();

int main() {
	srand(time(nullptr));

	cout << "Unit tests:" << endl;
	UnitTest_DoubleLinkedList();
	UnitTest_SingleLinkedList();

	cout << endl << "Perfomance tests:" << endl;

	/* Double-Linked List region */
	list<float> l1;

	std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i < 6; ++i) {
		l1.push_back(abs(rand()) / 1000.0F);
	}
	for (size_t i = 0; i < 200; ++i) {
		l1.push_front(abs(rand()) / 1000.0F);
		l1.push_front(abs(rand()) / 1000.0F);
		l1.pop_back();
	}
	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	std::cout << "The std::list time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " us\n";

	DoubleLinkedList<float> l2;

	begin = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i < 6; ++i) {
		l2.push_back(abs(rand()) / 1000.0F);
	}
	for (size_t i = 0; i < 200; ++i) {
		l2.push_front(abs(rand()) / 1000.0F);
		l2.push_front(abs(rand()) / 1000.0F);
		l2.pop_back();
	}
	end = std::chrono::high_resolution_clock::now();
	std::cout << "The DoubleLinkedList.h time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " us\n";

	/* Single-Linked List region */
	forward_list<float> sl1;

	begin = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i < 6; ++i) {
		sl1.push_front(abs(rand()) / 1000.0F);
	}
	for (size_t i = 0; i < 200; ++i) {
		sl1.push_front(abs(rand()) / 1000.0F);
		sl1.push_front(abs(rand()) / 1000.0F);
		sl1.pop_front();
	}
	end = std::chrono::high_resolution_clock::now();
	std::cout << "The std::forward_list time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " us\n";

	SingleLinkedList<float> sl2;

	begin = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i < 6; ++i) {
		sl2.push(abs(rand()) / 1000.0F);
	}
	for (size_t i = 0; i < 200; ++i) {
		sl2.push(abs(rand()) / 1000.0F);
		sl2.push(abs(rand()) / 1000.0F);
		sl2.pop();
	}
	end = std::chrono::high_resolution_clock::now();
	std::cout << "The SingleLinkedList.h time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " us\n";

	/* BST region */
	std::cout << "==== BST Test ====" << std::endl;
	test_bst();
	
	/* Hash List region */
	std::cout << "==== Hash List Test ====" << std::endl;
	test_HashList();
	
	return 0;
}

/* DOUBLE LINKED LIST UNIT TEST */
void UnitTest_DoubleLinkedList() {
	list<float> cb1;
	DoubleLinkedList<float> cb2(10);

	float tmp1;
	int tmp2;
	for (unsigned short i = 0; i != 5000; ++i) {
		tmp2 = abs(rand()) % 60;
		if (tmp2 < 10) { //Erase
			tmp2 = cb2.count();
			if (tmp2 != 0) {
				tmp2 = rand() % cb2.count();

				auto itemp = cb1.begin();
				for (int j = 0; j != tmp2; ++j, ++itemp);
				cb1.erase(itemp);

				cb2.erase(tmp2);
			}
		} else if (tmp2 < 20) { //Insert
			tmp1 = rand() / 3.0;

			try {
				tmp2 = cb2.count();
				if (tmp2 != 0) {
					tmp2 = rand() % cb2.count();

					auto itemp = cb1.begin();
					for (int j = 0; j != tmp2; ++j, ++itemp);
					cb1.insert(itemp, tmp1);

					cb2.insert(tmp2, tmp1);
				}
			} catch (const std::exception &) {
				cout << "double-linked list: 1 - fail! insert" << " | Test #" << i << endl;
				return;
			}
		} else if (tmp2 < 30) { //Push back
			tmp1 = rand() / 3.0;

			try {
				cb1.push_back(tmp1);

				cb2.push_back(tmp1);
			} catch (const std::exception &) {
				cout << "double-linked list: 1 - fail! push back" << " | Test #" << i << endl;
				return;
			}
		} else if (tmp2 < 40) { //Push front
			tmp1 = rand() / 3.0;

			try {
				cb1.push_front(tmp1);

				cb2.push_front(tmp1);
			} catch (const std::exception &) {
				cout << "double-linked list: 1 - fail! push front" << " | Test #" << i << endl;
				return;
			}
		} else if (tmp2 < 50) { //Pop back
			if (cb1.size() != cb2.count()) {
				cout << "double-linked list: 1 - fail! pop1 back" << " | Test #" << i << endl;
				return;
			}

			if (cb2.count() != 0) {
				try {
					tmp1 = cb1.back();
					cb1.pop_back();

					if (tmp1 != cb2.pop_back()) {
						cout << "double-linked list: 1 - fail! pop2 back" << " | Test #" << i << endl;
						return;
					}
				} catch (const std::exception &) {
					cout << "double-linked list: 1 - fail! pop3 back" << " | Test #" << i << endl;
					return;
				}
			}
		} else { //Pop front
			if (cb1.size() != cb2.count()) {
				cout << "double-linked list: 1 - fail! pop1 front" << " | Test #" << i << endl;
				return;
			}

			if (cb2.count() != 0) {
				try {
					tmp1 = cb1.front();
					cb1.pop_front();

					if (tmp1 != cb2.pop_front()) {
						cout << "double-linked list: 1 - fail! pop2 front" << " | Test #" << i << endl;
						return;
					}
				} catch (const std::exception &) {
					cout << "double-linked list: 1 - fail! pop3 front" << " | Test #" << i << endl;
					return;
				}
			}
		}
	}

	{ //Verify
		auto oth = cb1.begin();
		for (auto myb = cb2.begin(), mye = cb2.end(); myb != mye; ++myb) {
			if (*myb != *oth++) {
				cout << "double-linked list: 2 - fail! verify" << endl;
				return;
			}
		}
	}

	DoubleLinkedList<int> cb3(10), cb4(8);

	for (unsigned short i = 0; i != 10; ++i) {
		//Making a offset
		for (unsigned short j = 0; j != 3; ++j) {
			cb3.push_back(0);
			cb4.push_back(0);
		}
		for (unsigned short j = 0; j != 3; ++j) {
			cb3.pop_front();
			cb4.pop_front();
		}

		cb3.push_back(1); cb3.push_back(3); cb3.push_back(2); cb3.push_back(4);
		cb4.push_back(1); cb4.push_back(3); cb4.push_back(2); cb4.push_back(4);
		if (cb3 != cb4 || !(cb3 == cb4) || !(cb3 <= cb4) || !(cb3 >= cb4)) {
			cout << "double-linked list: 3 - fail! 1" << " | Test #" << i << endl;
			return;
		}
		cb3.pop_front(); cb3.pop_front(); cb3.pop_front(); cb3.pop_front();
		cb4.pop_front(); cb4.pop_front(); cb4.pop_front(); cb4.pop_front();

		cb3.push_back(1); cb3.push_back(3); cb3.push_back(3); cb3.push_back(4);
		cb4.push_back(1); cb4.push_back(3); cb4.push_back(2); cb4.push_back(4);
		if (cb3 < cb4 || cb3 <= cb4) {
			cout << "double-linked list: 3 - fail! 2" << " | Test #" << i << endl;
			return;
		}

		if (!(cb3 > cb4) || !(cb3 >= cb4)) {
			cout << "double-linked list: 3 - fail! 3" << " | Test #" << i << endl;
			return;
		}

		cb3.pop_back(); cb3.pop_back(); cb3.pop_back(); cb3.pop_back();
		cb4.pop_back(); cb4.pop_back(); cb4.pop_back(); cb4.pop_back();

		cb3.push_back(1); cb3.push_back(3); cb3.push_back(2); cb3.push_back(4);
		cb4.push_back(1); cb4.push_back(3); cb4.push_back(2);
		if (cb3 < cb4 || cb3 <= cb4) {
			cout << "double-linked list: 3 - fail! 2" << " | Test #" << i << endl;
			return;
		}

		if (!(cb3 > cb4) || !(cb3 >= cb4)) {
			cout << "double-linked list: 3 - fail! 3" << " | Test #" << i << endl;
			return;
		}

		cb3.pop_back(); cb3.pop_back(); cb3.pop_back(); cb3.pop_back();
		cb4.pop_back(); cb4.pop_back(); cb4.pop_back();
	}

	cout << "double-linked list: passed!" << endl;
}


/* SINGLE LINKED LIST UNIT TEST */
void UnitTest_SingleLinkedList() {
	list<float> cb1;
	SingleLinkedList<float> cb2(10);

	float tmp1;
	int tmp2;
	for (unsigned short i = 0; i != 5000; ++i) {
		tmp2 = abs(rand()) % 60;
		if (tmp2 < 10) { //Erase
			tmp2 = cb2.count();
			if (tmp2 != 0) {
				tmp2 = rand() % cb2.count();

				auto itemp = cb1.begin();
				for (int j = 0; j != tmp2; ++j, ++itemp);
				cb1.erase(itemp);

				cb2.erase(tmp2);
			}
		} else if (tmp2 < 20) { //Insert
			tmp1 = rand() / 3.0;

			try {
				tmp2 = cb2.count();
				if (tmp2 != 0) {
					tmp2 = rand() % cb2.count();

					auto itemp = cb1.begin();
					for (int j = 0; j != tmp2; ++j, ++itemp);
					cb1.insert(itemp, tmp1);

					cb2.insert(tmp2, tmp1);
				}
			} catch (const std::exception &) {
				cout << "single-linked list: 1 - fail! insert" << " | Test #" << i << endl;
				return;
			}
		} else if (tmp2 < 30) { //Push front
			tmp1 = rand() / 3.0;

			try {
				cb1.push_front(tmp1);

				cb2.push(tmp1);
			} catch (const std::exception &) {
				cout << "single-linked list: 1 - fail! push" << " | Test #" << i << endl;
				return;
			}
		} else { //Pop front
			if (cb1.size() != cb2.count()) {
				cout << "double-linked list: 1 - fail! pop1" << " | Test #" << i << endl;
				return;
			}

			if (cb2.count() != 0) {
				try {
					tmp1 = cb1.front();
					cb1.pop_front();

					if (tmp1 != cb2.pop()) {
						cout << "single-linked list: 1 - fail! pop2" << " | Test #" << i << endl;
						return;
					}
				} catch (const std::exception &) {
					cout << "single-linked list: 1 - fail! pop3" << " | Test #" << i << endl;
					return;
				}
			}
		}
	}

	{ //Verify
		auto oth = cb1.begin();
		for (auto myb = cb2.begin(), mye = cb2.end(); myb != mye; ++myb) {
			if (*myb != *oth++) {
				cout << "single-linked list: 2 - fail! verify" << endl;
				return;
			}
		}
	}

	SingleLinkedList<int> cb3(10), cb4(8);

	for (unsigned short i = 0; i != 10; ++i) {
		//Making a offset
		for (unsigned short j = 0; j != 3; ++j) {
			cb3.push(0);
			cb4.push(0);
		}
		for (unsigned short j = 0; j != 3; ++j) {
			cb3.pop();
			cb4.pop();
		}

		cb3.push(1); cb3.push(3); cb3.push(2); cb3.push(4);
		cb4.push(1); cb4.push(3); cb4.push(2); cb4.push(4);
		if (cb3 != cb4 || !(cb3 == cb4) || !(cb3 <= cb4) || !(cb3 >= cb4)) {
			cout << "single-linked list: 3 - fail! 1" << " | Test #" << i << endl;
			return;
		}
		cb3.pop(); cb3.pop(); cb3.pop(); cb3.pop();
		cb4.pop(); cb4.pop(); cb4.pop(); cb4.pop();

		cb3.push(1); cb3.push(3); cb3.push(3); cb3.push(4);
		cb4.push(1); cb4.push(3); cb4.push(2); cb4.push(4);
		if (cb3 < cb4 || cb3 <= cb4) {
			cout << "single-linked list: 3 - fail! 2" << " | Test #" << i << endl;
			return;
		}

		if (!(cb3 > cb4) || !(cb3 >= cb4)) {
			cout << "single-linked list: 3 - fail! 3" << " | Test #" << i << endl;
			return;
		}

		cb3.pop(); cb3.pop(); cb3.pop(); cb3.pop();
		cb4.pop(); cb4.pop(); cb4.pop(); cb4.pop();

		cb3.push(1); cb3.push(3); cb3.push(2); cb3.push(4);
		cb4.push(1); cb4.push(3); cb4.push(2);
		if (cb3 < cb4 || cb3 <= cb4) {
			cout << "single-linked list: 3 - fail! 2" << " | Test #" << i << endl;
			return;
		}

		if (!(cb3 > cb4) || !(cb3 >= cb4)) {
			cout << "single-linked list: 3 - fail! 3" << " | Test #" << i << endl;
			return;
		}

		cb3.pop(); cb3.pop(); cb3.pop(); cb3.pop();
		cb4.pop(); cb4.pop(); cb4.pop();
	}

	cout << "single-linked list: passed!" << endl;
}

void test_bst() {
	BinarySearchTree<float> bst{ 2, 4, 8, 16 };
	cout << "print: ";
	bst.print();
	cout << endl;
	bst.push(5);
	cout << "count: " << bst.count() << endl;
	bst.push(4);
	cout << "path: ";
	for (auto item : bst.path(4)) {
		cout << item << " ";
	}
	cout << endl;
	cout << "height: " << bst.height() << endl;
	bst.pop(4);
	cout << "print: ";
	bst.print();
	cout << endl;
	cout << "find 8: " << *bst.find(8) << endl;
	bst.push(9);
	bst.push(10);
	bst.push(11);
	cout << "unbalanced: ";
	bst.print();
	cout << endl;
	bst.balance();
	cout << "balanced: ";
	bst.print();
	cout << endl;

	BinarySearchTree<float> bst2;
	bst2.push(88);
	cout << "is bigger: " << (bst < bst2) << endl;
	cout << "is equal: " << (bst == bst2) << endl;

	cout << "Perfomance tests: " << endl;
	std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i != 500; ++i) {
		bst.push(rand() / 3.0);
	}
	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	std::cout << "push x500 time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms\n";

	begin = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i != 500; ++i) {
		bst.find(rand());
	}
	end = std::chrono::high_resolution_clock::now();
	std::cout << "look for random key x500 time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms\n";

	begin = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i != 500; ++i) {
		bst.pop(rand());
	}
	end = std::chrono::high_resolution_clock::now();
	std::cout << "erase random key x500 time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms\n";

	begin = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i != 500; ++i) {
		bst.path(rand());
	}
	end = std::chrono::high_resolution_clock::now();
	std::cout << "path of random key x500 time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms\n";

	begin = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i != 500; ++i) {
		bst.balance();
	}
	end = std::chrono::high_resolution_clock::now();
	std::cout << "balance x500 time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms\n";

	begin = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i != 500; ++i) {
		bst.height();
		bst.count();
	}
	end = std::chrono::high_resolution_clock::now();
	std::cout << "count + height x500 time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms\n";
}

void test_HashList() {
	HashList<int, float> test(0.7, 5), test2{ std::pair<int, float>(8,15), std::pair<int, float>(9,25), std::pair<int, float>(8,45) };

	test.emplace(1, 1.1);
	test.emplace(2, 2.1);
	test.emplace(3, 3.1);
	test.emplace(4, 4.1);
	test.emplace(5, 5.1);
	test.emplace(6, 6.1);
	test.emplace(7, 7.1);
	test.emplace(8, 8.1);
	cout << test << endl;
	auto bg = test.begin(), ed = test.end();
	ed--;
	for (; bg != ed; --ed) {
		cout << ed->first << " : " << ed->second << endl;
	}
	cout << ed->first << " : " << ed->second << endl;

	test2.erase(8);
	test2.erase(9);

	cout << "This is smaller than none? " << (test < test2) << "\nThis is bigger than none? " << (test > test2) << "\nEqual? " << (test == test2) << endl;
	cout << "How much of items? " << test.count() << endl;
	test.erase(3);
	cout << "And now? " << test.count() << endl;
	cout << "What about the element with key 3? " << test.find(3) << endl << endl;

	cout << "Perfomance check..." << endl;

	std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i != 5000; ++i) {
		test2.emplace(rand(), rand() / 3.0);
	}
	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	std::cout << "emplace x5000 time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms\n";

	begin = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i != 5000; ++i) {
		test2.find(rand());
	}
	end = std::chrono::high_resolution_clock::now();
	std::cout << "look for random key x5000 time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms\n";

	begin = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i != 5000; ++i) {
		test2.erase(rand());
	}
	end = std::chrono::high_resolution_clock::now();
	std::cout << "erase for random key x5000 time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms\n";

	cout << "Tests passed!" << endl << endl;
}