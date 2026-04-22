#pragma once

class Student
{
private:
    struct Exam
    {
        char* subject;
        double grade;
    };
    
    char* name;
    Exam* exams;
    size_t count;
    size_t capacity;
    
    void freeMemory();
    void copyFrom(const Student& other);
    void moveFrom(Student&& other);
    
    void resize(size_t newCapacity);
    
public:
    ~Student();
    Student(const Student& other);
    Student& operator=(const Student& other);
    Student(Student&& other) noexcept;
    Student& operator=(Student&& other) noexcept;
    
    Student();
    Student(const char* name);
    
    void addExam(const char* subject, double grade);
    double operator()() const;
    double operator[](const char* searchSubject) const;
    void print() const;
    const char* Student::getName() const;
};
