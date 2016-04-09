#include <cstring>
#include <string>
#include <iostream>

class Queue {
private:
    struct Que
    {
        int el;
        Que *beg, *next, *end;
    } *queue;
public:
    Queue()
    {
        queue = new Que;
        queue->beg = nullptr;
        queue->end = nullptr;
    }

    void push(int iEl)
    {
        Que *tmp = new Que;
        tmp->next = nullptr;
        tmp->el = iEl;
        if(queue->end != nullptr)
            queue->end->next = tmp;
        else
            queue->beg = tmp;
        queue->end = tmp;
    }

    int get() const
    {
        return queue->beg->el;
    }

    int pop(int *iEl)
    {
        if(queue->beg == nullptr) return 0;
        Que *tmp;
        tmp = queue->beg;
        *iEl = tmp->el;
        queue->beg = tmp->next;
        free(tmp);
        if(queue->beg == nullptr) queue->end = nullptr;
        return 1;
    }

    bool isEmpty()
    {
        if(queue->beg == nullptr) return true;
        return false;
    }
};
