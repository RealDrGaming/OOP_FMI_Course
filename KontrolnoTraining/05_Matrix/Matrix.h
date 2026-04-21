#pragma once

class Matrix
{
private:
    int** data;
    size_t cols;
    size_t rows;
    
    void freeMemory();
    void copyFrom(const Matrix& other);
    void moveFrom(Matrix&& other);

public:
    ~Matrix();
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);
    Matrix(Matrix&& other) noexcept;
    Matrix& operator=(Matrix&& other) noexcept;
    
    Matrix();
    Matrix(size_t rows, size_t cols);
    void set(size_t rows, size_t cols, int value);
    int get(size_t rows, size_t _cols) const;
    void print() const;
    
    Matrix operator+(const Matrix& other) const;
};
