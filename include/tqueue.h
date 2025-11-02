// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TQueue_H__
#define __TQueue_H__

#include <iostream>

const int MAX_STACK_SIZE = 100000;
const int MAX_QUEUE_SIZE = 100000;
// стек

template<class T>
class TStack
{
protected:
    T** data;
    int len;
    bool isNew;
    int top;
public:
    TStack();
    TStack(int len_);
    TStack(const TStack& s);
    TStack(TStack&& s);
    TStack(T** data_, int len_);
    ~TStack();
    int GetLen();
    void Resize(int newSize);
    void SetData(T** data_, int len_);

    void Push(T elem);
    T Pop();
    TStack& operator=(const TStack& s);
    TStack& operator=(TStack&& s);
    bool operator==(const TStack& s) const;
    bool operator!=(const TStack& s) const;
    bool IsFull() const;
    bool IsEmpty() const;
    
    template <class O>
    friend std::ostream& operator<<(std::ostream& o, TStack<O> t);
    template <class I>
    friend std::istream& operator>>(std::istream& i, TStack<I> t);
};

template<class T>
inline TStack<T>::TStack()
{
    len = 0;
    data = nullptr;
    isNew = true;
    top = 0;
}

template<class T>
inline TStack<T>::TStack(int len_) : TStack<T>::TStack()
{
    if (len_ < 0  || len_ > MAX_STACK_SIZE)
    {
        throw std::exception();
    }
    else if (len_ > 0)
    {
        len = len_;
        data = new T * [len];
        for (int i = 0; i < len; i++)
        {
            data[i] = nullptr;
        }
    }
}

template<class T>
inline TStack<T>::TStack(const TStack& s) : TStack<T>::TStack()
{
    if (s.len > 0)
    {
        len = s.len;
        data = new T*[len];
        for (int i = 0; i < len; i++)
        {
            if (s.data[i] != nullptr)
            {
                data[i] = new T(*(s.data[i]));
            }
            else
            {
                data[i] = nullptr;
            }
        }
    }
    top = s.top;
}

template<class T>
inline TStack<T>::TStack(TStack&& s)
{
    len = s.len;
    data = s.data;
    isNew = s.isNew;
    top = s.top;
    s.len = 0;   
    s.data = nullptr; 
    s.isNew = true;
    s.top = 0;
}

template<class T>
inline TStack<T>::TStack(T** data_, int len_) : TStack<T>::TStack()
{
    if (len_ < 0 || len_ > MAX_STACK_SIZE)
    {
        throw std::exception();
    }
    else if (len_ > 0)
    {
        len = len_;
        data = data_;
        isNew = false;
        for (int i = 0; i < len; i++)
        {
            if (data[i] == nullptr)
            {
                top = i;
                break;
            }
        }
    }
}

template<class T>
inline TStack<T>::~TStack()
{
    if (isNew)
    {
        if (data != nullptr)
        {
            for (int i = 0; i < len; i++)
            {
                delete data[i];
                data[i] = nullptr;
            }
            delete[] data;
        }
    }
    data = nullptr;
    isNew = true;
    len = 0;
}

template<class T>
inline int TStack<T>::GetLen()
{
    return len;
}


template<class T>
inline void TStack<T>::Resize(int newSize)
{
    if (newSize < 0 || newSize > MAX_STACK_SIZE)
    {
        throw std::exception();
    }
    else if (newSize == 0)
    {
        if (isNew)
        {
            if (data != nullptr)
            {
                for (int i = 0; i < len; i++)
                {
                    delete data[i];
                }
                delete[] data;
            }
        }
        data = nullptr;
        isNew = true;
        len = 0;
    }
    else if (len == newSize)
    {
        return;
    }
    else
    {
        T** newData = new T * [newSize];
        for (int i = 0; i < newSize; i++)
        {
            if (i < len)
            {
                newData[i] = data[i];
            }
            else
            {
                newData[i] = nullptr;
            }
        }
        if (isNew)
        {
            delete[] data;
        }
        data = newData;
        len = newSize;
        isNew = true;
    }
}

template<class T>
inline void TStack<T>::SetData(T** data_, int len_)
{
    if (len_ < 0 || len_ > MAX_STACK_SIZE)
    {
        throw std::exception();
    }
    else if (len_ == 0)
    {
        if (isNew)
        {
            if (data != nullptr)
            {
                for (int i = 0; i < len; i++)
                {
                    delete data[i];
                }
                delete[] data;
            }
        }
        data = nullptr;
        isNew = true;
        len = 0;
    }
    else if (len_ > 0)
    {
        if (isNew)
        {
            for (int i=0; i < len; i++)
            {
                delete data[i];
            }
            delete[] data;
        }
        data = nullptr;
        data = data_;
        len = len_;
        for (int i = 0; i < len; i++)
        {
            if (data[i] == nullptr)
            {
                top = i;
                break;
            }
        }
    }
}

