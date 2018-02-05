#include <iostream>

using namespace std;


class Queue {
	static const int SIZE = 100; // максимальный размер кучи
	int *h;         // указатель на массив кучи
	int HeapSize; // размер кучи
public:
	Queue();  // конструктор кучи
	void addelem(int);  // добавление элемента кучи
	void outHeap();  // вывод элементов кучи в форме кучи
	void out();  // вывод элементов кучи в форме массива
	int getmax();  // удаление вершины (максимального элемента)
	void heapify(int);  // упорядочение кучи
};

Queue::Queue() {
	h = new int[SIZE];
	HeapSize = 0;
}

void Queue::addelem(int n) {
	int i, parent;
	i = HeapSize;
	h[i] = n;
	parent = (i - 1) / 2;		//parent
	while (parent >= 0 && i > 0) {
		if (h[i] > h[parent]) {
			int temp = h[i];
			h[i] = h[parent];
			h[parent] = temp;
		}
		i = parent;
		parent = (i - 1) / 2;
	}
	HeapSize++;
}

void Queue::outHeap(void) {
	int i = 0;
	int k = 1;
	while (i < HeapSize) {
		while ((i < k) && (i < HeapSize)) {
			cout << h[i] << " ";
			i++;
		}
		cout << endl;
		k = k * 2 + 1;
	}
}

void Queue::out(void) {
	for (int i = 0; i< HeapSize; i++) {
		cout << h[i] << " ";
	}
	cout << endl;
}

void Queue::heapify(int i) {
	int left, right;
	int temp;
	left = 2 * i + 1;		//left
	right = 2 * i + 2;		//right
	if (left < HeapSize) {
		if (h[i] < h[left]) {
			temp = h[i];
			h[i] = h[left];
			h[left] = temp;
			heapify(left);
		}
	}
	if (right < HeapSize) {
		if (h[i] < h[right]) {
			temp = h[i];
			h[i] = h[right];
			h[right] = temp;
			heapify(right);
		}
	}
}

int Queue::getmax(void) {
	int x;
	x = h[0];
	h[0] = h[HeapSize - 1];
	HeapSize--;
	heapify(0);
	return(x);
}

int main() {
	Queue heap;
	int k;
	system("cls");
	for (int i = 0; i<5; i++) {
		cout << "Input element: " << i + 1 << ": ";
		cin >> k;
		heap.addelem(k);
	}
	heap.outHeap();
	cout << endl;
	heap.out();
	cout << endl << "Max: " << heap.getmax();
	cout << endl << "New heap: " << endl;
	heap.outHeap();
	cout << endl;
	heap.out();
	cout << endl << "Max: " << heap.getmax();
	cout << endl << "New heap: " << endl;
	heap.outHeap();
	cout << endl;
	heap.out();
	system("pause");
	return 0;
}