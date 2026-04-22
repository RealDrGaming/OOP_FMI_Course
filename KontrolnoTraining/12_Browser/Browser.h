#pragma once

#include "../11_WebPage/WebPage.h"

class Browser
{
private:
    WebPage* tabs;
    size_t count;
    size_t capacity;
    
    void freeMemory();
    void copyFrom(const Browser& other);
    void moveFrom(Browser&& other);
    
    void resize(size_t newCapacity);
    
public:
    ~Browser();
    Browser(const Browser& other);
    Browser& operator=(const Browser& other);
    Browser(Browser&& other) noexcept;
    Browser& operator=(Browser&& other) noexcept;
    
    Browser();
    void openTab(const WebPage& page);
    void closeTab(size_t index);
    WebPage& operator[](size_t index);
    void printAll() const;
};
