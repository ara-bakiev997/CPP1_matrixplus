//
// Created by Tysane Norine on 10/10/22.
//

#include "s21_matrix_oop.h"

/**
 * Default constructor*/
s21::S21Matrix::S21Matrix() {
  std::cout << "Default constructor" << std::endl;
  CreateMartix(5, 5);
}

/**
 * Parameterized constructor with number of rows and columns*/
s21::S21Matrix::S21Matrix(int rows, int cols) {
  std::cout << "Parameterized constructor" << std::endl;
  CreateMartix(rows, cols);
}
/**
 * Copy constructor */
s21::S21Matrix::S21Matrix(const S21Matrix &other) {
  std::cout << "Copy constructor" << std::endl;
  CreateMartix(other.rows_, other.cols_);
  std::memcpy(matrix_, other.matrix_, rows_ * cols_ * sizeof(double));
}
/**
 * Move constructor */
// s21::S21Matrix::S21Matrix(S21Matrix &&other) {
//   std::cout << "Move constructor" << std::endl;
//   if (rows_ * cols_ == other.rows_ * other.cols_) {
//	std::memcpy(matrix_, other.matrix_, other.rows_ * other.cols_ *
// sizeof(double));
//   } else {
//	matrix_ = new double[other.rows_ * other.cols_];
//	std::memcpy(matrix_, other.matrix_, other.rows_ * other.cols_ *
// sizeof(double));
//   }
//   cols_ = other.cols_;
//   rows_ = other.rows_;
//   other.cols_ = 0;
//   other.rows_ = 0;
// }
s21::S21Matrix::S21Matrix(S21Matrix &&other) {
  std::cout << "Move constructor" << std::endl;
  std::swap(matrix_, other.matrix_);
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
}

/**
 * Destructor */
s21::S21Matrix::~S21Matrix() {
  std::cout << "Destructor" << std::endl;
  RemoveMatrix();
}

/**
 * Matrix operations */
bool s21::S21Matrix::EqMatrix(const S21Matrix &other) {
  bool result = true;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    result = false;
  } else {
    for (auto i = 0; i < rows_ * cols_; ++i) {
      if (fabs(matrix_[i] - other.matrix_[i]) > EPS) {
        result = false;
        break;
      }
    }
  }
  return result;
}

void s21::S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  } else {
    for (auto i = 0; i < rows_ * cols_; ++i) {
      matrix_[i] += other.matrix_[i];
    }
  }
}

void s21::S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  } else {
    for (auto i = 0; i < rows_ * cols_; ++i) {
      matrix_[i] -= other.matrix_[i];
    }
  }
}

void s21::S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_ * cols_; ++i) {
    matrix_[i] *= num;
  }
}

void s21::S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::out_of_range(
        "The number of columns of the first matrix is not equal to the number "
        "of rows second matrix");
  }
  S21Matrix tmp(rows_, other.cols_);  // create temp matrix
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int x = 0; x < cols_; ++x) {
        tmp(i, j) += (*this)(i, x) * other(x, j);
      }
    }
  }
  // delete[] matrix_;
  // matrix_ = new double[rows_ * other.cols_];
  // cols_ = other.cols_;
  // std::memcpy(matrix_, other.matrix_, rows_ * other.cols_* sizeof(double));
  *this = tmp;
  // *this = std::move(tmp);
}

/**
 * Overload operators */
s21::S21Matrix &s21::S21Matrix::operator=(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    rows_ = other.rows_;
    cols_ = other.cols_;
    delete[] matrix_;
    matrix_ = new double[rows_ * cols_];
  }
  std::memcpy(matrix_, other.matrix_, rows_ * cols_ * sizeof(double));
  return *this;
}

double &s21::S21Matrix::operator()(int rows, int cols) const {
  if (rows >= rows_ || cols >= cols_) {
    throw std::out_of_range("Incorrect input, index is outside the matrix");
  }
  return matrix_[rows * cols_ + cols];
}

/**
 * Support functions */
void s21::S21Matrix::CreateMartix(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  matrix_ = new double[rows * cols];
}

void s21::S21Matrix::RemoveMatrix() {
  if (matrix_) {
    rows_ = 0;
    cols_ = 0;
    delete[] matrix_;
  }
}

void s21::S21Matrix::print() {
  //  std::cout << rows_ << std::endl;
  //  std::cout << cols_ << std::endl;
  for (auto i = 0; i < rows_; ++i) {
    for (auto j = 0; j < cols_; ++j) {
      std::cout << matrix_[i * cols_ + j] << ' ';
    }
    std::cout << std::endl;
  }
}

void s21::S21Matrix::init(double start) {
  for (auto i = 0; i < rows_ * cols_; ++i) {
    matrix_[i] = start++;
  }
}

int main() {
  std::cout << "_______FIRST_matrix_______" << std::endl;
  s21::S21Matrix mtr(4, 3);
  mtr.init(0);
  mtr.print();
  std::cout << "_______SECOND_matrix______" << std::endl;
  s21::S21Matrix mtr1(3, 4);
  mtr1.init(1);
  mtr1.print();
  mtr.MulMatrix(mtr1);
  std::cout << "_______RESULT_matrix______" << std::endl;
  mtr.print();

  //  std::cout << ((mtr1.EqMatrix(mtr) == true) ? "matrix equal" : "matrix
  //  isn't equal") << std::endl;

  return 0;
}
