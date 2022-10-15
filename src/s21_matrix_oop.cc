//
// Created by Tysane Norine on 10/10/22.
//

#include "s21_matrix_oop.h"

/**
 * Default constructor*/
s21::S21Matrix::S21Matrix() : rows_(5), cols_(5) {
  matrix_ = new double[rows_ * cols_];
}

/**
 * Parameterized constructor with number of rows and columns*/
s21::S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  matrix_ = new double[rows_ * cols_];
}
/**
 * Copy constructor */
s21::S21Matrix::S21Matrix(const S21Matrix &other) : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = new double[rows_ * cols_];
  std::memcpy(this->matrix_, other.matrix_, rows_ * cols_ * sizeof(double));
}
/**
 * Move constructor */
//s21::S21Matrix::S21Matrix(S21Matrix &&other) {
//  std::cout << "Move constructor" << std::endl;
//  if (rows_ * cols_ == other.rows_ * other.cols_) {
//	std::memcpy(matrix_, other.matrix_, other.rows_ * other.cols_ * sizeof(double));
//  } else {
//	matrix_ = new double[other.rows_ * other.cols_];
//	std::memcpy(matrix_, other.matrix_, other.rows_ * other.cols_ * sizeof(double));
//  }
//  cols_ = other.cols_;
//  rows_ = other.rows_;
//  other.cols_ = 0;
//  other.rows_ = 0;
//}
s21::S21Matrix::S21Matrix(S21Matrix &&other) {
  std::swap(matrix_, other.matrix_);
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
}

/**
 * Destructor */
s21::S21Matrix::~S21Matrix() {
  rows_ = 0;
  cols_ = 0;
  if (matrix_) {
	delete[] matrix_;
  }
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
	throw std::out_of_range("Incorrect input, matrices should have the same size");
  } else {
	for (auto i = 0; i < rows_ * cols_; ++i) {
	  matrix_[i] += other.matrix_[i];
	}
  }
}

void s21::S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
	throw std::out_of_range("Incorrect input, matrices should have the same size");
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

void s21::S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
      throw std::out_of_range("The number of columns of the first matrix is not equal to the number of rows second matrix");
  }
  delete[] matrix_;
  matrix_ = new double[rows_ * other.cols_];

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

double &s21::S21Matrix::operator()(int rows, int cols) {
    if (rows >= rows_ || cols >= cols_) {
        throw std::out_of_range("Incorrect input, index is outside the matrix");
    }
    return matrix_[rows * cols_ + cols];
}

/**
 * Support functions */

void s21::S21Matrix::print() {
  //  std::cout << rows_ << std::endl;
  //  std::cout << cols_ << std::endl;
  for (auto i = 0; i < rows_; i++) {
	for (auto j = 0; j < cols_; j++) {
	  std::cout << matrix_[i * rows_ + j] << ' ';
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
  s21::S21Matrix mtr(3, 3);
  mtr.init(0);
  mtr.print();
  std::cout << "value = " << mtr(1, 0) << std::endl;
//  s21::S21Matrix mtr1(3, 3);
//  std::cout << "_______SECOND_matrix______" << std::endl;
//  mtr1.init(0);
//  mtr1.print();
//  mtr1.SumMatrix(mtr);
//  std::cout << "_______RESULT_matrix______" << std::endl;
//  mtr.print();
  //  std::cout << ((mtr1.EqMatrix(mtr) == true) ? "matrix equal" : "matrix isn't equal") << std::endl;

  return 0;
}
