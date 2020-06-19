#ifndef LIST_HPP
#define LIST_HPP

/*
 * MyClass - клас який потрібно замінити на ваш
 * і видалити цей коментар, звісно)
*/

#include <stdexcept>
#include <string>

struct Node
{
	MyClass Value;
	Node* Next;
	Node(MyClass value, Node* next) 
		: Value(value), Next(next)

	Node();
	~Node();
};


class List
{
public:

	List();
	~List();
	
	//Inserts element BEFORE index
	void Insert(MyClass element);

	//Removes element at position
	void Remove(int index);
	void Remove(MyClass value);

	//returns root node pointer
	Node* GetRoot();

private:
	
	//Root node of list
	Node* Root;
};
#endif // !LIST_HPP