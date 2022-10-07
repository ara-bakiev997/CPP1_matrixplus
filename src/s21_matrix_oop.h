#ifndef __S21MATRIX_H__
#define __S21MATRIX_H__
#include <cstring>
#include <iostream>

class S21Matrix {
private:
  int _rows, _cols;
  double **matrix;

public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();
  void print();
  void init(double start);
};

#endif