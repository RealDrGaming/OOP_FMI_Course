#include "Gallery.h"

#include <algorithm>
#include <iostream>
#include <ostream>

void Gallery::freeMemory()
{
    delete[] galleryName;

    for (size_t i = 0; i < count; ++i)
    {
        delete[] paintings[i].paintingName;
    }
    
    delete[] paintings;
}

void Gallery::copyFrom(const Gallery& other)
{
    count = other.count;
    capacity = other.capacity;
    
    if (other.galleryName != nullptr)
    {
        this->galleryName = new char[std::strlen(other.galleryName) + 1];
        std::strcpy(this->galleryName, other.galleryName);
    } 
    else this->galleryName = nullptr;
    
    this->paintings = new Painting[other.capacity];
    
    for (size_t i = 0; i < other.count; ++i)
    {
        if (other.paintings[i].paintingName != nullptr)
        {
            this->paintings[i].paintingName = new char[std::strlen(other.paintings[i].paintingName) + 1];
            std::strcpy(this->paintings[i].paintingName, other.paintings[i].paintingName);
        } 
        else this->paintings[i].paintingName = nullptr;
        
        this->paintings[i].price = other.paintings[i].price;
    }

    for (size_t i = count; i < other.capacity; ++i)
    {
        this->paintings[i].paintingName = nullptr;
    }
}

void Gallery::moveFrom(Gallery&& other)
{
    this->galleryName = other.galleryName;
    this->paintings = other.paintings;
    this->count = other.count;
    this->capacity = other.capacity;
    
    other.galleryName = nullptr;
    other.paintings = nullptr;
    other.count = 0;
    other.capacity = 0;
}

void Gallery::resize(size_t newCapacity)
{
    if (newCapacity > capacity)
    {
        Painting* temp = new Painting[newCapacity];
        
        for (size_t i = 0; i < count; ++i)
        {
            temp[i].paintingName = paintings[i].paintingName;
            temp[i].price = paintings[i].price;
        }

        for (size_t i = count; i < newCapacity; ++i)
        {
            temp[i].paintingName = nullptr;
        }
        
        capacity = newCapacity;
        delete[] this->paintings;
        this->paintings = temp;
    }
}

Gallery::~Gallery()
{
    freeMemory();
}

Gallery::Gallery(const Gallery& other)
{
    copyFrom(other);
}

Gallery& Gallery::operator=(const Gallery& other)
{
    if (this != &other)
    {
        freeMemory();
        copyFrom(other);
    }
    return *this;
}

Gallery::Gallery(Gallery&& other) noexcept
{
    moveFrom(std::move(other));
}

Gallery& Gallery::operator=(Gallery&& other) noexcept
{
    if (this != &other)
    {
        freeMemory();
        moveFrom(std::move(other));
    }
    return *this;
}

Gallery::Gallery() : count(0), capacity(2)
{
    galleryName = nullptr;
    paintings = new Painting[capacity];

    for (size_t i = 0; i < capacity; ++i)
    {
        paintings[i].paintingName = nullptr;
    }
}

Gallery::Gallery(const char* name) : count(0), capacity(2)
{
    if (name != nullptr)
    {
        galleryName = new char[std::strlen(name) + 1];
        std::strcpy(galleryName, name);
    }
    else galleryName = nullptr;
    
    paintings = new Painting[capacity];

    for (size_t i = 0; i < capacity; ++i)
    {
        paintings[i].paintingName = nullptr;
    }
}

void Gallery::addPainting(const char* paintingName, double paintingPrice)
{
    if (count == capacity)
    {
        resize(capacity * 2);
    }
    
    if (paintingName != nullptr)
    {
        paintings[count].paintingName = new char[std::strlen(paintingName) + 1];
        std::strcpy(paintings[count].paintingName, paintingName);
    }
    else paintings[count].paintingName = nullptr;
    
    paintings[count].price = paintingPrice;
    
    count++;
}

double Gallery::operator[](size_t index) const
{
    if (index >= count) return -1;
    
    return paintings[index].price;
}

bool Gallery::operator==(const Gallery& other) const
{
    if (this->galleryName == nullptr && other.galleryName == nullptr)
    {
        if (this->count != other.count) return false;
    
        return true;
    }
    else if (this->galleryName == nullptr || other.galleryName == nullptr) return false;
    else if (std::strcmp(this->galleryName, other.galleryName) != 0) return false;
    
    if (this->count != other.count) return false;
    
    return true;
}

void Gallery::sellPainting(const char* paintingName)
{
    for (size_t i = 0; i < count; ++i)
    {
        if (std::strcmp(paintings[i].paintingName, paintingName) == 0)
        {
            delete[] paintings[i].paintingName;
            
            for (size_t j = i; j < count - 1; ++j)
            {
                paintings[j] = paintings[j + 1];
            }
            
            paintings[count - 1].paintingName = nullptr;
            count--;
            return;
        }
    }
}

void Gallery::print() const
{
    std::cout << "Gallery name: " << galleryName << std::endl;
    for (size_t i = 0; i < count; ++i)
    {
        std::cout << " ---" << paintings[i].paintingName << " : " << paintings[i].price << std::endl;
    }
}