//
// Created by Tysane Norine on 10/10/22.
//

#include "s21_matrix_oop.h"

/**
 * Default constructor*/
s21::S21Matrix::S21Matrix() : _rows(5), _cols(5) {
  std::cout << "Default constructor" << std::endl;
  matrix = (double **) new double[sizeof(double) * _rows * _cols + sizeof(double *) * _rows];
  double *ptr = (double *) (matrix + _rows);
  for (int i = 0; i < _rows; i++) {
	matrix[i] = ptr + i * _cols;
  }
}

/**
 * Parameterized constructor with number of rows and columns*/
s21::S21Matrix::S21Matrix(int rows, int cols) : _rows(rows), _cols(cols) {
  std::cout << "Parameterized constructor" << std::endl;
  matrix = (double **) new double[sizeof(double) * _rows * _cols + sizeof(double *) * _rows];
  double *ptr = (double *) (matrix + _rows);
  for (int i = 0; i < _rows; i++) {
	matrix[i] = ptr + i * _cols;
  }
}
/**
 * Copy constructor */
s21::S21Matrix::S21Matrix(const S21Matrix &other) {
  std::cout << "Copy constructor" << std::endl;
  this->_rows = other._rows;
  this->_cols = other._cols;
  int len = sizeof(double) * _rows * _cols + sizeof(double *) * _rows;
  this->matrix = (double **) new double[len];
  memcpy(this->matrix, other.matrix, len);
}
/**
 * Move constructor
 * https://www.bestprog.net/ru/2021/12/27/c-move-constructor-and-move-operator-ru/#q02
 */
s21::S21Matrix::S21Matrix(S21Matrix &&other) {
  std::cout << "Move constructor" << std::endl;
  int len = sizeof(double) * other._rows * other._cols + sizeof(double *) * other._rows;
  if (other._rows == this->_rows && other._cols == this->_cols) {
	std::memcpy(this->matrix, other.matrix, len);
  } else {
	delete[] this->matrix;
	this->matrix = (double **) new double[len];
	std::memcpy(this->matrix, other.matrix, len);
  }
  this->_cols = other._cols;
  this->_rows = other._rows;
  delete[] other.matrix;
  other._cols = 0;
  other._rows = 0;
}

/**
 * Destructor */
s21::S21Matrix::~S21Matrix() {
  std::cout << "Destructor" << std::endl;
  this->_rows = 0;
  this->_cols = 0;
  if (matrix) {
	delete[] matrix;
  }
}

void s21::S21Matrix::print() {
  std::cout << this->_rows << std::endl;
  std::cout << this->_cols << std::endl;
  for (int i = 0; i < _rows; i++) {
	for (int j = 0; j < _cols; j++) {
	  std::cout << matrix[i][j] << ' ';
	}
	std::cout << std::endl;
  }
}

void s21::S21Matrix::init(double start) {
  for (int i = 0; i < this->_rows; i++) {
	for (int j = 0; j < this->_cols; j++) {
	  matrix[i][j] = start++;
	}
  }
}

//int main() {
//  s21::S21Matrix mtr(4, 4);
//  mtr.init(10);
//  mtr.print();
//  s21::S21Matrix mtr1(mtr);
//  //  mtr1(&mtr);
//  mtr1.print();
//  // std::cout << "hello" << std::endl;
//
//  return 0;
//}