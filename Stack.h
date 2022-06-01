#ifndef STACK_H
#define STACK_H

struct cell{
	
	cell(){
		x=0;
		y=0;
		l=1;
		r=1;
		u=1;
		d=1;
		pre=0;
	}
	int x, y, l, r, u, d, pre;
};

template <class T>
struct Node
{
	T value;
	Node<T> *next;
};

template <class T>
class Stack
{
private:
	Node<T> *ptop;

public:
	
	Stack<T>();
	void push(T);
	void pop(T&);
	bool isEmpty();
	T &top();
};

#include "Stack.cpp"
#endif