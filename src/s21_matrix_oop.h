//
// Created by Tysane Norine on 10/10/22.
//

#ifndef CPP1_S21_MATRIXPLUS_0_SRC_S21_MATRIX_OOP_H_
#define CPP1_S21_MATRIXPLUS_0_SRC_S21_MATRIX_OOP_H_
#include <cmath>
#include <cstring>
#include <iostream>
#define EPS 1e-7

namespace s21 {
class S21Matrix {
 public:
  /**
   * constructors and destructors */
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other);
  ~S21Matrix();
  /**
   * matrix method */
  bool EqMatrix(const S21Matrix &other);
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  /**
   * overload operators */
  S21Matrix &operator=(const S21Matrix &other);
  double &operator()(int a, int b) const;
  /**
   * support func */
  void CreateMartix(int rows, int cols);
  void RemoveMatrix();
  void print();
  void init(double start);

 private:
  int rows_{}, cols_{};
  double *matrix_{};
};

}  // namespace s21

#endif  // CPP1_S21_MATRIXPLUS_0_SRC_S21_MATRIX_OOP_H_
