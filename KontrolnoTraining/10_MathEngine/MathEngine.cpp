#include "MathEngine.h"

#include <algorithm>
#include <iostream>
#include <ostream>

void MathEngine::freeMemory()
{
    delete[] polys;
}

void MathEngine::copyFrom(const MathEngine& other)
{
    this->capacity = other.capacity;
    this->count = other.count;
    
    this->polys = new Polynomial[this->capacity];
    
    for (size_t i = 0; i < this->count; i++)
    {
        this->polys[i] = other.polys[i];
    }
}

void MathEngine::moveFrom(MathEngine&& other)
{
    this->polys = other.polys;
    this->count = other.count;
    this->capacity = other.capacity;
    
    other.polys = nullptr;
    other.count = 0;
    other.capacity = 0;
}

void MathEngine::resize(size_t newCapacity)
{
    if (newCapacity > capacity)
    {
        Polynomial* temp = new Polynomial[newCapacity];
        
        for (size_t i = 0; i < count; i++)
        {
            temp[i] = this->polys[i];
        }
        
        delete[] polys;
        polys = temp;
        capacity = newCapacity;
    }
}

MathEngine::~MathEngine()
{
    freeMemory();
}

MathEngine::MathEngine(const MathEngine& other)
{
    copyFrom(other);
}

MathEngine& MathEngine::operator=(const MathEngine& other)
{
    if (this != &other)
    {
        freeMemory();
        copyFrom(other);
    }
    
    return *this;
}

MathEngine::MathEngine(MathEngine&& other) noexcept
{
    moveFrom(std::move(other));
}

MathEngine& MathEngine::operator=(MathEngine&& other) noexcept
{
    if (this != &other)
    {
        freeMemory();
        moveFrom(std::move(other));
    }
    
    return *this;
}

MathEngine::MathEngine() : count(0), capacity(2)
{
    polys = new Polynomial[capacity];
}

void MathEngine::addPolynomial(const Polynomial& polynomial)
{
    if (count == capacity)
    {
        resize(capacity * 2);
    }
    
    polys[count] = polynomial;
    count++;
}

Polynomial MathEngine::sumAll() const
{
    Polynomial result = Polynomial();

    for (size_t i = 0; i < count; ++i)
    {
        result = result + polys[i];
    }
    
    return result;
}

void MathEngine::evaluateAll(int x) const
{
    long long result = 0;
    
    for (size_t i = 0; i < count; i++)
    {
        result = polys[i](x);
        
        std::cout << "Polynomial " << i << ": " << result << std::endl;
    }
}