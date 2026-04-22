#include "University.h"

#include <algorithm>
#include <iostream>

void University::freeMemory()
{
    delete[] students;
}

void University::copyFrom(const University& other)
{
    this->count = other.count;
    this->capacity = other.capacity;
    
    this->students = new Student[other.capacity];

    for (size_t i = 0; i < count; ++i)
    {
        this->students[i] = other.students[i];
    }
}

void University::moveFrom(University&& other)
{
    this->students = other.students;
    this->count = other.count;
    this->capacity = other.capacity;
    
    other.students = nullptr;
    other.count = 0;
    other.capacity = 0;
}

void University::resize(size_t newCapacity)
{
    if (newCapacity > this->capacity)
    {
        Student* temp = new Student[newCapacity];

        for (size_t i = 0; i < count; ++i)
        {
            temp[i] = this->students[i];
        }
    
        delete[] this->students;
        this->students = temp;
        this->capacity = newCapacity;
    }
}

University::~University()
{
    freeMemory();
}

University::University(const University& other)
{
    copyFrom(other);
}

University& University::operator=(const University& other)
{
    if (this != &other)
    {
        freeMemory();
        copyFrom(other);
    }
    return *this;
}

University::University(University&& other) noexcept
{
    moveFrom(std::move(other));
}

University& University::operator=(University&& other) noexcept
{
    if (this != &other)
    {
        freeMemory();
        moveFrom(std::move(other));
    }
    return *this;
}

University::University() : count(0), capacity(2)
{
    students = new Student[capacity];
}

void University::addStudent(const Student& student)
{
    if (count == capacity)
    {
        resize(capacity * 2);
    }
    
    students[count] = student;
    count++;
}

double University::getAverageScore() const
{
    if (count == 0) return -1;

    double average = 0;
    
    for (size_t i = 0; i < this->count; ++i)
    {
        average += students[i]();
    }
    
    average /= this->count;
    
    return average;
}

void University::expelStudent(const char* name)
{
    for (size_t i = 0; i < count; ++i)
    {
        if (strcmp(name, students[i].getName()) == 0)
        {
            for (size_t j = i; j < count - 1; ++j)
            {
                students[j] = students[j + 1];
            }
            count--;
            return;
        }
    }
}

void University::print() const
{
    for (size_t i = 0; i < count; ++i)
    {
        std::cout << "Student: " << i << std::endl;
        students[i].print();
        std::cout << std::endl;
    }
}