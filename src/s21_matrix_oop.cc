//
// Created by Tysane Norine on 10/10/22.
//

#include "s21_matrix_oop.h"

/**
 * Default constructor*/
s21::S21Matrix::S21Matrix() : rows_(5), cols_(5) { CreateMartix_(); }
/**
 * Parameterized constructor with number of rows and columns*/
s21::S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  CreateMartix_();
}
/**
 * Copy constructor */
s21::S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  CreateMartix_();
  std::memcpy(matrix_, other.matrix_, rows_ * cols_ * sizeof(double));
}
/**
 * Move constructor */
s21::S21Matrix::S21Matrix(S21Matrix &&other) noexcept
    : rows_(0), cols_(0), matrix_(nullptr) {
  std::swap(matrix_, other.matrix_);
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
}
/**
 * Destructor */
s21::S21Matrix::~S21Matrix() { RemoveMatrix_(); }

/**
 * Matrix operations */
bool s21::S21Matrix::EqMatrix(const S21Matrix &other) {
  bool result = true;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    result = false;
  } else {
    for (auto i = 0; i < rows_ * cols_; ++i) {
      result = fabs(matrix_[i] - other.matrix_[i]) < EPS;
      if (!result) {
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
  }
  for (auto i = 0; i < rows_ * cols_; ++i) {
    matrix_[i] += other.matrix_[i];
  }
}

void s21::S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  for (auto i = 0; i < rows_ * cols_; ++i) {
    matrix_[i] -= other.matrix_[i];
  }
}

void s21::S21Matrix::MulNumber(const double num) {
  for (auto i = 0; i < rows_ * cols_; ++i) {
    matrix_[i] *= num;
  }
}

void s21::S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::out_of_range(
        "The number of columns of the first matrix is not equal to the number "
        "of rows second matrix");
  }
  S21Matrix tmp(rows_, other.cols_);
  for (auto i = 0; i < rows_; ++i) {
    for (auto j = 0; j < other.cols_; ++j) {
      for (auto x = 0; x < cols_; ++x) {
        tmp(i, j) += (*this)(i, x) * other(x, j);
      }
    }
  }
  *this = std::move(tmp);
}

s21::S21Matrix s21::S21Matrix::Transpose() {
  S21Matrix temp(cols_, rows_);
  for (auto i = 0; i < rows_; ++i) {
    for (auto j = 0; j < cols_; ++j) {
      temp(j, i) = (*this)(i, j);
    }
  }
  return temp;
}

s21::S21Matrix s21::S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::out_of_range("Invalid input, the matrix is not square");
  }
  S21Matrix result(rows_, cols_);
  double sign = 1;
  if (rows_ == 1) {
    result(0, 0) = (*this)(0, 0);
  } else {
    for (auto i = 0; i < rows_; ++i) {
      for (auto j = 0; j < cols_; ++j) {
        S21Matrix temp(rows_ - 1, cols_ - 1);
        GetMiniMatr_(i, j, &temp);
        sign = pow(-1, i + j);
        result(i, j) = sign * temp.Determinant();
        //		result(i, j) = sign * result(i, j); // скорее всего
        //решение выше лучше
      }
    }
  }
  return result;
}
/**
 * Used the Gaussian elimination method */
double s21::S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::out_of_range("Invalid input, the matrix is not square");
  }
  int check = 0, sign = 1;
  double quotient = 0, result = 1;
  if (rows_ == 1) {
    result = (*this)(0, 0);  // determinant for matrix 1x1
  } else if (rows_ == 2) {
    result = (*this)(0, 0) * (*this)(1, 1) -
             (*this)(0, 1) * (*this)(1, 0);  // determinant for matrix 2x2
  } else {
    S21Matrix temp(*this);
    for (auto i = 0; i < temp.rows_; ++i) {
      if (temp(i, i) == 0) {
        check = SwapStr_(&temp, i, i, &temp);
        sign = -sign;  // if you swap, then change the sign
      }
      if (!check) {
        for (auto j = i + 1; j < temp.rows_; ++j) {
          quotient = temp(j, i) / temp(i, i);
          for (auto x = i; x < temp.cols_; ++x) {
            temp(j, x) = temp(j, x) - quotient * temp(i, x);
          }
        }
        result *= temp(i, i);
      } else {
        result = 0;
        break;
      }
    }
    if (!check)
      result *= sign;  // проверь всегда ли верный знак получается, мб условие
                       // не нужно
  }
  return result;
}

s21::S21Matrix s21::S21Matrix::InverseMatrix() {
  double determinant = 0;
  determinant = (*this).Determinant();
  if (!determinant) {
    throw std::out_of_range("Invalid input, matrix determinant is 0");
  }
  S21Matrix temp = (*this).CalcComplements();
  temp = temp.Transpose();
  temp.MulNumber(1 / determinant);
  return temp;
}
/**
 * Accessor and mutator */
int s21::S21Matrix::get_rows() const { return rows_; }

int s21::S21Matrix::get_cols() const { return cols_; }

void s21::S21Matrix::set_rows(int rows) {
  if (rows_ != rows) {
    S21Matrix temp(rows, cols_);
    int rows_tmp = (rows > rows_) ? rows_ : rows;
    *this = CopyMatrix_(temp, rows_tmp, cols_);
  }
}

