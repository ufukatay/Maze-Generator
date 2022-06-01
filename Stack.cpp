#include <iostream>
#include "Stack.h"
using namespace std;

template <class T>
Stack<T>::Stack()
{
	ptop = NULL; 
}

template <class T>
void Stack<T>::push(T c)
{
	Node<T> *newNode;


	newNode = new Node<T>;
	newNode->value = c;

	
	if (isEmpty())
	{
		ptop = newNode;
		newNode->next = NULL;
	}
	else	
	{
		newNode->next = ptop;
		ptop = newNode;
	}
}

template <class T>
void Stack<T>::pop(T &c)
{
	Node<T> *temp;

	if (isEmpty())
	{
		cout << "The stack is empty.\n";
	}
	else
	{
		c = ptop->value;
		temp = ptop->next;
		delete ptop;
		ptop = temp;
	}
}

template <class T>
bool Stack<T>::isEmpty()
{
	bool status;

	if (ptop == NULL)
		status = true;
	else
		status = false;

	return status;
}

template <class T>
T &Stack<T>::top()
{
	return ptop->value;
}