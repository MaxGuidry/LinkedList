#include<iostream>
#include"List.h"
void list(NodeType<int> *);
int main()
{
	
	LinkedListType<int> *test = new LinkedListType<int>();
	LinkedListType<int> *second = new LinkedListType<int>();
	test->insertBack(2);
	test->insertBack(5);
	test->insertBack(9);
	test->insertBack(1);
	test->insertFirst(4);
	test->deleteNode(9);
	*second=*test;
	second->print();
	test->front();
	LinkedListIterator<int> temp =LinkedListIterator<int>(test->begin());
	bool d=test->search(7);
	test->destroyList();
	system("pause");
	return 0;
}

void list(NodeType<int> * node)
{
	while (node != NULL)
	{
		std::cout << node->info;
		node = node->link;
	}
}