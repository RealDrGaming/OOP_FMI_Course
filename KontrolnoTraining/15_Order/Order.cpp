#include "Order.h"

#include <algorithm>
#include <cstring>

void Order::freeMemory()
{
    delete[] prices;
    delete[] client;
}

void Order::copyFrom(const Order& other)
{
    this->count = other.count;
    this->capacity = other.capacity;
    
    this->client = new char[strlen(other.client) + 1];
    strcpy(this->client, other.client);
    
    this->prices = new double[other.capacity];

    for (size_t i = 0; i < other.count; ++i)
    {
        this->prices[i] = other.prices[i];
    }

    for (size_t i = other.count; i < other.capacity; ++i)
    {
        this->prices[i] = 0;
    }
}

void Order::moveFrom(Order&& other)
{
    this->prices = other.prices;
    this->client = other.client;
    this->count = other.count;
    this->capacity = other.capacity;
    
    other.prices = nullptr;
    other.client = nullptr;
    other.count = 0;
    other.capacity = 0;
}

void Order::resize(size_t newCapacity)
{
    if (newCapacity > this->capacity)
    {
        this->capacity = newCapacity;

        double* temp = new double[newCapacity];
        
        for (size_t i = 0; i < this->count; ++i)
        {
            temp[i] = this->prices[i];
        }

        for (size_t i = this->count; i < newCapacity; ++i)
        {
            temp[i] = 0;
        }
        
        delete[] this->prices;
        this->prices = temp;
        this->capacity = newCapacity;
    }
}

Order::~Order()
{
    freeMemory();
}

Order::Order(const Order& other)
{
    copyFrom(other);
}

Order& Order::operator=(const Order& other)
{
    if (this != &other)
    {
        freeMemory();
        copyFrom(other);
    }
    return *this;
}

Order::Order(Order&& other) noexcept
{
    moveFrom(std::move(other));
}

Order& Order::operator=(Order&& other) noexcept
{
    if (this != &other)
    {
        freeMemory();
        moveFrom(std::move(other));
    }
    return *this;
}

Order::Order() : count(0), capacity(2)
{
    this->client = nullptr;
    this->prices = new double[capacity];

    for (size_t i = 0; i < capacity; ++i)
    {
        this->prices[i] = 0;
    }
}

Order::Order(const char* clientName)
{
    this->client = new char[strlen(clientName) + 1];
    strcpy(this->client, clientName);
    
    this->prices = new double[capacity];

    for (size_t i = 0; i < capacity; ++i)
    {
        this->prices[i] = 0;
    }
}

void Order::addPrice(double priceToAdd)
{
    
}

const Order& Order::operator[](size_t index)
{
    
}

bool Order::operator>(const Order& other)
{
    
}

Order Order::operator+(const Order& other)
{
    
}

void Order::print() const
{
    
}