void s21::S21Matrix::set_cols(int cols) {
  if (cols_ != cols) {
    S21Matrix temp(rows_, cols);
    int cols_tmp = (cols > cols_) ? cols_ : cols;
    *this = CopyMatrix_(temp, rows_, cols_tmp);
  }
}
/**
 * Overload operators */
s21::S21Matrix s21::S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix temp(*this);
  temp.SumMatrix(other);
  return temp;
}

s21::S21Matrix s21::S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix temp(*this);
  temp.SubMatrix(other);
  return temp;
}

s21::S21Matrix s21::S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix temp(*this);
  temp.MulMatrix(other);
  return temp;
}

s21::S21Matrix s21::S21Matrix::operator*(const double &num) {
  S21Matrix temp(*this);
  temp.MulNumber(num);
  return temp;
}

bool s21::S21Matrix::operator==(const S21Matrix &other) {
  return this->EqMatrix(other);
}

s21::S21Matrix &s21::S21Matrix::operator=(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    (*this).RemoveMatrix_();
    rows_ = other.rows_;
    cols_ = other.cols_;
    this->CreateMartix_();
  }
  std::copy(other.matrix_, other.matrix_ + other.rows_ * other.cols_,
            this->matrix_);
  // std::memcpy(matrix_, other.matrix_, rows_ * cols_ * sizeof(double));
  return *this;
}

s21::S21Matrix &s21::S21Matrix::operator+=(const S21Matrix &other) {
  (*this).SumMatrix(other);
  return *this;
}

s21::S21Matrix &s21::S21Matrix::operator-=(const S21Matrix &other) {
  (*this).SubMatrix(other);
  return *this;
}

s21::S21Matrix &s21::S21Matrix::operator*=(const S21Matrix &other) {
  (*this).MulMatrix(other);
  return *this;
}

s21::S21Matrix &s21::S21Matrix::operator*=(const double &other) {
  (*this).MulNumber(other);
  return *this;
}

const double &s21::S21Matrix::operator()(int rows, int cols) const {
  if (rows >= rows_ || cols >= cols_) {
    throw std::out_of_range("Incorrect input, index is outside the matrix");
  }
  if (rows < 0 || cols < 0) {
    throw std::out_of_range("Incorrect input, index less than zero");
  }
  return matrix_[rows * cols_ + cols];
}

double &s21::S21Matrix::operator()(int rows, int cols) {
  if (rows >= rows_ || cols >= cols_) {
    throw std::out_of_range("Incorrect input, index is outside the matrix");
  }
  if (rows < 0 || cols < 0) {
    throw std::out_of_range("Incorrect input, index less than zero");
  }
  return matrix_[rows * cols_ + cols];
}

/**
 * Support functions */
void s21::S21Matrix::CreateMartix_() {
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::out_of_range("Incorrect input, index less than zero");
  }
  matrix_ = new double[rows_ * cols_]{};
}

void s21::S21Matrix::RemoveMatrix_() {
  if (matrix_) {
    delete[] matrix_;
    matrix_ = nullptr;
    rows_ = 0;
    cols_ = 0;
  }
}

int s21::S21Matrix::SwapStr_(S21Matrix *src, int x, int y, S21Matrix *dest) {
  int error = 0;
  int i = 0;
  //  *dest = *src;  //внимание
  for (i = x; i < src->rows_; ++i) {
    if ((*src)(i, y) != 0) {
      error = 0;
      break;
    } else {
      error = 1;
    }
  }
  if (!error) {
    double tmp = 0;
    for (auto j = 0; j < src->cols_; ++j) {
      tmp = (*src)(x, j);
      (*src)(x, j) = (*dest)(i, j);
      (*dest)(i, j) = tmp;
    }
  }
  return error;
}

void s21::S21Matrix::GetMiniMatr_(const int &x, const int &y,
                                  S21Matrix *result) {
  int di = 0, dj = 0;
  for (auto i = 0; i < (rows_ - 1); ++i) {
    if (i == x) di = 1;
    dj = 0;
    for (auto j = 0; j < (rows_ - 1); ++j) {
      if (j == y) dj = 1;
      (*result)(i, j) = (*this)((i + di), (j + dj));
    }
  }
}

s21::S21Matrix s21::S21Matrix::CopyMatrix_(S21Matrix &other, int rows,
                                           int cols) {
  for (auto i = 0; i < rows; ++i) {
    for (auto j = 0; j < cols; ++j) {
      other(i, j) = (*this)(i, j);
    }
  }
  return other;
}

// void s21::S21Matrix::print() {
//   for (auto i = 0; i < rows_; ++i) {
//     for (auto j = 0; j < cols_; ++j) {
//       std::cout << matrix_[i * cols_ + j] << ' ';
//     }
//     std::cout << std::endl;
//   }
// }

// void s21::S21Matrix::init(double start) {
//   for (auto i = 0; i < rows_ * cols_; ++i) {
//     matrix_[i] = start++;
//   }
//   // matrix_[0] = 1;
//   // matrix_[1] = 2;
//   // matrix_[2] = 3;
//   matrix_[3] = 0;
//   // matrix_[4] = 4;
//   // matrix_[5] = 2;
//   // matrix_[6] = 5;
//   // matrix_[7] = 2;
//   matrix_[8] = 3;
// }

double *s21::S21Matrix::get_matrix() const { return this->matrix_; }