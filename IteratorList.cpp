#include "IteratorList.h"

IteratorList::IteratorList() {
	head = new Node;
	head->data = 0;
	head->next = head;
	head->prev = head;
	size = 0;
}

IteratorList::IteratorList(const IteratorList& copy) {
	head = new Node;
	head->data = 0;
	head->next = head;
	head->prev = head;
	size = copy.size;
	Node *buf = copy.head->next;
	for (int i = 0; i < size; i++) {
		Node *temp = new Node;
		temp->data = buf->data;
		temp->next = head->next;
		temp->prev = head;
		head->next = temp;
		head = temp;
		buf = buf->next;
	}
	head->next->prev = head;
	head = head->next;
}

IteratorList::IteratorList(IteratorList&&  copy) {
	head = new Node;
	head->data = 0;
	head->next = head;
	size = copy.size;
	copy.head = copy.head->next;
	for (int i = 0; i < this->size; i++) {
		Node *temp = new Node;
		temp->data = copy.head->data;
		temp->next = head->next;
		temp->prev = head;
		head->next = temp;
		head = temp;
		Node *buf = copy.head->next;
		delete copy.head;
		copy.head = buf;
	}
	delete copy.head;
	head->next->prev = head;
	head = head->next;
}

IteratorList::~IteratorList() {
	if (size > 0) {
		makeEmpty();
	}
	delete head;
}

IteratorList& IteratorList::operator=(const IteratorList &obj) {
	if (this == &obj) {
		return *this;
	}
	if (size > 0) {
		makeEmpty();
	}
	size = obj.size;
	Node *buf = obj.head->next;
	for (int i = 0; i < this->size; i++) {
		Node *temp = new Node;
		temp->data = buf->data;
		temp->next = head->next;
		temp->prev = head;
		head->next = temp;
		head = temp;
		buf = buf->next;
	}
	head->next->prev = head;
	head = head->next;
	return *this;
}

IteratorList& IteratorList::operator=(IteratorList &&obj) {
	std::swap(head, obj.head);
	size = obj.size;
	return *this;
}

void IteratorList::addElem(const TElem &element) {
	Node *temp = new Node;
	temp->data = element;
	temp->next = head->next;
	temp->prev = head;
	if (head->prev == head) {
		head->prev = temp;
	}
	head->next = temp;
	size++;
}

void IteratorList::addElem(const TElem &element, Iterator &iter) {
	Node *temp = new Node;
	temp->data = element;
	temp->next = (iter.getCurrent())->next;
	temp->prev = (iter.getCurrent());
	(iter.getCurrent())->next->prev = temp;
	(iter.getCurrent())->next = temp;
	size++;
}

void IteratorList::deleteElem(Iterator &iter) {
	if (size == 0) {
		throw ListIsEmptyException();
	}
	if (iter.getCurrent() == head) {
		throw CurrentBufferException();
	}
	Node *currentElem = iter.getCurrent();
	Node *temp = currentElem->next;
	currentElem->next->prev = currentElem->prev;
	currentElem->prev->next = currentElem->next;
	delete (currentElem);
	iter.setCurrent(temp);
	size--;
}

void IteratorList::makeEmpty() {
	head = head->next;
	while (size>0) {
		Node *temp = head->next;
		delete head;
		head = temp;
		size--;
	}
	head->next = head;
	head->prev = head;
}

bool IteratorList::isEmpty() const{
	return (size==0);
}

int IteratorList::getSize() const{
	return size;
}

IteratorList::ListIterator* IteratorList::findElem(const TElem &elem) {
	IteratorList::ListIterator* obj = new ListIterator(*this);
	while (!obj->finish()) {
		obj->next();
		if (elem == obj->getElement()) {
			return obj;
		}
	}
	throw NoElemException();
}

IteratorList::ListIterator* IteratorList::getIterator() {
	return new ListIterator(*this);
}

IteratorList::ListIterator::ListIterator(IteratorList &theList) {
	index = 0;
	list = &theList;
	current = list->head;
}

IteratorList::ListIterator::~ListIterator() {

}

void IteratorList::ListIterator::start() {
	current = list->head;
	index = 0;
}

TElem IteratorList::ListIterator::getElement() const {
	if (current == list->head) {
		throw BufferException();
	}
	return current->data;
}

void IteratorList::ListIterator::next() {
	if (finish()) {
		throw EndOfIterator();
	}
	current = current->next;
	index++;
}

void IteratorList::ListIterator::prev() {
	if (current == list->head) {
		throw BufferException();
	}
	current = current->prev;
	index--;
}

bool IteratorList::ListIterator::finish() const {
	return(index == list->size);
}

Node* IteratorList::ListIterator::getCurrent() const {
	return current;
}

void IteratorList::ListIterator::setCurrent(Node* Current) {
	this->current = current;
}