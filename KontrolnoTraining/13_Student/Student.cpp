#include "Student.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <ostream>

void Student::freeMemory()
{
    delete[] name;

    for (size_t i = 0; i < count; ++i)
    {
        delete[] exams[i].subject;
    }
    
    delete[] exams;
}

void Student::copyFrom(const Student& other)
{
    this->capacity = other.capacity;
    this->count = other.count;

    if (other.name != nullptr)
    {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
    }
    else
    {
        this->name = nullptr;
    }
    this->exams = new Exam[other.capacity];
    for (size_t i = 0; i < other.count; ++i)
    {
        exams[i].subject = new char[strlen(other.exams[i].subject) + 1];
        strcpy(exams[i].subject, other.exams[i].subject);
        
        exams[i].grade = other.exams[i].grade;
    }
    for (size_t i = this->count; i < this->capacity; ++i)
    {
        exams[i].subject = nullptr;
    }
}

void Student::moveFrom(Student&& other)
{
    this->name = other.name;
    this->exams = other.exams;
    this->capacity = other.capacity;
    this->count = other.count;
    
    other.name = nullptr;
    other.exams = nullptr;
    other.capacity = 0;
    other.count = 0;
}

void Student::resize(size_t newCapacity)
{
    if (newCapacity > capacity)
    {
        Exam* temp = new Exam[newCapacity];
        for (size_t i = 0; i < count; ++i)
        {
            temp[i] = exams[i];
        }
        for (size_t i = this->count; i < newCapacity; ++i)
        {
            temp[i].subject = nullptr;
        }
        
        delete[] exams;
        exams = temp;
        this->capacity = newCapacity;
    }
}

Student::~Student()
{
    freeMemory();
}

Student::Student(const Student& other)
{
    copyFrom(other);
}

Student& Student::operator=(const Student& other)
{
    if (this != &other)
    {
        freeMemory();
        copyFrom(other);
    }
    return *this;
}

Student::Student(Student&& other) noexcept
{
    moveFrom(std::move(other));
}

Student& Student::operator=(Student&& other) noexcept
{
    if (this != &other)
    {
        freeMemory();
        moveFrom(std::move(other));
    }
    return *this;
}

Student::Student() : count(0), capacity(2)
{
    this->name = nullptr;
    this->exams = new Exam[capacity];

    for (size_t i = 0; i < capacity; ++i)
    {
        this->exams[i].subject = nullptr;
    }
}

Student::Student(const char* name) : count(0), capacity(2)
{
    if (name != nullptr)
    {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }
    else this->name = nullptr;
    
    this->exams = new Exam[capacity];

    for (size_t i = 0; i < capacity; ++i)
    {
        this->exams[i].subject = nullptr;
    }
}

void Student::addExam(const char* subject, double grade)
{
    if (count == capacity)
    {
        resize(capacity * 2);
    }
    
    exams[count].subject = new char[strlen(subject) + 1];
    strcpy(exams[count].subject, subject);
    
    exams[count].grade = grade;
    
    count++;
}

double Student::operator()() const
{
    if (count == 0) return 0.0;

    double average = 0;
    
    for (size_t i = 0; i < count; ++i)
    {
        average += exams[i].grade;
    }
    average /= count;
    
    return average;
}

double Student::operator[](const char* searchSubject) const
{
    for (size_t i = 0; i < count; ++i)
    {
        if (strcmp(exams[i].subject, searchSubject) == 0) return exams[i].grade;
    }
    
    return -1;
}

void Student::print() const
{
    std::cout << (name ? name : "Unknown Student") << std::endl;

    for (size_t i = 0; i < count; ++i)
    {
        std::cout << exams[i].subject << " - " << exams[i].grade << std::endl;
    }
}

const char* Student::getName() const {
    return name;
}