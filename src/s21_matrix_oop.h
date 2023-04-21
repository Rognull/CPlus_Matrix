#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <algorithm>
#include <cmath>
#include <exception>
#include <iostream>
#include <stdexcept>

constexpr double EPS = 1e-6;

class S21Matrix {

public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  ~S21Matrix();
  S21Matrix(const S21Matrix &ref);
  S21Matrix(S21Matrix &&ref);

  bool operator==(const S21Matrix &ref1);
  S21Matrix &operator=(const S21Matrix &ref);
  S21Matrix &operator=(S21Matrix &&ref);
  S21Matrix &operator*=(const S21Matrix val);
  S21Matrix &operator*=(const double val);
  S21Matrix operator*(const S21Matrix &val);
  friend S21Matrix operator*(const double num, const S21Matrix val);
  S21Matrix operator*(const double num);
  S21Matrix &operator+=(const S21Matrix val);
  S21Matrix operator+(const S21Matrix &val);
  S21Matrix &operator-=(const S21Matrix val);
  S21Matrix operator-(const S21Matrix &val);
  double &operator()(const int i,const int j);
  double &operator()(const int i,const int j) const;

  int Get_Rows() const;
  int Get_Cols() const;
  void Set_Rows(const int rows);
  void Set_Cols(const int cols);

  bool EqMatrix(const S21Matrix &other) const;
  S21Matrix Transpose();
  void SumMatrix(const S21Matrix &other);
  void MulMatrix(const S21Matrix &other);
  void MulNumber(const double other);
  void SubMatrix(const S21Matrix &other);
  S21Matrix CalcComplements();
  void CalcMinor(const int row, const int col, S21Matrix &result);
  double Determinant();
  S21Matrix InverseMatrix();
  void print_matrix(); // help func
  void Init_Matrix(); // help func

private:
  int rows_, cols_;
  double *matrix_;
};

#endif // SRC_S21_MATRIX_OOP_H_