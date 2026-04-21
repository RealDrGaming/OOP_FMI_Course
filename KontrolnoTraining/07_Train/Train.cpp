#include "Train.h"

#include <algorithm>
#include <iostream>
#include <ostream>

void Train::freeMemory()
{
    Wagon* current = head;
        
    while (current != nullptr)
    {
        Wagon* nextWagon = current->next;
        
        delete[] current->cargo;
        delete current;
        
        current = nextWagon;
    }
    
    head = nullptr;
    tail = nullptr;
}

void Train::copyFrom(const Train& other)
{
    this->head = nullptr;
    this->tail = nullptr;
    
    Wagon* current = other.head;
    
    while (current != nullptr)
    {
        *this += current->cargo; 
        
        current = current->next;
    }
}

void Train::moveFrom(Train&& other)
{
    this->head = other.head;
    this->tail = other.tail;
    
    other.head = nullptr;
    other.tail = nullptr;
}

Train::~Train()
{
    freeMemory();
}

Train::Train(const Train& other)
{
    copyFrom(other);
}

Train& Train::operator=(const Train& other)
{
    if (this != &other)
    {
        freeMemory();
        copyFrom(other);
    }
    
    return *this;
}

Train::Train(Train&& other) noexcept
{
    moveFrom(std::move(other));
}

Train& Train::operator=(Train&& other) noexcept
{
    if (this != &other)
    {
        freeMemory();
        moveFrom(std::move(other));
    }
    
    return *this;
}

Train::Train()
{
    head = nullptr;
    tail = nullptr;
}

void Train::print() const
{
    Wagon* currWagon = head;
    
    while (currWagon != nullptr)
    {
        std::cout << currWagon->cargo << std::endl;
        currWagon = currWagon->next;
    }
}

Train& Train::operator+=(const char* newCargo)
{
    Wagon* newWagon = new Wagon();
    newWagon->cargo = new char[strlen(newCargo) + 1];
    strcpy(newWagon->cargo, newCargo);
    newWagon->next = nullptr;

    if (head == nullptr)
    {
        head = newWagon;
        tail = newWagon;
    }
    else
    {
        tail->next = newWagon;
        tail = newWagon;
    }
    
    return *this;
}

Train Train::operator+(const Train& other) const
{
    Train temp(*this);

    Wagon* current = other.head;
    while (current != nullptr)
    {
        temp += current->cargo;
        current = current->next;
    }
    
    return temp;
}