#include "List2.h"


Node::Node(double data) {
    this->data = data;
    this->prev = this->next = NULL;
}

LinkedList::LinkedList(MemoryManager &mem) : ContainerList(mem)
{
    mm = &mem;
    this->head = this->tail = NULL;
}

Node* LinkedList::push_front(double data) {
    //Node* ptr = (Node*)(mm->allocMem(data));
    Node* ptr = new Node(data);
    ptr->next = head;
    if (head != NULL)
        head->prev = ptr;
        if (tail == NULL)
            tail = ptr;
            head = ptr;
 
            return ptr;
}
 
 
Node* LinkedList::push_back(double data) {
    //Node* ptr = (Node*)(mm->allocMem(data));
    Node* ptr = new Node(data);
    ptr->prev = tail;
    if (tail != NULL)
        tail->next = ptr;
    if (head == NULL)
    head = ptr;
    tail = ptr;
 
    return ptr;
}

void LinkedList::pop_front() {
    if (head == NULL) return;
                   
    Node* ptr = head->next;
    if (ptr != NULL)
        ptr->prev = NULL;
    else
        tail = NULL;
 
    mm->freeMem(head);
    head = ptr;
}
 
void LinkedList::pop_back() {
    if (tail == NULL) return;
 
    Node* ptr = tail->prev;
    if (ptr != NULL)
        ptr->next = NULL;
    else
        head = NULL;
 
    mm->freeMem(tail);
    tail = ptr;
}

void* LinkedList::IteratorList::getElement(size_t &size)  {
    size = sizeof(current_pos->data);
    return &(current_pos->data);
}

bool LinkedList::IteratorList::hasNext() {
    return current_pos->next == NULL ? false : true;
}

void  LinkedList::IteratorList::goToNext() {
    current_pos = current_pos->next;
}

void  LinkedList::IteratorList::goToPrev() {
    current_pos = current_pos->prev;
}

bool LinkedList::IteratorList::equals(LinkedList::Iterator *right) {
    return current_pos == ((IteratorList*)right)->current_pos ? true : false;
}