// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TQueue_H__
#define __TQueue_H__

#include <iostream>

// стек

template<class T>
class TStack
{
protected:
    size_t sz;
    T* pMem;
    int top;
public:
    TStack();
    TStack(size_t size);
    TStack(const TStack& s);
    TStack(TStack&& s);
    ~TStack();
    size_t size();
    void Push(T elem);
    T Pop();
    TStack& operator=(TStack& s);
    bool operator==(const TStack s);
    bool operator!=(const TStack s);
    bool IsFull();
    bool IsEmpty();
    void Resize(size_t newsize);
};

template<class T>
TStack<T>::TStack()
{
    sz = 0;
    pMem = nullptr;
    top = -1;
}

template<class T>
TStack<T>::TStack(size_t size)
{
    sz = size;
    pMem = new T[size];
    top = 0;
}

template<class T>
TStack<T>::TStack(const TStack& s)
{
    sz = s.sz;
    pMem = new T[size];
    if (pMem != nullptr)
    {
        for (int i = 0; i < sz; i++)
        {
            pMem[i] = s.pMem[i];
        }
    }
    top = s.top;
}

template<class T>
TStack<T>::TStack(TStack&& s)
{
    sz = s.sz;
    pMem = s.pMem;
    s.pMem = nullptr;
    s.sz = 0;
}

template<class T>
TStack<T>::~TStack()
{
    sz = 0;
    if (pMem != nullptr)
    {
        delete[] pMem;
        pMem = nullptr;
    }
    top = -1;
}
template<class T>
size_t TStack<T>::size()
{
    return top+1;
}

template<class T>
bool TStack<T>::IsEmpty()
{
    return top==-1;
}

template<class T>
bool TStack<T>::IsFull()
{
    return top==sz-1;
}

template<class T>
void TStack<T>::Push(T elem)
{
    if (isFull() || pMem == nullptr) throw std::exception();
    pMem(top) = elem;
    top++;
}
template<class T>
T TStack<T>::Pop()
{
    if (isEmpty() || pMem == nullptr) throw std::exception();
    T res = pMem(top);
    pMem(top) = 0;
    top--;
    return res;
}

template<class T>
TStack<T>& TStack<T>::operator=(TStack& s)
{
    if (this != &s)
    {
        top = s.top;
        sz = s.sz;
        if (sz == 0)
        {
            pMem = nullptr;
        }
        else 
        {
            pMem = new T[size];
            for (int i = 0; i < sz; i++)
            {
                pMem[i] = s.pMem[i];
            }
        }
    }
    return *this;
}

template<class T>
bool TStack<T>::operator==(const TStack s)
{
    return (sz == s.sz && pMem == s.pMem && top == s.top);
}

template<class T>
bool TStack<T>::operator!=(const TStack s)
{
    return !(this == s);
}

// очередь

template<class T>
class TQueue
{
protected:
    size_t sz;
    T* pMem;
    T* head;
    T* tail;
public:
    TQueue();
    TQueue(size_t size);
    TQueue(const TQueue& s);
    TQueue(TQueue&& s);
    ~TQueue();
    size_t size();
    bool IsFull();
    bool IsEmpty();
    void Push(T elem);
    T Pop();
    TQueue& operator=(TQueue& q);
    bool operator==(const TQueue q);
    bool operator!=(const TQueue q);
};

template<class T>
TQueue<T>::TQueue()
{
    sz = 0;
    pMem = nullptr;
    head = nullptr;
    tail = nullptr;
}

template<class T>
TQueue<T>::TQueue(size_t size)
{
    if (size < 0)
    {
        throw std::exception();
    }
    TQueue();
    sz = size;
    pMem = new T[size];
}

template<class T>
TQueue<T>::TQueue(const TQueue& s)
{
    sz = s.sz;
    pMem = new T[size];
    if (pMem != nullptr)
    {
        for (int i = 0; i < sz; i++)
        {
            pMem[i] = s.pMem[i];
        }
    }
    head = s.head;
    tail = s.tail;
}

template<class T>
TQueue<T>::TQueue(TQueue&& s)
{
    sz = s.sz;
    pMem = s.pMem;
    head = s.head;
    tail = s.tail;
    s.pMem = nullptr;
    s.head = nullptr;
    s.tail = nullptr;
    s.sz = 0;
}

template<class T>
TQueue<T>::~TQueue()
{
    sz = 0;
    if (pMem != nullptr)
    {
        delete[] pMem;
        pMem = nullptr;
    }
    head = nullptr;
    tail = nullptr;
}
template<class T>
size_t TQueue<T>::size()
{
    return head-tail;
}

template<class T>
bool TQueue<T>::IsEmpty()
{
    return head == tail;
}

template<class T>
bool TQueue<T>::IsFull()
{
    return head == size;
}
template<class T>
void TQueue<T>::Push(T elem)
{
    if (isFull() || pMem == nullptr) throw std::exception();
    if (head == sz)
    {
        *tail = elem;
        tail++;
    }
    else
    {
        *head = elem;
        head--;
    }
    top++;
}
template<class T>
T Pop()
{
    if (IsEmpty()) 
    {
        throw std::exception("Queue is empty");
    }

    T elem = *head;
    head++;
    return elem;
}

template<class T>
TQueue<T>& TQueue<T>::operator=(TQueue& s)
{
    if (this != &s)
    {
        delete[] pMem;
        head = s.head;
        tail = s.tail;
        sz = s.sz;
        if (sz == 0)
        {
            pMem = nullptr;
        }
        else
        {
            pMem = new T[size];
            for (int i = 0; i < sz; i++)
            {
                pMem[i] = s.pMem[i];
            }
        }
    }
    return *this;
}

template<class T>
bool TQueue<T>::operator==(const TQueue s)
{
    return (sz == s.sz && pMem == s.pMem && head == s.head && tail == s.tail);
}

template<class T>
bool TQueue<T>::operator!=(const TQueue s)
{
    return !(this == s);
}
#endif
