//
// Created by Tysane Norine on 10/10/22.
//

#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_
#include <cmath>
#include <cstring>
#include <iostream>
#define EPS 1e-7

namespace s21 {
class S21Matrix {
 public:
  /**
   * constructors, destructor s*/
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
  S21Matrix InverseMatrix();
  /**
   * accessor and mutator */
  int GetRows() const;
  int GetCols() const;
  void SetRows(int rows);
  void SetCols(int cols);
  /**
   * overload operators */
  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix operator*(const double &num);
  bool operator==(const S21Matrix &other);
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(const double &other);
  double &operator()(int a, int b) const;

  /**
   * support func */
  void print();
  void init(double start);

 private:
  int rows_{}, cols_{};
  double *matrix_{};
  /**
   * support func */
  void CreateMartix();
  void RemoveMatrix();
  int SwapStr(S21Matrix *A, int x, int y, S21Matrix *result);
  void GetMiniMatr(int x, int y, S21Matrix *result);
  S21Matrix CopyMatrix(const S21Matrix &other, int rows, int cols);
};

}  // namespace s21

#endif  // SRC_S21_MATRIX_OOP_H_
