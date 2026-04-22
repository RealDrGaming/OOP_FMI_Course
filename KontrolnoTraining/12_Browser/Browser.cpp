#include "Browser.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <ostream>

void Browser::freeMemory()
{
    delete[] tabs;
}

void Browser::copyFrom(const Browser& other)
{
    this->capacity = other.capacity;
    this->count = other.count;
    
    this->tabs = new WebPage[capacity];
    
    for (size_t i = 0; i < count; ++i)
    {
        this->tabs[i] = other.tabs[i];
    }
}

void Browser::moveFrom(Browser&& other)
{
    this->tabs = other.tabs;
    this->count = other.count;
    this->capacity = other.capacity;
    
    other.tabs = nullptr;
    other.count = 0;
    other.capacity = 0;
}

void Browser::resize(size_t newCapacity)
{
    if (newCapacity > capacity)
    {
        WebPage* temp = new WebPage[newCapacity];
        
        for (size_t i = 0; i < count; ++i)
        {
            temp[i] = tabs[i];
        }
        
        delete[] this->tabs;
        this->tabs = temp;
        this->capacity = newCapacity;
    }
}

Browser::~Browser()
{
    freeMemory();
}

Browser::Browser(const Browser& other)
{
    copyFrom(other);
}

Browser& Browser::operator=(const Browser& other)
{
    if (this != &other)
    {
        freeMemory();
        copyFrom(other);
    }
    return *this;
}

Browser::Browser(Browser&& other) noexcept
{
    moveFrom(std::move(other));
}

Browser& Browser::operator=(Browser&& other) noexcept
{
    if (this != &other)
    {
        freeMemory();
        moveFrom(std::move(other));
    }
    return *this;
}

Browser::Browser() : count(0), capacity(2)
{
    this->tabs = new WebPage[capacity];
}

void Browser::openTab(const WebPage& page)
{
    if (count == capacity)
    {
        resize(capacity * 2);    
    }
    
    this->tabs[count] = page;
    count++;
}

void Browser::closeTab(size_t index)
{
    if (index >= count) return;
    
    for (size_t i = index; i < count - 1; ++i)
    {
        tabs[i] = tabs[i + 1];
    }
    
    count--;
}

WebPage& Browser::operator[](size_t index)
{
    if (index >= count) return tabs[0];
    
    return tabs[index];
}

void Browser::printAll() const
{
    for (size_t i = 0; i < count; ++i)
    {
        std::cout << "--- Tab " << i << " ---\n";
        tabs[i].print();
        std::cout << std::endl;
    }
}