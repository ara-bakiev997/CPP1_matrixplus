//
// Created by Tysane Norine on 10/10/22.
//

#ifndef CPP1_S21_MATRIXPLUS_0_SRC_S21_MATRIX_OOP_H_
#define CPP1_S21_MATRIXPLUS_0_SRC_S21_MATRIX_OOP_H_

#include <iostream>

namespace s21 {
class S21Matrix {
 private:
  int _rows, _cols;
  double **matrix;

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other);
  ~S21Matrix();
  void print();
  void init(double  start);
};

}// namespace s21

#endif//CPP1_S21_MATRIXPLUS_0_SRC_S21_MATRIX_OOP_H_
