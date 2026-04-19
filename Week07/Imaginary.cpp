#include "Imaginary.h"
#include "Complex.h"

// ==========================================
// Конструктори (Constructors)
// ==========================================

// Конструктор по подразбиране (Default constructor) - стойност 1
Imaginary::Imaginary() : coefficient(1.0) {}

// Параметричен конструктор
Imaginary::Imaginary(double coefficient) : coefficient(coefficient) {}

// ==========================================
// Getters & Setters
// ==========================================

double Imaginary::getCoefficient() const
{
    return coefficient;
}

void Imaginary::setCoefficient(double coeff)
{
    coefficient = coeff;
}

// ==========================================
// Member Operators (Modifying the object)
// ==========================================

Imaginary& Imaginary::operator+=(const Imaginary& other)
{
    this->coefficient += other.coefficient;
    return *this;
}

Imaginary& Imaginary::operator-=(const Imaginary& other)
{
    this->coefficient -= other.coefficient;
    return *this;
}

Imaginary& Imaginary::operator*=(double scalar)
{
    this->coefficient *= scalar;
    return *this;
}

Imaginary& Imaginary::operator/=(double scalar)
{
    this->coefficient /= scalar;
    return *this;
}

// ==========================================
// Non-Member Operators (Friend functions)
// ==========================================

// Вход / Изход (I/O Operators)
std::ostream& operator<<(std::ostream& os, const Imaginary& obj)
{
    os << obj.coefficient << "i";
    return os;
}

std::istream& operator>>(std::istream& is, Imaginary& obj)
{
    is >> obj.coefficient;
    return is;
}

// Imaginary and Imaginary arithmetic
Imaginary operator+(const Imaginary& lhs, const Imaginary& rhs)
{
    return Imaginary(lhs.coefficient + rhs.coefficient);
}

Imaginary operator-(const Imaginary& lhs, const Imaginary& rhs)
{
    return Imaginary(lhs.coefficient - rhs.coefficient);
}

double operator*(const Imaginary& lhs, const Imaginary& rhs)
{
    // (a*i) * (b*i) = a*b * i^2 = -(a*b)
    return -(lhs.coefficient * rhs.coefficient);
}

double operator/(const Imaginary& lhs, const Imaginary& rhs)
{
    // (a*i) / (b*i) = a / b
    return lhs.coefficient / rhs.coefficient;
}

// ------------------------------------------
// Commutative Operators with double
// ------------------------------------------

// Multiplication (Commutative)
Imaginary operator*(const Imaginary& lhs, double rhs)
{
    return Imaginary(lhs.coefficient * rhs);
}

Imaginary operator*(double lhs, const Imaginary& rhs)
{
    return Imaginary(lhs * rhs.coefficient);
}

// Addition (Commutative, Returns Complex)
// Assuming Complex constructor is: Complex(double real, double imaginary)
Complex operator+(const Imaginary& lhs, double rhs)
{
    // (a*i) + b = b + a*i
    return Complex(rhs, lhs.coefficient);
}

Complex operator+(double lhs, const Imaginary& rhs)
{
    // b + (a*i) = b + a*i
    return Complex(lhs, rhs.coefficient);
}

// Subtraction (Not strictly commutative in logic, but handles both parameter orders)
Complex operator-(const Imaginary& lhs, double rhs)
{
    // (a*i) - b = -b + a*i
    return Complex(-rhs, lhs.coefficient);
}

Complex operator-(double lhs, const Imaginary& rhs)
{
    // b - (a*i) = b - a*i
    return Complex(lhs, -rhs.coefficient);
}