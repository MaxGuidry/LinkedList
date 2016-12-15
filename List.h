#pragma once
#include<cassert>
template<typename Type>
struct NodeType;

template<typename Type>
class LinkedListIterator;

template<typename Type>
class LinkedListType
{
public:

	//Overload the assignment operator
	const LinkedListType<Type>& operator= (const LinkedListType<Type>& otherList)
	{
		copyList(otherList);
		return *this;
	}

	//Initialize the list to an empty state
	//Postcondition: first = NULL, last = NULL, count = 0;
	void initializeList()
	{
		first = new NodeType<Type>;
		last = new NodeType<Type>;
		count = 0;
	}

	//Function to determine whether the list is empty
	//Postcondition: Returns true if the list is empty otherwise it returns false
	bool isEmptyList() const
	{
		return (count == 0) ? true : false;
	}

	//Function to output the data contained in each node
	//Postcondition: Node
	void print() const
	{
		NodeType<Type> * temp = new NodeType<Type>;
		int counter = 0;
		for (; temp != NULL; counter++)
		{
			if (counter == 0)
			{
				temp = first;
			}
			else
			{
				temp = temp->link;
			}
			if (temp != nullptr)
				std::cout << temp->info << ", ";
		}
	}

	//Function to insert node at the end of the list
	//Postcondition: first points to the new list, node is inserted 
	//at the beginning of the list, last points to the last node in
	//the list, and count is incremented by 1;
	void insertBack(const Type& node)
	{
		if (count == 0)
		{
			first->info = node;
			first->link = nullptr;
			last->info = node;
			last->link = nullptr;
			count++;
		}
		else
		{
			NodeType<Type> *newNode = new NodeType<Type>;
			last->link = newNode;
			last = newNode;
			if (count == 1)
				first->link = newNode;
			last->info = node;
			last->link = nullptr;
			count++;
		}
	}

	//Function to insert node at the begining of the list
	//Postcondition: first points to the new list, node is inserted 
	//at the beginning of the list, last points to the last node in
	//the list, and count is incremented by 1
	void insertFirst(const Type & node)
	{
		if (count == 0)
		{
			first->info = node;
			first->link = nullptr;
			last->info = node;
			last->link = nullptr;
			count++;
		}
		else
		{
			NodeType<Type> *newNode = new NodeType<Type>;
			newNode->link = first;
			first = newNode;
			first->info = node;
			count++;
		}
	}

	//Default constructor
	//Initializes the list to an empty state
	//Postcondition: first = NULL, last = NULL, count = 0;
	LinkedListType()
	{
		first = new NodeType<Type>;
		last = new NodeType<Type>;
		count = 0;
	}

	//Function to return the first element in the list
	//Precondition: The list must exist and must not be empty
	//Postcondition: If the list is empty, the program terminates; otherwise,
	//the first element of the list is returned
	Type front() const
	{
		assert(count != 0);
		return first->info;
	}

	//Function to return the last element in the list
	//Precondition: The list must exist and must not be empty
	//Postcondition: If the list is empty, the program terminates; otherwise,
	//the last element of the list is returned
	Type back() const
	{
		assert(count != 0);
		return last->info;
	}

	//Function to determine whether node is in the list
	//Postcondition: Returns true if node is in the list
	//otherwise teh value false is returned
	bool search(const Type& nodeInfo)
	{
		LinkedListIterator<Type> temp = LinkedListIterator<Type>(begin());
		while (*temp != NULL)
		{
			if (*temp == nodeInfo)
				return true;
			++temp;
		}
		return false;
	}

	//Function to return an iterator at the begining of the linked list
	//Postcondition: Returns an iteratir such that the current is set to first
	LinkedListIterator<Type> begin()
	{
		return LinkedListIterator<Type>(first);
	}

	//Funcion to rturn an iterator at the end of the linked list
	//Postcondition: Returns an iterator such that current is set to NULL
	LinkedListIterator<Type> end()
	{
		return LinkedListIterator<Type>(last->link);
	}

	//Function to return the number of nodes in the list
	//Postcondition: The value of count is returned
	const int length()
	{
		return count;
	}

	//Function to delete all the nodes from the list
	//Postcondition: first = NULL, last = NULL, count = 0;
	void destroyList()
	{
		NodeType<Type> * temp = first;
		while (temp != NULL)
		{
			NodeType<Type> *tmp = temp;
			temp = temp->link;
			delete tmp;
		}
		first = NULL;
		last = NULL;
		count = 0;
	}

	//Function to delete node from the list
	//Postcondition: If found, the node containing the node is deleted from the list. first points to
	//the first node, last points to the last node of the update list, and count is decremented by 1
	void deleteNode(const Type& nodeInfo)
	{

		NodeType<Type>* node = first;
		if (node == nullptr)
			return;
		if (node->info == nodeInfo)
		{
			NodeType<Type> *tmp = node;
			node = node->link;
			delete tmp;
			count--;
			first = node;
		}
		else
		{
			while (node->link != NULL)
			{
				if (node->link->info == nodeInfo)
				{
					NodeType<Type>* tmp = node->link;
					node->link = node->link->link;
					delete tmp;
					count--;
					break;
				}
				node = node->link;
			}
		}
	}

	//copy constructor
	LinkedListType<Type>(const LinkedListType<Type>otherList)
	{
		copyList(otherList);
	}

	//deconstructor
	//Deletes all the nodes from the list
	//Postcondition: The list object is destroyed
	~LinkedListType<Type>()
	{
		destroyList();
	}
protected:
	int count; //variable that stores the number of elements in the list.
	NodeType<Type> * first; //pointer to the first node of the list.
	NodeType<Type> * last;  //pointet to the last node of the list.
private:
	//Function to make a copy of list
	//Postcondition: A copy of list is created and assigned to this list
	void copyList(const LinkedListType<Type>&otherList)
	{
		first = otherList.first;
		last = otherList.last;
		count = otherList.count;
	}
};


template<typename Type>
struct NodeType
{
public:
	Type info;
	NodeType<Type> * link;
};


template<typename Type>
class LinkedListIterator
{
private:
	NodeType<Type> * current;
public:
	//Default constructor
	//Postcondition: current = NULL
	LinkedListIterator() {}

	//Constructor with parameter
	//Postcondition: current = node
	LinkedListIterator(NodeType<Type> *a) :current(a) {}
	
	//Function to overlaod the dereferencing operator *
	//Postcondition:Returns the info contained in the node
	Type operator*	()
	{
		if (current == nullptr)
			return NULL;
		return current->info;
	}

	//Overload the pre-increment operator
	//Postcondition: The iterator is advanced to the next node
	LinkedListIterator<Type> operator++()
	{
		current = current->link;
		return *this;
	}

	//Overlaod the equality operator
	//Postcondition: Returns true if this iterator is equal to the 
	//iterator specified by right otherwise returns false
	bool operator==(const LinkedListIterator<Type>& a)
	{
		return (current == a.current) ? true : false;
	}

	//Overlaod the not equal operator
	//Postcondition: Returns true if this iterator is not equal to the 
	//iterator specified by right otherwise returns false
	bool operator!=(const LinkedListIterator<Type>& a)
	{
		return (current != a.current) ? true : false;
	}
};