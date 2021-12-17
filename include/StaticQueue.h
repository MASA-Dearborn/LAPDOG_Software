#pragma once

template<typename T, const int buffer_size>
class StaticQueue
{
public:

    StaticQueue();
    ~StaticQueue();

    bool isEmpty() const;
    unsigned int getSize() const;

    void enqueue(const T& value);
    void enqueue(const T* source, unsigned int amount);
    T deqeue();
    void deqeue(const T* dest, unsigned int amount);

protected:

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

template<typename T, const int buffer_size>
void StaticQueue<T, buffer_size>::enqueue(const T& value)
{

}

template<typename T, const int buffer_size>
void StaticQueue<T, buffer_size>::enqueue(const T* source, unsigned int amount)
{

}

template<typename T, const int buffer_size>
T StaticQueue<T, buffer_size>::deqeue()
{

}

template<typename T, const int buffer_size>
void StaticQueue<T, buffer_size>::deqeue(const T* dest, unsigned int amount)
{

}
