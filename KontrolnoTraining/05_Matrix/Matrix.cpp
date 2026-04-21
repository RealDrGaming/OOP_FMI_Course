#include "Matrix.h"

#include <algorithm>
#include <iostream>
#include <ostream>

void Matrix::freeMemory()
{
    for (size_t i = 0; i < rows; ++i)
    {
        delete[] data[i];
    }
    delete[] data;
}

void Matrix::copyFrom(const Matrix& other)
{
    this->rows = other.rows;
    this->cols = other.cols;
    
    if (other.data == nullptr) {
        this->data = nullptr;
        return;
    }
    
    this->data = new int*[this->rows];
    
    for (size_t i = 0; i < this->rows; ++i)
    {
        this->data[i] = new int[this->cols];
        
        for (size_t j = 0; j < this->cols; ++j)
        {
            this->data[i][j] = other.data[i][j];
        }
    }
}

void Matrix::moveFrom(Matrix&& other)
{
    this->data = other.data;
    this->rows = other.rows;
    this->cols = other.cols;
    
    other.data = nullptr;
    other.rows = 0;
    other.cols = 0;
}

Matrix::~Matrix()
{
    freeMemory();
}

Matrix::Matrix(const Matrix& other)
{
    copyFrom(other);
}

Matrix& Matrix::operator=(const Matrix& other)
{
    if (this != &other)
    {
        freeMemory();
        copyFrom(other);
    }
    return *this;
}

Matrix::Matrix(Matrix&& other) noexcept
{
    moveFrom(std::move(other));
}

Matrix& Matrix::operator=(Matrix&& other) noexcept
{
    if (this != &other)
    {
        freeMemory();
        moveFrom(std::move(other));
    }
    return *this;
}

Matrix::Matrix() : cols(0), rows(0)
{
    data = nullptr;
}

Matrix::Matrix(size_t rows, size_t cols) : cols(cols), rows(rows)
{
    data = new int*[rows];

    for (size_t i = 0; i < rows; ++i)
    {
        data[i] = new int[cols];
        for (size_t j = 0; j < cols; ++j)
        {
            data[i][j] = 0;
        }
    }
}

void Matrix::set(size_t _rows, size_t _cols, int value)
{
    if (this->rows <= _rows || this->cols <= _cols) return;
    this->data[_rows][_cols] = value;
}

int Matrix::get(size_t _rows, size_t _cols) const
{
    if (this->rows <= _rows || this->cols <= _cols) return -1;
    return this->data[_rows][_cols];
}

void Matrix::print() const
{
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            std::cout << data[i][j] << " ";
        }
        
        std::cout << std::endl;
    }
}

Matrix Matrix::operator+(const Matrix& other) const
{
    if (this-> rows != other.rows || this-> cols != other.cols)
    {
        return Matrix();
    }
    
    Matrix result(this->rows, this->cols);
    
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; i < cols; ++j)
        {
            result.data[i][j] = this->data[i][j] + other.data[i][j];
        }
    }
    
    return result;
}