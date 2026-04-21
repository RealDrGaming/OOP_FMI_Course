#include "Dictionary.h"

#include <algorithm>
#include <iostream>
#include <ostream>

void Dictionary::freeMemory()
{
    for (size_t i = 0; i < size; ++i)
    {
        delete[] entries[i].word;
        delete[] entries[i].translation;
    }

    delete[] entries;
}

void Dictionary::copyFrom(const Dictionary& other)
{
    this-> size = other.size;
    this->capacity = other.capacity;
    
    this->entries = new WordPair[this->capacity];
    
    for (size_t i = 0; i < this->size; ++i)
    {
        this->entries[i].word = new char[strlen(other.entries[i].word) + 1];
        strcpy(this->entries[i].word, other.entries[i].word);
        
        this->entries[i].translation = new char[strlen(other.entries[i].translation) + 1];
        strcpy(this->entries[i].translation, other.entries[i].translation);
    }
}

void Dictionary::moveFrom(Dictionary&& other)
{
    this->entries = other.entries;
    this->capacity = other.capacity;
    this->size = other.size;
    
    other.size = 0;
    other.capacity = 0;
    other.entries = nullptr;
}

void Dictionary::resize(size_t newCapacity)
{
    if (newCapacity > capacity)
    {
        WordPair* temp = new WordPair[newCapacity];
        
        for (size_t i = 0; i < size; ++i)
        {
            temp[i].word = entries[i].word;
            temp[i].translation = entries[i].translation;
        }

        for (size_t i = size; i < newCapacity; ++i)
        {
            temp[i].word = nullptr;
            temp[i].translation = nullptr;
        }
        
        delete[] entries;
        entries = temp;
        capacity = newCapacity;
    }
}

Dictionary::~Dictionary()
{
    freeMemory();
}

Dictionary::Dictionary(const Dictionary& other)
{
    copyFrom(other);
}

Dictionary& Dictionary::operator=(const Dictionary& other)
{
    if (this != &other)
    {
        freeMemory();
        copyFrom(other);
    }
    return *this;
}

Dictionary::Dictionary(Dictionary&& other) noexcept
{
    moveFrom(std::move(other));
}

Dictionary& Dictionary::operator=(Dictionary&& other) noexcept
{
    if (this != &other)
    {
        freeMemory();
        moveFrom(std::move(other));
    }
    return *this;
}

Dictionary::Dictionary() : size(0), capacity(2)
{
    this->entries = new WordPair[this->capacity];
    
    for (size_t i = 0; i < this->capacity; ++i)
    {
        this->entries[i].word = nullptr;
        this->entries[i].translation = nullptr;
    }
}

void Dictionary::add(const char* word, const char* translation)
{
    for (size_t i = 0; i < size; ++i)
    {
        if (strcmp(entries[i].word, word) == 0)
        {
            delete[] entries[i].translation;
            
            entries[i].translation = new char[strlen(translation) + 1];
            strcpy(entries[i].translation, translation);
            return;
        }
    }
    
    if (this->size == this->capacity)
    {
        resize(this->capacity * 2);
    }
    
    entries[this->size].word = new char[strlen(word) + 1];
    strcpy(entries[this->size].word, word);
    
    entries[this->size].translation = new char[strlen(translation) + 1];
    strcpy(entries[this->size].translation, translation);
    
    this->size++;
}

const char* Dictionary::operator[](const char* word) const
{
    for (size_t i = 0; i < size; ++i)
    {
        if (strcmp(entries[i].word, word) == 0) return entries[i].translation;
    }
    return nullptr;
}

Dictionary Dictionary::operator+(const Dictionary& other) const
{
    Dictionary temp(*this);

    for (size_t i = 0; i < other.size; ++i)
    {
        temp.add(other.entries[i].word, other.entries[i].translation);
    }
    
    return temp;
}

void Dictionary::print() const
{
    for (size_t i = 0; i < this->size; ++i)
    {
        std::cout << entries[i].word << " - " << entries[i].translation << std::endl;
    }
}