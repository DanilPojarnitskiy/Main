#include "Container.h"
#include "Mem.h"

struct Node
{
    double data;
    Node* prev, * next;
    Node(double data);
};

class ContainerList : Container 
{
public:
    class IteratorList : Iterator
    {
    public:

        IteratorList(Node* node) {
            current_pos = node;
        }

        Node* current_pos;

        void* getElement(size_t &size) override;
        
        // Возвращает true, если есть следующий элемент, иначе false.
        bool hasNext() override;

        // Переход к следующему элементу.
        void goToNext() override;

        void goToPrev();

        // // проверка на равенство итераторов
        bool equals(Iterator *right) override;
    };

    ContainerList(MemoryManager &mem): Container(mem) {}

};


class LinkedList : public ContainerList
{
    
public:
    Node* head, * tail;

    LinkedList(MemoryManager &mem);

    Node* push_front(double data);
 
    Node* push_back(double data);

    void pop_front();

    void pop_back();

    IteratorList begin() { return IteratorList(head); }

    IteratorList end() { return IteratorList(tail->next); }

private:
    MemoryManager *mm;
};