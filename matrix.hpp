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

    Matrix(std::istream &is);

    // copy constructor
    Matrix(const Matrix &m);
    // copy assignment
    Matrix &operator=(const Matrix &m);
    // move constructor
    Matrix(Matrix &&m) noexcept;
    // move assignment
    Matrix &operator=(Matrix &&m) noexcept;
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

Matrix::Matrix(Matrix &&m) noexcept{
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

#endif //KOLAKANMI_MATRIX_HPP