template<class T>
inline void TStack<T>::Push(T elem)
{
    if (IsFull())
    {
        throw std::exception();
    }
    data[top] = new T(elem);
    top++;
}

template<class T>
inline T TStack<T>::Pop()
{
    if (IsEmpty())
    {
        throw std::exception();
    }
    top--;
    T res = *(data[top]);
    delete data[top];
    data[top] = nullptr;
    return res;
}

template<class T>
inline TStack<T>& TStack<T>::operator=(const TStack& s)
{
    if (this == &s) {
        return *this; // Защита от самоприсваивания
    }

    // Очищаем текущие данные
    if (isNew && data != nullptr) {
        for (int i = 0; i < len; i++) {
            delete data[i];
        }
        delete[] data;
    }

    // Копируем данные из s
    len = s.len;
    top = s.top;
    isNew = true;

    if (s.len > 0) 
    {
        data = new T * [len];
        for (int i = 0; i < len; i++) 
        {
            if (s.data[i] != nullptr)
            {
                data[i] = new T(*(s.data[i]));
            }
            else
            {
                data[i] = nullptr;
            }
        }
    }
    else {
        data = nullptr;
    }

    return *this;
}

template<class T>
inline TStack<T>& TStack<T>::operator=(TStack&& s)
{
    if (this == &s) 
    {
        return *this;
    }

    // Очищаем текущие данные
    if (isNew && data != nullptr) 
    {
        for (int i = 0; i < len; i++) 
        {
            delete data[i];
        }
        delete[] data;
    }

    len = s.len;
    data = s.data;
    isNew = s.isNew;
    top = s.top;

    s.len = 0;
    s.data = nullptr;
    s.isNew = true;
    s.top = 0;

    return *this;
}

template<class T>
inline bool TStack<T>::operator==(const TStack& s) const
{
    // Проверка на самосравнение
    if (this == &s) 
    {
        return true;
    }

    // Сравниваем основные параметры
    if (len != s.len || top != s.top) 
    {
        return false;
    }

    // Сравниваем содержимое данных
    for (int i = 0; i < len; i++) {
        if (data[i] == nullptr && s.data[i] == nullptr)
        {
            continue;
        }
        // Один nullptr, а другой нет - не равны
        if (data[i] == nullptr || s.data[i] == nullptr)
        {
            return false;
        }
        if (*(data[i]) != *(s.data[i])) 
        {
            return false;
        }

    }
    return true;
}

template<class T>
inline bool TStack<T>::operator!=(const TStack& s) const
{
    return !(*this == s);
}

template<class T>
inline bool TStack<T>::IsFull() const
{
    return top>=len;
}

template<class T>
inline bool TStack<T>::IsEmpty() const
{
    return top == 0;
}

template<class O>
inline std::ostream& operator<<(std::ostream& o, TStack<O> s)
{
    o << '(';
    for (int i = 0; i < s.len; i++)
    {
        if (s.data[i] != nullptr)
        {
            o << *(s.data[i]);
        }
        else
        {
            o << "null";
        }
        if (i == s.len - 1)
        {
            o << ')';
        }
        else
        {
            o << ' ';
        }
    }
    return o;
}

template<class I>
inline std::istream& operator>>(std::istream& i, TStack<I> t)
{
    return i;
}

template<class T>
class TQueue
{
protected:
    T** data;
    int len;
    bool isNew;
    int head; // индекс первого элемента
    int tail; // индекс следующего за последним элементом
    int count; // количество элементов в очереди
public:
    TQueue();
    TQueue(int len_);
    TQueue(const TQueue& s);
    TQueue(TQueue&& s);
    TQueue(T** data_, int len_);
    ~TQueue();
    int GetLen();
    void Resize(int newsize);
    void SetData(T** data_, int len_);

    T* RemoveFromHead();
    void AddToTail(T elem);

    TQueue& operator=(const TQueue& s);
    TQueue& operator=(TQueue&& s);
    bool operator==(const TQueue& s) const;
    bool operator!=(const TQueue& s) const;
    bool IsFull() const;
    bool IsEmpty() const;

