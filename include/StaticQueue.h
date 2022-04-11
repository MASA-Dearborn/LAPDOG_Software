#pragma once
#include <cstring>
// Does not work when dequeuing SIZE from the queue. If buffer is 4 big and we dequeue 4, does not work.

template<typename T, const int buffer_size>
class StaticQueue
{
public:

    StaticQueue() {}
    ~StaticQueue() {}

    bool isEmpty() const;
    unsigned int getBufferSize() const;
    unsigned int getDataSize() const;

    int enqueue(const T* source, const unsigned int amount);
    int dequeue(T* dest, const unsigned int amount);
    const T* peek();

protected:

    inline bool willOverflow(const int amount);
    inline bool willUnderflow(const int amount);
    inline int needUnwrap(const int amount);
    inline int needWrap(const int amount);
    inline int getPtrOffset(const T* ptr) const;

    T data[buffer_size];
    T* top {nullptr};               // next free space ptr
    T* bottom {nullptr};            // first occupied space ptr
    unsigned int size {buffer_size};

};

template<typename T, const int buffer_size>
int StaticQueue<T, buffer_size>::getPtrOffset(const T* ptr) const
{
    return (ptr - data); 
}

template<typename T, const int buffer_size>
bool StaticQueue<T, buffer_size>::isEmpty() const
{
    if (this == nullptr)
        return 0;

    return (top == nullptr) || (bottom == nullptr) || (top == bottom);
}

template<typename T, const int buffer_size>
unsigned int StaticQueue<T, buffer_size>::getBufferSize() const
{
    if (this == nullptr)
        return 0;

    return size;
}

template<typename T, const int buffer_size>
unsigned int StaticQueue<T, buffer_size>::getDataSize() const
{
    if (this == nullptr)
        return 0;

    if (top > bottom)
        return top - bottom;
    else if (top < bottom)
        return (size - getPtrOffset(bottom)) + getPtrOffset(top);
    else
        return 0;
}

/**
 *  @brief  Queues multiple elements 
 *  @param  source  Constant pointer to location to read data to queue
 *  @param  amount  Amount of data to queue from source
 * 
 *  @return Returns the amount of data stored otherwise 0
**/
template<typename T, const int buffer_size>
int StaticQueue<T, buffer_size>::enqueue(const T* source, const unsigned int amount)
{
    int wrappedAmount;
    int unwrappedAmount;
    if (willOverflow(amount)) 
        return 0;

    if (bottom == nullptr || top == nullptr)
    {
        bottom = data;
        top = data;
    }

    wrappedAmount = needWrap(amount);
    if(wrappedAmount > 0)
    {
        unwrappedAmount = amount - wrappedAmount;
        memcpy(top, source, unwrappedAmount);
        memcpy(data, source + unwrappedAmount, wrappedAmount);
        top = data + unwrappedAmount;
    }
    else
    {
        memcpy(top, source, amount);
        top += amount;
        if (top == data + size)
            top = data;
    }

    return amount;
}

/**
 *  @brief  Dequeue multiple elements to dest
 *  @param  dest    pointer to location to store deqeued data
 *  @param  amount  amount of data to deqeue
 **/
template<typename T, const int buffer_size>
int StaticQueue<T, buffer_size>::dequeue(T* dest, const unsigned int amount)
{
    int wrappedAmount;
    int unwrappedAmount;

    if(willUnderflow(amount)) 
        return 0;

    wrappedAmount = needUnwrap(amount);
    if(wrappedAmount > 0)
    {
        unwrappedAmount = amount - wrappedAmount;
        memcpy(dest, bottom, unwrappedAmount);
        memcpy(dest + unwrappedAmount, data, wrappedAmount);
        bottom = data + wrappedAmount;
    }
    else
    {
        memcpy(dest, bottom, amount);
        bottom += amount;
        if (bottom == data + size)
            bottom = data;
    }

    return amount;
}

template<typename T, const int buffer_size>
const T* StaticQueue<T, buffer_size>::peek()
{
    if (this != NULL && bottom != nullptr && top != nullptr)
        return bottom;
    else
        return NULL;
}

/**
 *  @brief  Returns true if the data will overflow if written
 *  @param  amount  Amount of data going to be written 
 *  
 *  @return Boolean true for overflow & false for not. 
**/
template<typename T, const int buffer_size>
inline bool StaticQueue<T, buffer_size>::willOverflow(const int amount)
{
    if (this == nullptr)
        return 0;
        
    return ((top < bottom) && ((top + amount) > bottom)) || ((top > bottom) && ((getPtrOffset(top + amount) % size) > getPtrOffset(bottom))) || (top == bottom) && (amount > size);
}

/**
 *  @brief  Returns true if the data will underflow if deqeued
 *  @param  amount  Amount of data going to be written 
 *  
 *  @return Boolean true for underflow & false for not. 
**/
template<typename T, const int buffer_size>
inline bool StaticQueue<T, buffer_size>::willUnderflow(const int amount)
{
    if (this == nullptr)
        return 0;

    return (top > bottom) && (bottom + amount > top) || (top < bottom) && (((getPtrOffset(bottom) + amount) % size) > getPtrOffset(top)) || (top == bottom);
}

/**
 *  @brief  Returns amount of data that will need to be wrapped
 *  @param  amount  Amount of data going to be written 
 *  
 *  @return Integer result of data needed to be wrapped, 0 for no wrap. 
**/
template<typename T, const int buffer_size>
inline int StaticQueue<T, buffer_size>::needWrap(const int amount)
{
    if (this == nullptr)
        return 0;

    int wrapped = 0;
    int unwrapped = 0;

    if (getPtrOffset(top + amount) > size)
    {
        unwrapped = size - getPtrOffset(top);
        wrapped = amount - unwrapped;
    }

    return wrapped;

}

template<typename T, const int buffer_size>
inline int StaticQueue<T, buffer_size>::needUnwrap(const int amount)
{
    if (this == nullptr)
        return 0;

    int wrapped = 0;
    int unwrapped = 0;

    if (getPtrOffset(bottom) + amount > size)
    {
        unwrapped = size - getPtrOffset(bottom);
        wrapped = amount - unwrapped;
    }

    return wrapped;
}
