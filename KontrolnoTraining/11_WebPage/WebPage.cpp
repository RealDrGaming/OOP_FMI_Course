#include "WebPage.h"

#include <algorithm>
#include <iostream>
#include <ostream>

void WebPage::freeMemory()
{
    delete[] this->url;
    
    for (size_t i = 0; i < count; ++i)
    {
        delete[] this->links[i];
    }
    
    delete[] this->links;
}

void WebPage::copyFrom(const WebPage& other)
{
    this->count = other.count;
    this->capacity = other.capacity;
    
    if (other.url != nullptr)
    {
        this->url = new char[strlen(other.url) + 1];
        strcpy(this->url, other.url);
    } 
    else 
    {
        this->url = nullptr;
    }
    
    this->links = new char*[other.capacity];
    for (size_t i = 0; i < other.count; ++i)
    {
        this->links[i] = new char[strlen(other.links[i]) + 1];
        strcpy(this->links[i], other.links[i]);
    }

    for (size_t i = other.count; i < other.capacity; ++i)
    {
        links[i] = nullptr;
    }
}

void WebPage::moveFrom(WebPage&& other)
{
    this->count = other.count;
    this->capacity = other.capacity;
    this->url = other.url;
    this->links = other.links;
    
    other.count = 0;
    other.capacity = 0;
    other.url = nullptr;
    other.links = nullptr;
}

void WebPage::resize(size_t newCapacity)
{
    if (newCapacity > capacity)
    {
        char** temp = new char*[newCapacity];
        for (size_t i = 0; i < this->count; ++i)
        {
            temp[i] = links[i];
        }

        for (size_t i = this->count; i < newCapacity; ++i)
        {
            temp[i] = nullptr;
        }
        
        delete[] this->links;
        this->links = temp;
        this->capacity = newCapacity;
    }
}

WebPage::~WebPage()
{
    freeMemory();
}

WebPage::WebPage(const WebPage& other)
{
    copyFrom(other);
}

WebPage& WebPage::operator=(const WebPage& other)
{
    if (this != &other)
    {
        freeMemory();
        copyFrom(other);
    }
    return *this;
}

WebPage::WebPage(WebPage&& other) noexcept
{
    moveFrom(std::move(other));
}

WebPage& WebPage::operator=(WebPage&& other) noexcept
{
    if (this != &other)
    {
        freeMemory();
        moveFrom(std::move(other));
    }
    return *this;
}

WebPage::WebPage() : count(0), capacity(2)
{
    this-> url = nullptr;
    links = new char*[capacity];

    for (size_t i = 0; i < capacity; ++i)
    {
        links[i] = nullptr;
    }
}

WebPage::WebPage(const char* pageUrl) : count(0), capacity(2)
{
    this-> url = new char[strlen(pageUrl) + 1];
    strcpy(this-> url, pageUrl);
    
    links = new char*[capacity];

    for (size_t i = 0; i < capacity; ++i)
    {
        links[i] = nullptr;
    }
}

WebPage& WebPage::operator+=(const char* newLink)
{
    if (count == capacity)
    {
        resize(capacity * 2);
    }
    
    this->links[count] = new char[strlen(newLink) + 1];
    strcpy(this->links[count], newLink);
    
    count++;
    
    return *this;
}

bool WebPage::operator==(const WebPage& other) const
{
    if (this->url == nullptr && other.url != nullptr) return false;
    if (this->url != nullptr && other.url == nullptr) return false;
    if (this->url != nullptr && other.url != nullptr)
    {
        if (strcmp(this->url, other.url) != 0) return false;
    }
    
    for (size_t i = 0; i < count; ++i)
    {
        if (strcmp(this->links[i], other.links[i]) != 0) return false;
    }
    
    return true;
}

const char* WebPage::operator[](size_t index) const
{
    if (index >= count) return nullptr;
    
    return links[index];
}

void WebPage::print() const
{
    std::cout << this->url << std::endl;
    std::cout << "Links:" << std::endl;

    for (size_t i = 0; i < count; ++i)
    {
        std::cout << "   - " << links[i] << std::endl;
    }
}