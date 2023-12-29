//
// Created by Kolakanmi Apanisile on 24/12/2023.
//

#ifndef KOLAKANMI_MATRIX_HPP
#define KOLAKANMI_MATRIX_HPP

#include <cstdio>
#include <initializer_list>
#include <istream>
#include <sstream>

using element = double;

class Matrix {
public:
    size_t rows;
    size_t cols;

    Matrix(size_t rows, size_t cols);
    Matrix(size_t rows, size_t cols, element *items);

    // constructor with initializer list
    Matrix(size_t rows, size_t cols, std::initializer_list<element> list);

    // constructor with io stream
    Matrix(size_t rows, size_t cols, std::istream &is);

    explicit Matrix(std::istream &is);

    // copy constructor
    Matrix(const Matrix &m);
    // copy assignment
    Matrix &operator=(const Matrix &m);
    // move constructor
    Matrix(Matrix &&m) noexcept;
    // move assignment
    Matrix &operator=(Matrix &&m) noexcept;

    // sum matrix
    Matrix operator+(const Matrix &m) const;

    [[nodiscard]] Matrix add(const Matrix &m) const;

    Matrix operator+(const Matrix &m);

    Matrix add(const Matrix &m);

    // subtract matrix
    Matrix operator-(const Matrix &m) const;

    [[nodiscard]] Matrix sub(const Matrix &m) const;

    Matrix operator-(const Matrix &m);

    Matrix sub(const Matrix &m);

    // multiply matrix
    Matrix operator*(const Matrix &m) const;

    [[nodiscard]] Matrix mul(const Matrix &m) const;



    element at(size_t row, size_t col) const;

    void set_value(size_t row, size_t col, element value);

    // destructor
    ~Matrix() {
        delete[] items;
    }
private:
    size_t stride;
    element *items;
};

Matrix::Matrix(size_t rows, size_t cols) {
    this->rows = rows;
    this->cols = cols;
    this->stride = cols;
    this->items = new element[rows * cols];
}

Matrix::Matrix(size_t rows, size_t cols, element *items) {
    this->rows = rows;
    this->cols = cols;
    this->stride = cols;
    this->items = items;
}

Matrix::Matrix(size_t rows, size_t cols, std::initializer_list<element> list) {
    this->rows = rows;
    this->cols = cols;
    this->stride = cols;
    this->items = new element[rows * cols];

    size_t i = 0;
    for (auto &e : list) {
        this->items[i] = e;
        ++i;
    }
}

Matrix::Matrix(size_t rows, size_t cols, std::istream &is) {
    this->rows = rows;
    this->cols = cols;
    this->stride = cols;
    this->items = new element[rows * cols];

    // use istream iterator to read data from stream
    auto iter = std::istream_iterator<element>(is);
    auto end = std::istream_iterator<element>();

    for (size_t i = 0; i < rows * cols && iter != end; ++i) {
        this->items[i] = *iter;
        ++iter;
    }
}

Matrix::Matrix(std::istream &is) {

    // stream should contain elements in the form of matrix
    // ===================
    // 1 2 3
    // 4 5 6
    // 7 8 9
    // ===================

    //read stream, line by line into a vector of strings
    std::vector<std::vector<element>> lines;
    std::string line;
    while (getline(is, line)) {
        std::istringstream iss(line);
        lines.emplace_back(std::istream_iterator<element>(iss),
                                             std::istream_iterator<element>());
    }

    // get the number of rows and cols
    rows = lines.size();

    // get the number of cols by counting the number of elements in the first line
    cols = lines.at(0).size();

    stride = cols;

    // allocate memory for the matrix
    this->items = new element[rows * cols];

    // copy the elements from the vector of vector of elements to the matrix
    size_t i = 0;
    for (auto &line : lines) {
        for (auto &e : line) {
            this->items[i] = e;
            ++i;
        }
    }
}

Matrix::Matrix(const Matrix &m) {
    this->rows = m.rows;
    this->cols = m.cols;
    this->stride = m.stride;
    this->items = new element[m.rows * m.cols];

    for (size_t i = 0; i < m.rows * m.cols; ++i) {
        this->items[i] = m.items[i];
    }
}

Matrix &Matrix::operator=(const Matrix &m) {
    if (this == &m) {
        return *this;
    }

    this->rows = m.rows;
    this->cols = m.cols;
    this->stride = m.stride;
    this->items = new element[m.rows * m.cols];

    for (size_t i = 0; i < m.rows * m.cols; ++i) {
        this->items[i] = m.items[i];
    }

    return *this;
}

Matrix::Matrix(Matrix &&m) noexcept : rows(0), cols(0), stride(0), items(nullptr) {
    this->rows = m.rows;
    this->cols = m.cols;
    this->stride = m.stride;
    this->items = m.items;

    m.rows = 0;
    m.cols = 0;
    m.stride = 0;
    m.items = nullptr;
}

Matrix &Matrix::operator=(Matrix &&m) noexcept{
    if (this == &m) {
        return *this;
    }

    delete[] this->items;

    this->rows = m.rows;
    this->cols = m.cols;
    this->stride = m.stride;
    this->items = m.items;

    m.rows = 0;
    m.cols = 0;
    m.stride = 0;
    m.items = nullptr;

    return *this;
}

Matrix Matrix::operator+(const Matrix &m) const {
    return this->add(m);
}

Matrix Matrix::add(const Matrix &m) const {
    Matrix result(this->rows, this->cols);

    for (size_t i = 0; i < this->rows * this->cols; ++i) {
        result.items[i] = this->items[i] + m.items[i];
    }

    return result;
}

Matrix Matrix::operator+(const Matrix &m) {
    return this->add(m);
}

Matrix Matrix::add(const Matrix &m) {

    for (size_t i = 0; i < this->rows * this->cols; ++i) {
        this->items[i] += m.items[i];
    }

    return *this;
}

Matrix Matrix::operator-(const Matrix &m) const{
    return this->sub(m);
}

Matrix Matrix::sub(const Matrix &m) const {
    Matrix result(this->rows, this->cols);

    for (size_t i = 0; i < this->rows * this->cols; ++i) {
        result.items[i] = this->items[i] - m.items[i];
    }

    return result;
}

Matrix Matrix::operator-(const Matrix &m) {
    return this->sub(m);
}

Matrix Matrix::sub(const Matrix &m) {

    for (size_t i = 0; i < this->rows * this->cols; ++i) {
        this->items[i] -= m.items[i];
    }

    return *this;
}

Matrix Matrix::operator*(const Matrix &m) const{
    return this->mul(m);
}

Matrix Matrix::mul(const Matrix &m) const {
    // A = m * n   B = n * p   A * B = m * p
    Matrix result(this->rows, m.cols);

    for (size_t i = 0; i < this->rows; ++i) {
        for (size_t j = 0; j < m.cols; ++j) {
            element sum = 0;
            for (size_t k = 0; k < this->cols; ++k) {
                sum += this->at(i, k) * m.at(k, j);
            }
            result.set_value(i, j, sum);
        }
    }

    return result;
}

element Matrix::at(size_t row, size_t col) const {
    return this->items[row * this->stride + col];
}

void Matrix::set_value(size_t row, size_t col, element value) {
    this->items[row * this->stride + col] = value;
}


#endif //KOLAKANMI_MATRIX_HPP
