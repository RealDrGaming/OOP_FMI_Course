#pragma once

Here is the complete implementation for the Complex class.

Unlike the Army class, you do not need the Rule of Five here. The Rule of Five is only required when your class manages dynamic memory (using new and delete). Because a complex number is just two standard double variables, the compiler's default memory management (the "Rule of Zero") is perfectly safe and highly efficient.

Here is the setup.

Complex.h
C++
#pragma once
#include <iostream>
#include <compare>

class Complex
{
private:
    double realPart;
    double imaginaryPart;

public:
    // Конструктори
    Complex();
    Complex(double real, double imaginary);
    
    // Allow implicit conversion from a real number (e.g., Complex c = 5.0;)
    Complex(double real); 

    // Getters & Setters
    double getReal() const;
    double getImaginary() const;
    void setReal(double real);
    void setImaginary(double imaginary);

    // ==========================================
    // Member Operators
    // ==========================================
    
    // Spaceship operator (C++20) for comparisons
    //auto operator<=>(const Complex& other) const = default;

    Complex& operator+=(const Complex& other);
    Complex& operator-=(const Complex& other);
    Complex& operator*=(const Complex& other);
    Complex& operator/=(const Complex& other);

    // ==========================================
    // Non-Member Operators
    // ==========================================
    
    friend std::ostream& operator<<(std::ostream& os, const Complex& obj);
    friend std::istream& operator>>(std::istream& is, Complex& obj);

    friend Complex operator+(const Complex& lhs, const Complex& rhs);
    friend Complex operator-(const Complex& lhs, const Complex& rhs);
    friend Complex operator*(const Complex& lhs, const Complex& rhs);
    friend Complex operator/(const Complex& lhs, const Complex& rhs);
};