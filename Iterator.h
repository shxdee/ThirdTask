#pragma once

struct EndOfIterator{};
typedef int TElem;

struct Node
{
	TElem data;
	Node *next;
	Node *prev;
};

class Iterator {
public:
	virtual void start() = 0;
	virtual TElem getElement() const = 0;
	virtual void next() = 0;
	virtual void prev() = 0;
	virtual bool finish() const = 0;
	virtual Node* getCurrent() const = 0;
	virtual void setCurrent(Node* current) = 0;
};