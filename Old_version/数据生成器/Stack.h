#pragma once

#define Stack__Num 1000

template <class T>
class Stack
{
    int size;
    T element[Stack__Num];
    int top;

public:
    Stack()
    {
        size = Stack__Num;
        top = 0;
    }
    bool isFull()
    {
        return top == size;
    }
    bool isEmpty()
    {
        return top == 0;
    }
    bool push(T x)
    {
        if (isFull())
            return false;

        element[top++] = x;
        return true;
    }
    bool pop(T& x)
    {
        if (isEmpty())
            return false;

        x = element[--top];
        return true;
    }
    void clear()
    {
        top = 0;
    }
};