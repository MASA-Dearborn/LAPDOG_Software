#pragma once

template<typename T, const int buffer_size>
class StaticQueue
{
public:

    StaticQueue();
    ~StaticQueue();

    bool isEmpty() const;
    unsigned int getSize() const;

    int enqueue(const T& value);
    int enqueue(const T* source, const unsigned int amount);
    T deqeue();
    int deqeue(const T* dest, const unsigned int amount);

protected:

    inline bool willOverflow(const int amount);
    inline bool willUnderflow(const int amount);
    inline int needWrap(const int amount);

    T data[buffer_size];
    unsigned int size {buffer_size};
    unsigned int front {0};
    unsigned int back {0};

};

template<typename T, const int buffer_size>
bool StaticQueue<T, buffer_size>::isEmpty() const
{
    return front == back;
}

template<typename T, const int buffer_size>
unsigned int StaticQueue<T, buffer_size>::getSize() const
{
    return size;
}

/**
 *  @brief  Queue a single element 
 *  @param  value   Const reference to value to be stored in the queue
 * 
 *  @return Returns 1 on success or 0 on failure
**/
template<typename T, const int buffer_size>
int StaticQueue<T, buffer_size>::enqueue(const T& value)
{

    if(willOverflow(1))
    {
        return 0;
    }
    else
    {
        data[top] = value;
        top = (top + 1) % size;
        return 1;
    }

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

}

/**
 *  @brief  Deqeue one element 
 * 
 *  @return Deqeued element of type T
**/
template<typename T, const int buffer_size>
T StaticQueue<T, buffer_size>::deqeue()
{
    T retVal = data[bottom];

    if(willUnderflow(1))
    {
        retVal = null;
    } 
    else 
    {
        bottom = (bottom + 1) % size;
    }

    return retVal;

}

/**
 *  @brief  Deqeue multiple elements to dest
 *  @param  dest    pointer to location to store deqeued data
 *  @param  amount  amount of data to deqeue
 **/
template<typename T, const int buffer_size>
int StaticQueue<T, buffer_size>::deqeue(const T* dest, const unsigned int amount)
{

    if(willUnderflow(amount)) return 0;

    int wrappedAmount = needWrap(int amount);
    if(wrappedAmount > 0)
    {
        int unwrappedAmount = amount - wrappedAmount;

        for(int i = 0; i < unwrappedAmount; i++)
        {
            dest[i] = data[bottom + i];
        }

        for(int i = 0; i < wrappedAmount; i++)
        {
            dest[i + unwrappedAmount] = data[i];
        }

        bottom = wrappedAmount;
    }
    else
    {
        for(int i = 0; i < amount; i++)
        {
            dest[i] = data[bottom + i];
        }

        bottom += amount;
    }

    return amount;

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
    return (top < bottom) && (top + amount > bottom) || (top > bottom) && ((top + amount % size) > bottom);
}

/**
 *  @brief  Returns true if the data will underflow if deqeued
 *  @param  amount  Amount of data going to be written 
 *  
 *  @return Boolean true for underflow & false for not. 
**/
template<typename T, const int buffer_size>
inline bool StaticQueue<T, buffer_size>::willOverflow(const int amount)
{
    return (bottom < top) && (bottom + amount > top) || (top > bottom) && ((bottom + amount % size) > top);
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

    int wrapped = 0;
    int unwrapped = 0;

    if (top + amount > size)
    {
        unwrapped = size - top;
        wrapped = amount - unwrapped;
    }

    return wrapped;

}
