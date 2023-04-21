#include "s21_matrix_oop.h"
#include <cmath>
#include <iostream>

S21Matrix::S21Matrix() {
  rows_ = 3;
  cols_ = 3;
  matrix_ = new double[rows_ * cols_]();
}

S21Matrix::S21Matrix(const int k, const int j) {
  rows_ = k;
  cols_ = j;
  if (rows_ <= 0 || cols_ <= 0) {

    throw std::out_of_range(
        "Incorrect index , rows_ <= 0 || cols_ <= 0 in constructor");
  }
  matrix_ = new double[rows_ * cols_]();
}

S21Matrix::~S21Matrix() {
  if (matrix_) {
    delete[] matrix_;
  }
  matrix_ = nullptr;
}

int S21Matrix ::Get_Rows() const { return rows_; }

int S21Matrix ::Get_Cols() const { return cols_; }

void S21Matrix ::Set_Rows(const int rows) {
  if (rows < 1)
    throw std::logic_error("Error, index is out of range");
  if (rows_ != rows) {
    S21Matrix tmp_matrix(rows, cols_);
    for (int i = 0; i < rows_ && i < tmp_matrix.rows_; i++) {
      for (int j = 0; j < cols_ && j < tmp_matrix.cols_; j++) {
        tmp_matrix(i, j) = (*this)(i, j);
      }
    }
    *this = std::move(tmp_matrix);
  }
}

void S21Matrix ::Set_Cols(const int cols) {
  if (cols < 1)
    throw std::logic_error("Error, index is out of range");
  if (cols_ != cols) {
    S21Matrix tmp_matrix(rows_, cols);
    for (int i = 0; i < rows_ && i < tmp_matrix.rows_; i++) {
      for (int j = 0; j < cols_ && j < tmp_matrix.cols_; j++) {
        tmp_matrix(i, j) = (*this)(i, j);
      }
    }
    *this = std::move(tmp_matrix);
  }
}

bool S21Matrix::operator==(const S21Matrix &ref) { return EqMatrix(ref); }

bool S21Matrix::EqMatrix(const S21Matrix &ref) const {
  if (this->cols_ != ref.cols_ && this->rows_ != ref.rows_) {
    return false;
  } else {
    return std::equal(this->matrix_,
                      this->matrix_ + (this->rows_ * this->cols_ - 1),
                      ref.matrix_, [](const double a, const double b) {
                        return std::fabs(a - b) >= EPS ? false : true;
                      });
  }
}

S21Matrix::S21Matrix(const S21Matrix &ref) {
  matrix_ = new double[ref.cols_ * ref.rows_]();
  cols_ = ref.cols_;
  rows_ = ref.rows_;
  for (int k = 0; k < cols_ * rows_; k++) {
    matrix_[k] = ref.matrix_[k];
  }
}

S21Matrix &S21Matrix::operator=(const S21Matrix &ref) {
  if (this != &ref) {
    if (this->cols_ * this->rows_ != ref.cols_ * ref.rows_) {
      if (matrix_) {
        delete[] matrix_;
      }
      matrix_ = new double[ref.cols_ * ref.rows_]();
    }
    cols_ = ref.cols_;
    rows_ = ref.rows_;
    for (int k = 0; k < cols_ * rows_; k++) {
      matrix_[k] = ref.matrix_[k];
    }
  }
  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&ref) {
  if (this != &ref) {
    delete[] matrix_;
    this->cols_ = ref.cols_;
    this->rows_ = ref.rows_;
    this->matrix_ = std::exchange(ref.matrix_, nullptr);
  }
  return *this;
}

S21Matrix::S21Matrix(S21Matrix &&ref) {
  if (this != &ref) {
    this->cols_ = ref.cols_;
    this->rows_ = ref.rows_;
    this->matrix_ = std::exchange(ref.matrix_, nullptr);
  }
}

double &S21Matrix::operator()(const int row, const int col) {
  if (row >= rows_ || col >= cols_) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[row * cols_ + col];
}

double &S21Matrix::operator()(const int row, const int col) const {
  if (row >= rows_ || col >= cols_) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[row * cols_ + col];
}

S21Matrix S21Matrix::operator-(const S21Matrix &val) {
  S21Matrix res(*this);
  res.SubMatrix(val);
  return res;
}

void S21Matrix::SubMatrix(const S21Matrix &o) {
  if (rows_ != o.rows_ || cols_ != o.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size\n");
  }
  for (auto i = 0; i < rows_ * cols_; i++) {
    matrix_[i] = matrix_[i] - o.matrix_[i];
  }
}

