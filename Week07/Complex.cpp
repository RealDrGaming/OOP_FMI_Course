#include "Complex.h"

#include "Complex.h"

// ==========================================
// Конструктори (Constructors)
// ==========================================

Complex::Complex() : realPart(0.0), imaginaryPart(0.0) {}

Complex::Complex(double real, double imaginary) : realPart(real), imaginaryPart(imaginary) {}

Complex::Complex(double real) : realPart(real), imaginaryPart(0.0) {}

// ==========================================
// Getters & Setters
// ==========================================

double Complex::getReal() const { return realPart; }
double Complex::getImaginary() const { return imaginaryPart; }

void Complex::setReal(double real) { realPart = real; }
void Complex::setImaginary(double imaginary) { imaginaryPart = imaginary; }

// ==========================================
// Member Operators (Modifying the object)
// ==========================================

Complex& Complex::operator+=(const Complex& other)
{
    this->realPart += other.realPart;
    this->imaginaryPart += other.imaginaryPart;
    return *this;
}

Complex& Complex::operator-=(const Complex& other)
{
    this->realPart -= other.realPart;
    this->imaginaryPart -= other.imaginaryPart;
    return *this;
}

Complex& Complex::operator*=(const Complex& other)
{
    // (a + bi)(c + di) = (ac - bd) + (ad + bc)i
    double newReal = (this->realPart * other.realPart) - (this->imaginaryPart * other.imaginaryPart);
    double newImaginary = (this->realPart * other.imaginaryPart) + (this->imaginaryPart * other.realPart);
    
    this->realPart = newReal;
    this->imaginaryPart = newImaginary;
    return *this;
}

Complex& Complex::operator/=(const Complex& other)
{
    // Denominator = c^2 + d^2
    double denominator = (other.realPart * other.realPart) + (other.imaginaryPart * other.imaginaryPart);
    
    // If dividing by zero, you could throw an exception here depending on your professor's rules.
    
    double newReal = ((this->realPart * other.realPart) + (this->imaginaryPart * other.imaginaryPart)) / denominator;
    double newImaginary = ((this->imaginaryPart * other.realPart) - (this->realPart * other.imaginaryPart)) / denominator;
    
    this->realPart = newReal;
    this->imaginaryPart = newImaginary;
    return *this;
}

// ==========================================
// Non-Member Operators
// ==========================================

// I/O Operators
std::ostream& operator<<(std::ostream& os, const Complex& obj)
{
    os << obj.realPart;
    
    // Format nicely so it outputs "3 + 4i" or "3 - 4i" instead of "3 + -4i"
    if (obj.imaginaryPart >= 0) {
        os << " + " << obj.imaginaryPart << "i";
    } else {
        os << " - " << -obj.imaginaryPart << "i";
    }
    
    return os;
}

std::istream& operator>>(std::istream& is, Complex& obj)
{
    // Expecting input like: 3 4 (for 3 + 4i)
    is >> obj.realPart >> obj.imaginaryPart;
    return is;
}

// Arithmetic Operators (Reusing the +=, -=, *=, /= logic to keep code DRY)
Complex operator+(const Complex& lhs, const Complex& rhs)
{
    Complex result = lhs;
    result += rhs;
    return result;
}

Complex operator-(const Complex& lhs, const Complex& rhs)
{
    Complex result = lhs;
    result -= rhs;
    return result;
}

Complex operator*(const Complex& lhs, const Complex& rhs)
{
    Complex result = lhs;
    result *= rhs;
    return result;
}

Complex operator/(const Complex& lhs, const Complex& rhs)
{
    Complex result = lhs;
    result /= rhs;
    return result;
}