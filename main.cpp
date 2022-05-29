#include "IteratorList.h"
using namespace std;

int main()
{
    IteratorList test1 = IteratorList();
    IteratorList::ListIterator* it = nullptr;

    test1.addElem(0);
    test1.addElem(1);
    test1.addElem(2);
    test1.addElem(3);
    test1.addElem(4);
    it = test1.findElem(0);
    it->start();
    while (!it->finish()) {
        it->next();
        cout << it->getElement() << endl;
    }
    cout << endl;

    test1.makeEmpty();
    cout << test1.isEmpty() << endl;
    cout << endl;

    test1.addElem(2);
    test1.addElem(41);
    test1.addElem(5);
    test1.addElem(6000);
    test1.addElem(76);
    it = test1.findElem(2);
    test1.addElem(500, *it);
    it->start();
    while (!it->finish()) {
        it->next();
        cout << it->getElement() << endl;
    }
    cout << endl;

    it = test1.findElem(500);
    test1.deleteElem(*it);
    it->start();
    while (!it->finish()) {
        it->next();
        cout << it->getElement() << endl;
    }
    cout << endl;
}