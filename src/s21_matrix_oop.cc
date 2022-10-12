//
// Created by Tysane Norine on 10/10/22.
//

#include "s21_matrix_oop.h"

/**
 * Default constructor*/
s21::S21Matrix::S21Matrix() : rows_(5), cols_(5) {
  std::cout << "Default constructor" << std::endl;
  matrix_ = new double[rows_ * cols_];
}

/**
 * Parameterized constructor with number of rows and columns*/
s21::S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  std::cout << "Parameterized constructor" << std::endl;
  matrix_ = new double[rows_ * cols_];
}
/**
 * Copy constructor */
s21::S21Matrix::S21Matrix(const S21Matrix &other) : rows_(other.rows_), cols_(other.cols_) {
  std::cout << "Copy constructor" << std::endl;
  matrix_ = new double[rows_ * cols_];
  memcpy(this->matrix_, other.matrix_, rows_ * cols_);
}
/**
 * Move constructor
 * https://www.bestprog.net/ru/2021/12/27/c-move-constructor-and-move-operator-ru/#q02
 */
s21::S21Matrix::S21Matrix(S21Matrix &&other) {
  std::cout << "Move constructor" << std::endl;
  if (rows_ * cols_ == other.rows_ * other.cols_) {
	std::memcpy(matrix_, other.matrix_, other.rows_ * other.cols_);
  } else {
	delete[] matrix_;
	matrix_ = new double[other.rows_ * other.cols_];
	std::memcpy(matrix_, other.matrix_, other.rows_ * other.cols_);
  }
  cols_ = other.cols_;
  rows_ = other.rows_;
  delete[] other.matrix_;
  other.cols_ = 0;
  other.rows_ = 0;
}

/**
 * Destructor */
s21::S21Matrix::~S21Matrix() {
  std::cout << "Destructor" << std::endl;
  rows_ = 0;
  cols_ = 0;
  if (matrix_) {
	delete[] matrix_;
  }
}

void s21::S21Matrix::print() {
  std::cout << rows_ << std::endl;
  std::cout << cols_ << std::endl;
  double tmp = matrix_[0];
  for (int i = 0; i < rows_; i++) {
	for (int j = 0; j < cols_; j++) {
	  std::cout << matrix_[i * rows_ + j] << ' ';
	}
	std::cout << std::endl;
  }
}

void s21::S21Matrix::init(double start) {
  std::cout << "init" << std::endl;
  double tmp = 0;
  for (int i = 0; i < rows_ * cols_; ++i) {
	matrix_[i] = start++;
  }
}

int main() {
  s21::S21Matrix mtr(4, 4);
  mtr.init(0);
  mtr.print();
  //  s21::S21Matrix mtr1(mtr);
  //  mtr1(&mtr);
  //  mtr1.print();
  // std::cout << "hello" << std::endl;

  return 0;
}
