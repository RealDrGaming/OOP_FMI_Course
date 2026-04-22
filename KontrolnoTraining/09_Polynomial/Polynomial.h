#pragma once

class Polynomial
{
private:
    size_t degree;
    int* coeffs;
    
    void freeMemory();
    void copyFrom(const Polynomial& other);
    void moveFrom(Polynomial&& other);
    
public:
    ~Polynomial();
    Polynomial(const Polynomial& other);
    Polynomial& operator=(const Polynomial& other);
    Polynomial(Polynomial&& other) noexcept;
    Polynomial& operator=(Polynomial&& other) noexcept;
    
    Polynomial();
    Polynomial(size_t maxDegree);
    
    int& operator[](size_t index);
    int operator[](size_t index) const;
    bool operator==(const Polynomial& other) const;
    long long operator()(int x) const;
    Polynomial operator+(const Polynomial& other) const;
};
