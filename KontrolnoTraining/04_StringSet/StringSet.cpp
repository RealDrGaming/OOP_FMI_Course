#include "StringSet.h"

#include <iostream>

void StringSet::freeMemory()
{
    if (this->words != nullptr)
    {
        for (size_t i = 0; i < count; i++)
        {
            delete[] words[i];
        }
        delete[] words;
    }
}

void StringSet::copyFrom(const StringSet& other)
{
    this->count = other.count;
    this->capacity = other.capacity;
    
    this->words = new char*[other.capacity];
    
    for (size_t i = 0; i < other.count; i++)
    {
        words[i] = new char[strlen(other.words[i]) + 1];
        strcpy(words[i], other.words[i]);
    }

    for (size_t i = other.count; i < capacity; ++i)
    {
        this->words[i] = nullptr;
    }
}

void StringSet::moveFrom(StringSet&& other)
{
    this->words = other.words;
    this->count = other.count;
    this->capacity = other.capacity;
    
    other.words = nullptr;
    other.count = 0;
    other.capacity = 0;
}

void StringSet::resize(size_t newCapacity)
{
    if (newCapacity > capacity)
    {
        capacity = newCapacity;
        
        char** temp = new char*[newCapacity];
        
        for (size_t i = 0; i < count; i++)
        {
            temp[i] = words[i];
        }

        for (size_t i = count; i < newCapacity; ++i)
        {
            temp[i] = nullptr;
        }
        
        delete[] words;
        
        words = temp;
        capacity = newCapacity;
    }
}

StringSet::~StringSet()
{
    freeMemory();
}

StringSet::StringSet(const StringSet& other)
{
    copyFrom(other);
}

StringSet& StringSet::operator=(const StringSet& other)
{
    if (this != &other)
    {
        freeMemory();
        copyFrom(other);
    }
    return *this;
}

StringSet::StringSet(StringSet&& other) noexcept
{
    moveFrom(std::move(other));
}

StringSet& StringSet::operator=(StringSet&& other) noexcept
{
    if (this != &other)
    {
        freeMemory();
        moveFrom(std::move(other));
    }
    return *this;
}

StringSet::StringSet() : count(0), capacity(2)
{
    this->words = new char*[this->capacity];
    
    for (size_t i = 0; i < capacity; ++i)
    {
        this->words[i] = nullptr;
    }
}

bool StringSet::contains(const char* word) const
{
    for (size_t i = 0; i < count; i++)
    {
        if (strcmp(words[i], word) == 0) return true;
    }
    
    return false;
}

void StringSet::add(const char* word)
{
    if (this->contains(word)) return;
    
    if (this->capacity == this-> count)
    {
        resize(this->capacity * 2);
    }
    
    words[this->count] = new char[strlen(word) + 1];
    strcpy(words[this->count], word);
    
    count++;
}

StringSet& StringSet::operator+=(const char* word)
{
    add(word);
    
    return *this;
}

StringSet StringSet::operator+(const StringSet& other) const
{
    StringSet result = *this;

    for (size_t i = 0; i < other.count; ++i)
    {
        result.add(other.words[i]);
    }
    
    return result;
}

void StringSet::print() const
{
    for (size_t i = 0; i < count; i++)
    {
        std::cout << words[i] << std::endl;
    }
}