    template <class O>
    friend std::ostream& operator<<(std::ostream& o, TQueue<O> t);
    template <class I>
    friend std::istream& operator>>(std::istream& i, TQueue<I> t);
};

template<class T>
inline TQueue<T>::TQueue()
{
    len = 0;
    data = nullptr;
    isNew = true;
    head = 0;
    tail = 0;
    count = 0;
}

template<class T>
inline TQueue<T>::TQueue(int len_) : TQueue<T>::TQueue()
{
    if (len_ < 0 || len_ > MAX_QUEUE_SIZE)
    {
        throw std::exception();
    }
    else if (len_ > 0)
    {
        len = len_;
        data = new T * [len];
        for (int i = 0; i < len; i++)
        {
            data[i] = nullptr;
        }
    }
}

template<class T>
inline TQueue<T>::TQueue(const TQueue& s) : TQueue<T>::TQueue()
{
    if (s.len > 0)
    {
        len = s.len;
        data = new T * [len];
        for (int i = 0; i < len; i++)
        {
            if (s.data[i] != nullptr)
            {
                data[i] = new T(*(s.data[i]));
            }
            else
            {
                data[i] = nullptr;
            }
        }
    }
    head = s.head;
    tail = s.tail;
    count = s.count;
}

template<class T>
inline TQueue<T>::TQueue(TQueue&& s)
{
    len = s.len;
    data = s.data;
    isNew = s.isNew;
    head = s.head;
    tail = s.tail;
    count = s.count;

    s.len = 0;
    s.data = nullptr;
    s.isNew = true;
    s.head = 0;
    s.tail = 0;
    s.count = 0;
}

template<class T>
inline TQueue<T>::TQueue(T** data_, int len_) : TQueue<T>::TQueue()
{
    if (len_ < 0 || len_ > MAX_QUEUE_SIZE)
    {
        throw std::exception();
    }
    else if (len_ > 0)
    {
        len = len_;
        data = data_;
        isNew = false;

        // Подсчитываем количество элементов и находим head/tail
        count = 0;
        for (int i = 0; i < len; i++)
        {
            if (data[i] != nullptr)
            {
                count++;
                tail = (i + 1) % len;
            }
        }
        if (count > 0)
        {
            // Находим первый не-nullptr элемент
            for (int i = 0; i < len; i++)
            {
                if (data[i] != nullptr)
                {
                    head = i;
                    break;
                }
            }
        }
        else
        {
            head = 0;
            tail = 0;
        }
    }
}

template<class T>
inline TQueue<T>::~TQueue()
{
    if (isNew)
    {
        if (data != nullptr)
        {
            for (int i = 0; i < len; i++)
            {
                delete data[i];
            }
            delete[] data;
        }
    }
    data = nullptr;
    isNew = true;
    len = 0;
    head = 0;
    tail = 0;
    count = 0;
}

template<class T>
inline int TQueue<T>::GetLen()
{
    return len;
}

template<class T>
inline void TQueue<T>::Resize(int newsize)
{
    if (newsize < 0)
    {
        throw std::exception();
    }
    else if (newsize == 0)
    {
        if (isNew)
        {
            if (data != nullptr)
            {
                for (int i = 0; i < len; i++)
                {
                    delete data[i];
                }
                delete[] data;
            }
        }
        data = nullptr;
        isNew = true;
        len = 0;
        head = 0;
        tail = 0;
        count = 0;
    }
    else if (len == newsize)
    {
        return;
    }
    else
    {
        T** newData = new T * [newsize];
        for (int i = 0; i < newsize; i++)
        {
            newData[i] = nullptr;
        }

        // Копируем существующие элементы
        int newCount = 0;
        int newHead = 0;
        int newTail = 0;

        if (count > 0)
        {
            int current = head;
            for (int i = 0; i < std::min(count, newsize); i++)
            {
                newData[i] = new T(*(data[current]));
                newCount++;
                current = (current + 1) % len;
            }
            newTail = newCount;
        }

        // Очищаем старые данные
        if (isNew && data != nullptr)
        {
            for (int i = 0; i < len; i++)
            {
                delete data[i];
            }
            delete[] data;
        }

        data = newData;
        len = newsize;
        head = newHead;
        tail = newTail;
        count = newCount;
        isNew = true;
    }
}

