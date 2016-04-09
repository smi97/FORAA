#include <cstring>
#include <string>
#include <iostream>

class Queue {
private:
        int el;
        Queue *beg, *next, *end;
public:
    Queue()
    {
        next = nullptr;
        beg = nullptr;
        end = nullptr;
    }

    void push(int iEl)
    {
        Queue *tmp = new Queue;
        tmp->next = nullptr;
        tmp->el = iEl;
        if(end != nullptr)
            end->next = tmp;
        else
            beg = tmp;
        end = tmp;
    }

    int get() const
    {
        return beg->el;
    }

    int pop(int *iEl)
    {
        if(beg == nullptr) return 0;
        Queue *tmp;
        tmp = beg;
        *iEl = tmp->el;
        beg = tmp->next;
        free(tmp);
        if(beg == nullptr) end = nullptr;
        return 1;
    }

    bool isEmpty()
    {
        if(beg == nullptr) return true;
        return false;
    }
};
