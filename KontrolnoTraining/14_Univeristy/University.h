#pragma once

#include "../13_Student/Student.h"

class University
{
private:
    Student* students;
    size_t count;
    size_t capacity;
    
    void freeMemory();
    void copyFrom(const University& other);
    void moveFrom(University&& other);
    
    void resize(size_t newCapacity);
    
public:
    ~University();
    University(const University& other);
    University& operator=(const University& other);
    University(University&& other) noexcept;
    University& operator=(University&& other) noexcept;
    
    University();
    
    void addStudent(const Student& student);
    double getAverageScore() const;
    void expelStudent(const char* name);
    void print() const;
};