S21Matrix S21Matrix::operator+(const S21Matrix &val) {
  S21Matrix res(val);
  res.SumMatrix(*this);
  return res;
}

void S21Matrix::SumMatrix(const S21Matrix &o) {
  if (rows_ != o.rows_ || cols_ != o.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  for (auto i = 0; i < rows_ * cols_; i++) {
    matrix_[i] = matrix_[i] + o.matrix_[i];
  }
}

S21Matrix S21Matrix::operator*(const S21Matrix &val) {
  S21Matrix res(*this);
  res.MulMatrix(val);
  return res;
}

void S21Matrix::MulMatrix(const S21Matrix &val) {
  if (this->rows_ <= 0 || this->cols_ <= 0 || val.rows_ <= 0 ||
      val.cols_ <= 0 || this->cols_ != val.rows_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  S21Matrix buf(this->rows_, val.cols_);
  // S21Matrix buf2(val); // cant use const matrix for operator ()
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < val.cols_; j++) {
      for (int k = 0; k < this->cols_; k++) {
        buf(i, j) += (*this)(i, k) * val(k, j);
      }
    }
  }
  *this = buf;
}

void S21Matrix::MulNumber(const double val) {
  for (auto i = 0; i < rows_ * cols_; i++) {
    matrix_[i] = matrix_[i] * val;
  }
}

S21Matrix operator*(const double num, const S21Matrix val) {
  S21Matrix res(val);
  return res * num;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix res(*this);
  res.MulNumber(num);
  return res;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix val) {
  this->MulMatrix(val);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const double val) {
  this->MulNumber(val);
  return *this;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix val) {
  this->SumMatrix(val);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix val) {
  this->SubMatrix(val);
  return *this;
}

void S21Matrix::print_matrix() {
  for (int k = 0, buf = 0; k < rows_ * cols_; k++) {
    std::cout << matrix_[k] << " ";
    buf++;
    if (buf == cols_) {
      buf = 0;
      std::cout << "\n";
    }
  }
  std::cout << "\n";
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);
  for (int k = 0; k < rows_; k++) {
    for (int j = 0; j < cols_; j++) {
      result(j, k) = (*this)(k, j);
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  S21Matrix result(this->rows_, this->cols_);
  int sign = 0;
  if (this->rows_ <= 0 || this->cols_ <= 0 || this->rows_ != this->cols_) {
    throw std::logic_error("Error, incorect matrix, not square");
  }
  if (this->rows_ == 1 && this->cols_ == 1) {
    S21Matrix small(1, 1);
    small(0, 0) = (*this)(0, 0);
    return small;
  } else {
    S21Matrix minor(this->rows_ - 1, this->cols_ - 1);
    for (int k = 0; k < this->rows_; k++) {
      for (int m = 0; m < this->cols_; m++) {
        this->CalcMinor(k, m, minor);
        sign = ((k + m) % 2 == 0) ? 1 : -1;
        result(k, m) = minor.Determinant() * sign;
      }
    }
  }

  return result;
}

void S21Matrix::CalcMinor(const int row, const int col, S21Matrix &result) {
  if (result.rows_ != this->rows_ - 1 || result.cols_ != this->cols_ - 1)
    throw std::logic_error("Error, wrong minor matrix size");
  for (int i = 0, i2 = 0; i < this->rows_; i++) {
    if (i != row) {
      for (int j = 0, j2 = 0; j < this->cols_; j++) {
        if (j != col) {
          result(i2, j2) = (*this)(i, j);
          j2++;
        }
      }
      i2++;
    }
  }
}

double S21Matrix::Determinant() {
  double result = 0.;
  if (rows_ != cols_)
    throw std::logic_error("Error, rows  not equal columns");
  if (this->rows_ == 1 && this->cols_ == 1) {
    return (*this)(0, 0);
  } else if (this->rows_ == 2) {
    result = ((*this)(0, 0) * (*this)(1, 1)) - ((*this)(1, 0) * (*this)(0, 1));
  } else {
    S21Matrix buf(this->rows_ - 1, this->cols_ - 1);
    int sign = 1;
    for (int i = 0; i < this->rows_; i++) {
      this->CalcMinor(0, i, buf);
      result += sign * (*this)(0, i) * buf.Determinant();
      sign *= -1;
    }
  }

  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  S21Matrix result(*this);
  double determ = this->Determinant();
  if (fabs(determ) < 1e-7) {
    throw std::logic_error("determinant = 0, incorect matrix");
  } else {
    result = result.CalcComplements();
    result = result.Transpose();
    result.MulNumber(1 / determ);
  }
  return result;
}

void S21Matrix::Init_Matrix() {
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      (*this)(i, j) = i + j;
    }
  }
}