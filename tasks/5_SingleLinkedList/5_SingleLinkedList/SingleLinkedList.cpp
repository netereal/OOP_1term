#include <iostream>
using namespace std;

struct Node
{
	int data;
	Node* next;
	Node(int _data, Node* _next) : data(_data), next(_next) {}
};

class List
{
	Node* root;
public:
	List();
	~List();
	void AddNode(int _data);
	void DeleteNode(int _data);
	void ClearList();
	void View();
	void AddInTail(int _data);
	Node* Find(int _data);
	void List::Function(int N, List &list1, List &list2);
};

List::List()
{
	root = nullptr;
}
List::~List()
{
	Node* p;
	while (root)
	{
		p = root;
		root = root->next;
		delete p;
	}
}
void List::AddNode(int _data)
{
	if (!root)
	{
		root = new Node(_data, nullptr); return;
	}
	Node* p = new Node(_data, root);
	root = p;
}
void List::DeleteNode(int _data)
{
	if (root->data == _data)
	{
		Node* p = root;
		root = root->next;
		delete p;
	}
	Node* p = root;
	while (p->next->data != _data) p = p->next;
	Node* s = p->next;
	p->next = s->next;
	delete s;
}
void List::ClearList()
{
	Node* p;
	while (root)
	{
		p = root;
		root = root->next;
		delete p;
	}
}
void List::View()
{
	Node* p = root;
	while (p)
	{
		cout << p->data <<' ';
		p = p->next;
	}
}
Node* List::Find(int _data)
{
	Node* p = root;
	while (p && p->data != _data) p = p->next;
	return p;
}
void List::AddInTail(int _data)
{
	if (!root) { root = new Node(_data, nullptr); return; }
	Node* p = root;
	while (p->next) p = p->next;
	p->next = new Node(_data, nullptr);
}

void List::Function(int N, List &list1, List &list2)
{
	Node* p = root;
	while (p)
	{
		if (p->data > N) list1.AddInTail(p->data);
		else list2.AddInTail(p->data);
		p = p->next;
	}
}

int main()
{
	List list = List();
	List list1 = List();
	List list2 = List();

	for (int i = 0; i < 10; i++)
		list.AddNode(i);
	cout << "Start List:" << endl;
	list.View();
	cout << endl << endl;
	int m = 0;
	cout << "Input N: ";
	cin >> m;

	list.Function(m, list1, list2);

	cout << "List 1:" << endl;
	list1.View();
	cout << endl << endl;

	cout << "List 2:" << endl;
	list2.View();
	cout << endl << endl;

	system("pause");
}
