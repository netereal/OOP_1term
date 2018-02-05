#include <iostream>
#include <vector>
#include <ctime>
using namespace std;
const int N = 10;

struct Node
{
	int data;
	Node* next;
	Node(int _data, Node* _next) : data(_data), next(_next) {}
};

class Queue
{
	Node* head;
	Node* tail;
public:
	Queue();
	~Queue();

	void Push(int _data);
	void Pop();
	int Show();

	Node* at(int i);
	int Size();

	void InsertionSort();
	void QuickSort();
private:
	void quick(int left, int right);
	void insertion(int n);
};

Queue::Queue()
{
	head = nullptr;
	tail = nullptr;
}
Queue::~Queue()
{
	tail = nullptr;
	while (head)
	{
		Node* p = head;
		head = head->next;
		delete p;
	}
}

void Queue::Push(int _data)
{
	if (!head)
	{
		head = new Node(_data, nullptr);
		tail = head;
		return;
	}
	head = new Node(_data, head);
}
void Queue::Pop()
{
	Node* p = head;
	while (p->next != tail) p = p->next;
	tail = p;
	delete p->next;
	p->next = nullptr;
}
int Queue::Show()
{
	return tail->data;
}

Node* Queue::at(int i)
{
	if (i < 0) return 0;
	Node* p = head;
	while (i > 0) { if (!p) return 0; p = p->next; i--; }
	return p;
}
int Queue::Size()
{
	Node* p = head;
	int i = 0;
	while (p)
	{
		i++;
		p = p->next;
	}
	return i;
}

void Queue::InsertionSort()
{
	insertion(Size());
}
void Queue::QuickSort()
{
	quick(0, Size() - 1);
}

void Queue::quick(int left, int right)
{
	int i = left, j = right;
	int pivot = at((left + right) / 2)->data;
	while (i <= j)
	{
		while (at(i)->data < pivot) i++;
		while (at(j)->data > pivot) j--;
		if (i <= j)
		{
			swap(at(i)->data, at(j)->data);
			i++;
			j--;
		}
	}
	if (left < j) quick(left, j);
	if (i < right) quick(i, right);
}
void Queue::insertion(int n)
{
	int p, k;
	for (int i = 1; i < n; i++)
	{
		p = at(i)->data;
		k = i - 1;
		while (k >= 0 && at(k)->data > p)
		{
			at(k + 1)->data = at(k)->data;
			at(k)->data = p;
			k--;
		}
	}
}

int main()
{
	srand(time(NULL));

	Queue qu1 = Queue();
	Queue qu2 = Queue();

	for (int i = 0; i < N; i++)
	{
		qu1.Push(rand() % 10 + 1);
		qu2.Push(rand() % 10 + 1);
	}

	cout << "Queue 1: " << endl;
	for (int i = 0; i < qu1.Size(); i++) cout << qu1.at(i)->data << endl;
	cout << endl << endl;

	cout << "Queue 1: QuickSort" << endl;
	qu1.QuickSort();
	for (int i = 0; i < qu1.Size(); i++) cout << qu1.at(i)->data << endl;
	cout << endl << endl;

	cout << "Queue 2: " << endl;
	for (int i = 0; i < qu2.Size(); i++) cout << qu2.at(i)->data << endl;
	cout << endl << endl;

	cout << "Queue 2: InsertionSort" << endl;
	qu2.InsertionSort();
	for (int i = 0; i < qu2.Size(); i++) cout << qu2.at(i)->data << endl;
	cout << endl << endl;


	system("pause");
}
