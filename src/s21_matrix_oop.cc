//
// Created by Tysane Norine on 10/10/22.
//

#include "s21_matrix_oop.h"

/**
 * Default constructor*/
s21::S21Matrix::S21Matrix() : rows_(5), cols_(5) {
  std::cout << "Default constructor" << std::endl;
  CreateMartix();
}

/**
 * Parameterized constructor with number of rows and columns*/
s21::S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  std::cout << "Parameterized constructor" << std::endl;
  CreateMartix();
}
/**
 * Copy constructor */
s21::S21Matrix::S21Matrix(const S21Matrix &other) : rows_(other.rows_), cols_(other.cols_) {
  std::cout << "Copy constructor" << std::endl;
  CreateMartix();
  std::memcpy(matrix_, other.matrix_, rows_ * cols_ * sizeof(double));
}
/**
 * Move constructor */
// s21::S21Matrix::S21Matrix(S21Matrix &&other) {
//   std::cout << "Move constructor" << std::endl;
//   if (rows_ * cols_ == other.rows_ * other.cols_) {
//	std::memcpy(matrix_, other.matrix_, other.rows_ * other.cols_ *
// sizeof(double));
//   } else {
//	matrix_ = new double[other.rows_ * other.cols_];
//	std::memcpy(matrix_, other.matrix_, other.rows_ * other.cols_ *
// sizeof(double));
//   }
//   cols_ = other.cols_;
//   rows_ = other.rows_;
//   other.cols_ = 0;
//   other.rows_ = 0;
// }
s21::S21Matrix::S21Matrix(S21Matrix &&other) {
  std::cout << "Move constructor" << std::endl;
  std::swap(matrix_, other.matrix_);
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
}

/**
 * Destructor */
s21::S21Matrix::~S21Matrix() {
  std::cout << "Destructor" << std::endl;
  RemoveMatrix();
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
	throw std::out_of_range(
		"Incorrect input, matrices should have the same size");
  } else {
	for (auto i = 0; i < rows_ * cols_; ++i) {
	  matrix_[i] += other.matrix_[i];
	}
  }
}

void s21::S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
	throw std::out_of_range(
		"Incorrect input, matrices should have the same size");
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

void s21::S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
	throw std::out_of_range(
		"The number of columns of the first matrix is not equal to the number "
		"of rows second matrix");
  }
  S21Matrix tmp(rows_, other.cols_);// create temp matrix
  for (int i = 0; i < rows_; ++i) {
	for (int j = 0; j < other.cols_; ++j) {
	  for (int x = 0; x < cols_; ++x) {
		tmp(i, j) += (*this)(i, x) * other(x, j);
	  }
	}
  }
  // delete[] matrix_;
  // matrix_ = new double[rows_ * other.cols_];
  // cols_ = other.cols_;
  // std::memcpy(matrix_, other.matrix_, rows_ * other.cols_ * sizeof(double));
  *this = tmp;
  // *this = std::move(tmp);
}

