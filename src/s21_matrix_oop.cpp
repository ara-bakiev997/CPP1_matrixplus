#include "s21_matrix_oop.h"

/*
 * Parameterized constructor with number of rows and columns **/
S21Matrix::S21Matrix(int rows, int cols) : _rows(rows), _cols(cols) {
  matrix = (double **)new double[sizeof(double) * _rows * _cols +
								 sizeof(double *) * _rows];
  double *ptr = (double *)(matrix + _rows);
  for (int i = 0; i < _rows; i++) {
	matrix[i] = ptr + i * _cols;
  }
}

void S21Matrix::print() {
  std::cout << this->_rows << std::endl;
  std::cout << this->_cols << std::endl;
  for (int i = 0; i < _rows; i++) {
	for (int j = 0; j < _cols; j++) {
	  std::cout << matrix[i][j] << ' ' ;
	}
	std::cout << std::endl;
}
}
void S21Matrix::init(double start) {
  for (int i = 0; i < this->_rows; i++) {
	for (int j = 0; j < this->_cols; j++) {
	  matrix[i][j] = start++;
	}
  }
}

S21Matrix::~S21Matrix() {
  this->_rows = 0;
  this->_cols = 0;
  delete[] matrix;
}

int main() {
  S21Matrix mtr(3, 3);
  mtr.init(10);
  mtr.print();
  // std::cout << "hello" << std::endl;

  return 0;
}