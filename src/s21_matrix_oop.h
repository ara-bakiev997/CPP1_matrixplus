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
   * Constructors and  destructor */
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other) noexcept;
  ~S21Matrix();

  /**
   * Matrix method */
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
   * Accessor and mutator */
  int get_rows() const;
  int get_cols() const;
  void set_rows(int rows);
  void set_cols(int cols);
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
  const double &operator()(int a, int b) const;
  double &operator()(int a, int b);

  /**
   * support func */
  void print();
  void init(double start);
  double *get_matrix() const;

 private:
  int rows_{}, cols_{};
  double *matrix_{};
  /**
   * Support func */
  void CreateMartix_();
  void RemoveMatrix_();
  int SwapStr_(S21Matrix *src, int x, int y, S21Matrix *dest);
  void GetMiniMatr_(const int &x, const int &y, S21Matrix *result);
  S21Matrix CopyMatrix_(S21Matrix &other, int rows, int cols);
};

}  // namespace s21

#endif  // SRC_S21_MATRIX_OOP_H_
