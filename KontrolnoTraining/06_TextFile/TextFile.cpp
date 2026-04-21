#include "TextFile.h"

#include <iostream>

void TextFile::freeMemory()
{
    for (size_t i = 0; i < count; ++i)
    {
        delete[] lines[i];
    }
    
    delete[] lines;
}

void TextFile::copyFrom(const TextFile& other)
{
    this->count = other.count;
    this->capacity = other.capacity;
    
    lines = new char*[capacity];
    
    for (size_t i = 0; i < count; ++i)
    {
        lines[i] = new char[strlen(other.lines[i]) + 1];
        strcpy(lines[i], other.lines[i]);
    }

    for (size_t i = count; i < capacity; ++i)
    {
        lines[i] = nullptr;
    }
}

void TextFile::moveFrom(TextFile&& other)
{
    lines = other.lines;
    capacity = other.capacity;
    count = other.count;
    
    other.lines = nullptr;
    other.capacity = 0;
    other.count = 0;
}

void TextFile::resize(size_t newCapacity)
{
    if (newCapacity > capacity)
    {
        char** temp = new char*[newCapacity];
        
        for (size_t i = 0; i < count; ++i)
        {
            temp[i] = lines[i];
        }

        for (size_t i = count; i < newCapacity; ++i)
        {
            temp[i] = nullptr;
        }
        
        delete[] lines;
        
        capacity = newCapacity;
        lines = temp;
    }
}

TextFile::~TextFile()
{
    freeMemory();
}

TextFile::TextFile(const TextFile& other)
{
    copyFrom(other);
}

TextFile& TextFile::operator=(const TextFile& other)
{
    if (this != &other)
    {
        freeMemory();
        copyFrom(other);
    }
    return *this;
}

TextFile::TextFile(TextFile&& other) noexcept
{
    moveFrom(std::move(other));
}

TextFile& TextFile::operator=(TextFile&& other) noexcept
{
    if (this != &other)
    {
        freeMemory();
        moveFrom(std::move(other));
    }
    return *this;
}

TextFile::TextFile() : count(0), capacity(2)
{
    lines = new char*[capacity];
    for (size_t i = 0; i < capacity; ++i)
    {
        lines[i] = nullptr;
    }
}

void TextFile::appendLine(const char* line)
{
    if (count == capacity)
    {
        resize(capacity * 2);
    }
    
    lines[count] = new char[strlen(line) + 1];
    strcpy(lines[count], line);
    count++;
}

void TextFile::print() const
{
    for (size_t i = 0; i < count; ++i)
    {
        std::cout << i << ". " << lines[i] << std::endl;
    }
}

TextFile& TextFile::operator+=(const char* text)
{
    appendLine(text);
    
    return *this;
}

TextFile TextFile::operator+(const TextFile& other) const
{
    TextFile temp(*this);

    for (size_t i = 0; i < other.count; ++i)
    {
        temp.appendLine(other.lines[i]);
    }
    
    return temp;
}