s21::S21Matrix s21::S21Matrix::Transpose() {
  S21Matrix temp(cols_, rows_);
  for (auto i = 0; i < rows_; i++) {
	for (auto j = 0; j < cols_; j++) {
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
	for (int i = 0; i < rows_; i++) {
	  for (int j = 0; j < cols_; j++) {
		S21Matrix temp(rows_ - 1, cols_ - 1);
		GetMiniMatr(i, j, &temp);
		result(i, j) = temp.Determinant();
		sign = pow(-1, i + j);
		result(i, j) = sign * result(i, j);
	  }
	}
  }
  return result;
}

double s21::S21Matrix::Determinant() {
  if (rows_ != cols_) {
	throw std::out_of_range("Invalid input, the matrix is not square");
  }
  int check = 0, sign = 1;
  double quotient = 0, result = 1;
  if (rows_ == 1) {
	result = (*this)(0, 0);// determinant for matrix 1x1
  } else if (rows_ == 2) {
	result = (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);// determinant for matrix 2x2
  } else {
	S21Matrix temp(*this);
	for (int i = 0; i < temp.rows_; i++) {
	  if (temp(i, i) == 0) {
		check = SwapStr(&temp, i, i, &temp);
		sign = -sign;
	  }
	  if (!check) {
		for (int j = i + 1; j < temp.rows_; j++) {
		  quotient = temp(j, i) / temp(i, i);
		  for (int x = i; x < temp.cols_; x++) {
			temp(j, x) = temp(j, x) - quotient * temp(i, x);
		  }
		}
		result *= temp(i, i);
	  } else {
		result = 0;
		break;
	  }
	}
	if (!check) result *= sign;
  }
  return result;
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

double &s21::S21Matrix::operator()(int rows, int cols) const {
  if (rows >= rows_ || cols >= cols_) {
	throw std::out_of_range("Incorrect input, index is outside the matrix");
  }
  return matrix_[rows * cols_ + cols];
}

/**
 * Support functions */
void s21::S21Matrix::CreateMartix() {
  matrix_ = new double[rows_ * cols_];
}

void s21::S21Matrix::RemoveMatrix() {
  if (matrix_) {
	rows_ = 0;
	cols_ = 0;
	delete[] matrix_;
  }
}

int s21::S21Matrix::SwapStr(S21Matrix *A, int x, int y, S21Matrix *result) {
  int error = 0;
  int i = 0;
  *result = *A;//   внимание
  for (i = x; i < A->rows_; i++) {
	if ((*A)(i, y) != 0) {
	  error = 0;
	  break;
	} else {
	  error = 1;
	}
  }
  if (!error) {
	double tmp = 0;
	for (int j = 0; j < A->cols_; j++) {
	  tmp = (*A)(x, j);
	  (*A)(x, j) = (*A)(i, j);
	  (*A)(i, j) = tmp;
	}
  }
  return error;
}

void s21::S21Matrix::GetMiniMatr(int x, int y, S21Matrix *result) {
  int di = 0, dj;
  for (int i = 0; i < (rows_ - 1); i++) {
	if (i == x) di = 1;
	dj = 0;
	for (int j = 0; j < (rows_ - 1); j++) {
	  if (j == y) dj = 1;
	  (*result)(i, j) = (*this)((i + di), (j + dj));
	}
  }
}

void s21::S21Matrix::print() {
  //  std::cout << rows_ << std::endl;
  //  std::cout << cols_ << std::endl;
  for (auto i = 0; i < rows_; ++i) {
	for (auto j = 0; j < cols_; ++j) {
	  std::cout << matrix_[i * cols_ + j] << ' ';
	}
	std::cout << std::endl;
  }
}

void s21::S21Matrix::init(double start) {
  //  for (auto i = 0; i < rows_ * cols_; ++i) {
  //	matrix_[i] = start++;
  //  }
  matrix_[0] = 1;
  matrix_[1] = 2;
  matrix_[2] = 3;
  matrix_[3] = 0;
  matrix_[4] = 4;
  matrix_[5] = 2;
  matrix_[6] = 5;
  matrix_[7] = 2;
  matrix_[8] = 1;
}

int main() {
  std::cout << "_______FIRST_matrix_______" << std::endl;
  s21::S21Matrix mtr(3, 3);
  mtr.init(5);
  mtr.print();
  //  double result = mtr.Determinant();
  //  std::cout << "Determinant = " << result << std::endl;

  //   std::cout << "_______SECOND_matrix______" << std::endl;
  s21::S21Matrix mtr1;
  mtr1 = mtr.CalcComplements();
  //  mtr1.init(1);
  //    mtr1.print();
  //  mtr.MulMatrix(mtr1);
  std::cout << "_______RESULT_matrix______" << std::endl;
  mtr1.print();

  //  std::cout << ((mtr1.EqMatrix(mtr) == true) ? "matrix equal" : "matrix
  //  isn't equal") << std::endl;

  return 0;
}
