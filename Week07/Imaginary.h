#pragma once
#include <iostream>
#include <compare>

class Complex; // Forward declaration needed for the return types

class Imaginary
{
private:
    // Реалната част пред имагинерната единица (e.g., the 'b' in b*i)
    double coefficient; 

public:
    // Конструктор по подразбиране (Default constructor)
    Imaginary();

    // Параметричен конструктор
    explicit Imaginary(double coefficient);

    // Getter & Setter
    double getCoefficient() const;
    void setCoefficient(double coefficient);

    // ==========================================
    // Member Operators (Modifying the object)
    // ==========================================
    
    // Three-way comparison (C++20)
    //auto operator<=>(const Imaginary& other) const = default;

    Imaginary& operator+=(const Imaginary& other);
    Imaginary& operator-=(const Imaginary& other);
    Imaginary& operator*=(double scalar);
    Imaginary& operator/=(double scalar);

    // ==========================================
    // Non-Member Operators (Friend functions)
    // ==========================================

    // I/O Operators
    friend std::ostream& operator<<(std::ostream& os, const Imaginary& obj);
    friend std::istream& operator>>(std::istream& is, Imaginary& obj);

    // Imaginary and Imaginary operations
    friend Imaginary operator+(const Imaginary& lhs, const Imaginary& rhs);
    friend Imaginary operator-(const Imaginary& lhs, const Imaginary& rhs);
    friend double operator*(const Imaginary& lhs, const Imaginary& rhs);
    friend double operator/(const Imaginary& lhs, const Imaginary& rhs);

    // ------------------------------------------
    // Commutative Operators with double
    // ------------------------------------------

    // Multiplication
    friend Imaginary operator*(const Imaginary& lhs, double rhs);
    friend Imaginary operator*(double lhs, const Imaginary& rhs);

    // Addition (Returns Complex)
    friend Complex operator+(const Imaginary& lhs, double rhs);
    friend Complex operator+(double lhs, const Imaginary& rhs);

    // Subtraction (Returns Complex)
    friend Complex operator-(const Imaginary& lhs, double rhs);
    friend Complex operator-(double lhs, const Imaginary& rhs);
};