template<class T>
inline void TQueue<T>::SetData(T** data_, int len_)
{
    if (len_ < 0 || len_ > MAX_QUEUE_SIZE)
    {
        throw std::exception();
    }
    else if (len_ == 0)
    {
        if (isNew)
        {
            if (data != nullptr)
            {
                for (int i = 0; i < len; i++)
                {
                    delete data[i];
                }
                delete[] data;
            }
        }
        data = nullptr;
        isNew = true;
        len = 0;
        head = 0;
        tail = 0;
        count = 0;
    }
    else if (len_ > 0)
    {
        if (isNew && data != nullptr)
        {
            for (int i = 0; i < len; i++)
            {
                delete data[i];
            }
            delete[] data;
        }

        data = data_;
        len = len_;
        isNew = false;

        // Подсчитываем элементы и находим head/tail
        count = 0;
        for (int i = 0; i < len; i++)
        {
            if (data[i] != nullptr)
            {
                count++;
            }
        }

        if (count > 0)
        {
            // Находим head (первый не-nullptr)
            for (int i = 0; i < len; i++)
            {
                if (data[i] != nullptr)
                {
                    head = i;
                    break;
                }
            }
            // Находим tail (следующий за последним)
            tail = (head + count) % len;
        }
        else
        {
            head = 0;
            tail = 0;
        }
    }
}

template<class T>
inline T* TQueue<T>::RemoveFromHead()
{
    if (IsEmpty())
    {
        throw std::exception();
    }

    T* result = data[head];
    data[head] = nullptr;
    head = (head + 1) % len; // Двигаем head вперед
    count--;
    return result;
}

template<class T>
inline void TQueue<T>::AddToTail(T elem)
{
    if (IsFull())
    {
        throw std::exception();
    }

    data[tail] = new T(elem);
    tail = (tail + 1) % len; // Двигаем tail вперед
    count++;
}

template<class T>
inline TQueue<T>& TQueue<T>::operator=(const TQueue& s)
{
    if (this == &s) {
        return *this;
    }

    // Очищаем текущие данные
    if (isNew && data != nullptr) {
        for (int i = 0; i < len; i++) {
            delete data[i];
        }
        delete[] data;
    }

    // Копируем данные из s
    len = s.len;
    head = s.head;
    tail = s.tail;
    count = s.count;
    isNew = true;

    if (s.len > 0)
    {
        data = new T * [len];
        for (int i = 0; i < len; i++)
        {
            if (s.data[i] != nullptr)
            {
                data[i] = new T(*(s.data[i]));
            }
            else
            {
                data[i] = nullptr;
            }
        }
    }
    else {
        data = nullptr;
    }

    return *this;
}

template<class T>
inline TQueue<T>& TQueue<T>::operator=(TQueue&& s)
{
    if (this == &s)
    {
        return *this;
    }

    // Очищаем текущие данные
    if (isNew && data != nullptr)
    {
        for (int i = 0; i < len; i++)
        {
            delete data[i];
        }
        delete[] data;
    }

    len = s.len;
    data = s.data;
    isNew = s.isNew;
    head = s.head;
    tail = s.tail;
    count = s.count;

    s.len = 0;
    s.data = nullptr;
    s.isNew = true;
    s.head = 0;
    s.tail = 0;
    s.count = 0;

    return *this;
}

template<class T>
inline bool TQueue<T>::operator==(const TQueue& s) const
{
    if (this == &s)
    {
        return true;
    }

    if (len != s.len || count != s.count)
    {
        return false;
    }

    // Сравниваем элементы в порядке очереди
    int current1 = head;
    int current2 = s.head;
    for (int i = 0; i < count; i++)
    {
        if (*(data[current1]) != *(s.data[current2]))
        {
            return false;
        }
        current1 = (current1 + 1) % len;
        current2 = (current2 + 1) % len;
    }

    return true;
}

template<class T>
inline bool TQueue<T>::operator!=(const TQueue& s) const
{
    return !(*this == s);
}

template<class T>
inline bool TQueue<T>::IsFull() const
{
    return count >= len;
}

template<class T>
inline bool TQueue<T>::IsEmpty() const
{
    return count == 0;
}

// Операторы ввода/вывода можно реализовать аналогично TStack
template<class O>
inline std::ostream& operator<<(std::ostream& o, TQueue<O> q)
{
    o << '(';
    for (int i = 0; i < q.len; i++)
    {
        if (q.data[i] != nullptr)
        {
            o << *(q.data[i]);
        }
        else
        {
            o << "null";
        }
        if (i == q.len - 1)
        {
            o << ')';
        }
        else
        {
            o << ' ';
        }
    }
    return o;
}

template<class I>
inline std::istream& operator>>(std::istream& i, TQueue<I> t)
{
    // Реализация ввода очереди
    return i;
}
#endif
