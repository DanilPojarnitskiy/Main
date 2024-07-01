#include "List2.h"

int main() {

	Mem* men = new Mem(1024);
	size_t size = 0;

	LinkedList mylist(*men);
	mylist.push_back(15);
	mylist.push_front(23);
	LinkedList::IteratorList iter = mylist.begin();
	LinkedList::IteratorList iterEnd = mylist.end();
	iterEnd.goToPrev();

	std::cout << *(double*)(iter.getElement(size)) << std::endl;
	std::cout << *(double*)iterEnd.getElement(size);
}
