#pragma once

#include "List.h"
#include "iostream"

struct CurrentBufferException{};
struct ListIsEmptyException{};

class IteratorList : public List {
private:
	Node *head;
	int size;
public:
	class ListIterator : public Iterator {
	private:
		int index;
		IteratorList *list;
		Node *current;
	public:
		ListIterator(IteratorList &theList);
		~ListIterator();
		void start();
		TElem getElement() const;
		void next();
		void prev();
		bool finish() const;
		Node* getCurrent() const;
		void setCurrent(Node* current);
	};
	friend class ListIterator;
	IteratorList();
	IteratorList(const IteratorList &copy);
	IteratorList(IteratorList &&copy);
	~IteratorList();
	void addElem(const TElem &elem);
	void addElem(const TElem &elem, Iterator &iter);
	IteratorList& operator=(const IteratorList &obj);
	IteratorList& operator=(IteratorList &&obj);
	void deleteElem(Iterator &iter);
	void makeEmpty();
	bool isEmpty() const;
	int getSize() const;
	IteratorList::ListIterator* findElem(const TElem &elem);
	IteratorList::ListIterator* getIterator();
};