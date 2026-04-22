#include "Polynomial.h"

#include <algorithm>

void Polynomial::freeMemory()
{
    delete[] coeffs;
    coeffs = nullptr;
}

void Polynomial::copyFrom(const Polynomial& other)
{
    this->degree = other.degree;
    
    this->coeffs = new int[other.degree + 1];
    
    for (size_t i = 0; i <= other.degree; ++i)
    {
        coeffs[i] = other.coeffs[i];
    }
}

void Polynomial::moveFrom(Polynomial&& other)
{
    this->coeffs = other.coeffs;
    this->degree = other.degree;
    
    other.coeffs = nullptr;
    other.degree = 0;
}

Polynomial::~Polynomial()
{
    freeMemory();
}

Polynomial::Polynomial(const Polynomial& other)
{
    copyFrom(other);
}

Polynomial& Polynomial::operator=(const Polynomial& other)
{
    if (this != &other)
    {
        freeMemory(); 
        copyFrom(other);
    }
    return *this;
}

Polynomial::Polynomial(Polynomial&& other) noexcept
{
    moveFrom(std::move(other));
}

Polynomial& Polynomial::operator=(Polynomial&& other) noexcept
{
    if (this != &other)
    {
        freeMemory(); 
        moveFrom(std::move(other));
    }
    return *this;
}

Polynomial::Polynomial() : degree(0)
{
    coeffs = new int[1];
    coeffs[0] = 0;
}

Polynomial::Polynomial(size_t maxDegree) : degree(maxDegree)
{
    coeffs = new int[maxDegree + 1];
    
    for (size_t i = 0; i <= maxDegree; ++i)
    {
        this->coeffs[i] = 0;
    }
}

int& Polynomial::operator[](size_t index)
{
    if (index <= degree)
    {
        return coeffs[index];
    }
    
    return coeffs[0];
}

int Polynomial::operator[](size_t index) const
{
    if (index <= degree)
    {
        return coeffs[index];
    }
    
    return coeffs[0];
}

bool Polynomial::operator==(const Polynomial& other) const
{
    if (this->degree != other.degree) return false;
    
    for (size_t i = 0; i <= degree; ++i)
    {
        if (coeffs[i] != other.coeffs[i])
        {
            return false;
        }
    }
    
    return true;
}

long long Polynomial::operator()(int x) const
{
    long long sum = 0;
    
    for (size_t i = 0; i <= degree; ++i)
    {
        sum += coeffs[i] * pow(x, i);
    }
    
    return sum;
}

Polynomial Polynomial::operator+(const Polynomial& other) const
{
    size_t biggerDegree = std::max(this->degree, other.degree);
    size_t smallerDegree = std::min(this->degree, other.degree);
    
    bool isThisDegreeBigger = biggerDegree == this->degree;
    
    Polynomial result(biggerDegree);
    
    for (size_t i = 0; i <= smallerDegree; ++i)
    {
        result.coeffs[i] = this->coeffs[i] + other.coeffs[i];
    }

    for (size_t i = smallerDegree + 1; i <= biggerDegree; ++i)
    {
        if (isThisDegreeBigger)
        {
            result.coeffs[i] = this->coeffs[i];
        }
        else
        {
            result.coeffs[i] = other.coeffs[i];
        }
    }
    
    return result;
}