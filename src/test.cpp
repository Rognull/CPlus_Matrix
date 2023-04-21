#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}

 

TEST(Constructor, Default) {
  auto test = S21Matrix();
  EXPECT_EQ(test.Get_Rows(), 3);
  EXPECT_EQ(test.Get_Cols(), 3);
}

TEST(Constructor, Args) {
  auto test = S21Matrix(2, 4);
  EXPECT_EQ(test.Get_Rows(), 2);
  EXPECT_EQ(test.Get_Cols(), 4);
}

TEST(Constructor, Copy) {
  auto test = S21Matrix(2, 4);
  test(0, 0) = 3;
  auto test2 = (test);
  EXPECT_EQ(test2.Get_Rows(), 2);
  EXPECT_EQ(test2.Get_Cols(), 4);
  EXPECT_EQ(test2(0, 0), 3);
}

TEST(Constructor, Move) {
  S21Matrix test(2, 4);
  test(0, 0) = 3;
  S21Matrix test2;
  test2 = (std::move(test));
  EXPECT_EQ(test2.Get_Rows(), 2);
  EXPECT_EQ(test2.Get_Cols(), 4);
  EXPECT_EQ(test2(0, 0), 3);
}

TEST(Setter, Rows) {
  auto test = S21Matrix(2, 2);
  test(0, 0) = 3;
  test(0, 1) = 1;
  test(1, 0) = 2;
  test(1, 1) = -2;
  EXPECT_EQ(test.Get_Rows(), 2);
  test.Set_Rows(3);
  EXPECT_EQ(test.Get_Rows(), 3);
  EXPECT_EQ(test(1, 1), -2);
  test.Set_Rows(1);
  test.Set_Cols(1);
  test.Set_Rows(2);
  test.Set_Cols(2);
  EXPECT_EQ(test(1, 1), 0);
}

TEST(Setter, Cols) {
  auto test = S21Matrix(2, 1);
  test(0, 0) = 3;
  test(1, 0) = 2;
  EXPECT_EQ(test.Get_Cols(), 1);
  test.Set_Cols(10);
  EXPECT_EQ(test.Get_Cols(), 10);
  EXPECT_EQ(test(1, 9), 0);
  EXPECT_EQ(test(0, 0), 3);
}

TEST(Arithmethic, EqMatrix) {
  auto test1 = S21Matrix();
  auto test2 = S21Matrix();
  test1.Init_Matrix();
  test2.Init_Matrix();
  EXPECT_EQ(test1.EqMatrix(test2), true);
  EXPECT_EQ(test2.EqMatrix(test1), true);
  EXPECT_EQ(test1 == test2, true);
  EXPECT_EQ(test2 == test1, true);
  test1(0, 0) = 10;
  EXPECT_EQ(test1.EqMatrix(test2), false);
  EXPECT_EQ(test2.EqMatrix(test1), false);
  EXPECT_EQ(test1 == test2, false);
  EXPECT_EQ(test2 == test1, false);
}

TEST(Arithmethic, SumMatrix) {
  auto test1 = S21Matrix(2, 2);
  auto test2 = S21Matrix(2, 2);
  test1.Init_Matrix();
  test2.Init_Matrix();
  test1 += test2;
  EXPECT_EQ(test1(0, 0), 0);
  EXPECT_EQ(test1(1, 0), 2);
  EXPECT_EQ(test1(0, 1), 2);
  EXPECT_EQ(test1(1, 1), 4);
}

TEST(Arithmethic, SubMatrix) {
  auto test1 = S21Matrix(2, 2);
  auto test2 = S21Matrix(2, 2);
  test1.Init_Matrix();
  test2.Init_Matrix();
  test1 *= 3;
  test1 -= test2;
  EXPECT_EQ(test1(0, 0), 0);
  EXPECT_EQ(test1(1, 0), 2);
  EXPECT_EQ(test1(0, 1), 2);
  EXPECT_EQ(test1(1, 1), 4);
}

TEST(Arithmethic, MulMatrix) {
  auto test1 = S21Matrix(2, 2);
  auto test2 = S21Matrix(2, 2);
  test1.Init_Matrix();
  test2.Init_Matrix();
  test1 *= test2;
  EXPECT_EQ(test1(0, 0), 1);
  EXPECT_EQ(test1(1, 0), 2);
  EXPECT_EQ(test1(0, 1), 2);
  EXPECT_EQ(test1(1, 1), 5);
}

TEST(Arithmethic, MulNum) {
 S21Matrix test(3, 6);
  test(0, 0) = 10;
  test(2, 2) = 3.5;
  test.MulNumber(2);
  EXPECT_DOUBLE_EQ(test(0, 0), 20);
  EXPECT_DOUBLE_EQ(test(2, 2), 7);
}

TEST(Actions, Transpose) {
  auto test1 = S21Matrix(2, 2);
  test1(0, 0) = 3;
  test1(0, 1) = 1;
  test1(1, 0) = 20;
  test1(1, 1) = -2;
  test1 = test1.Transpose();
  EXPECT_EQ(test1(0, 0), 3);
  EXPECT_EQ(test1(0, 1), 20);
  EXPECT_EQ(test1(1, 0), 1);
  EXPECT_EQ(test1(1, 1), -2);
}



TEST(Actions, Complements) {
  S21Matrix test(4, 4);
  test(0, 0) = 0;
  test(0, 1) = 1;
  test(0, 2) = 1;
  test(0, 3) = 1;
  test(1, 0) = 2;
  test(1, 1) = 2;
  test(1, 2) = 2;
  test(1, 3) = 2;
  test(2, 0) = 0;
  test(2, 1) = 0;
  test(2, 2) = 4;
  test(2, 3) = 20;
  test(3, 0) = 0;
  test(3, 1) = 0;
  test(3, 2) = 3;
  test(3, 3) = 5;
  S21Matrix tmp = test.CalcComplements();
  EXPECT_DOUBLE_EQ(tmp(1, 0), 40);
}

TEST(Actions, Determinant) {
  auto test1 = S21Matrix(2, 2);
  test1(0, 0) = 3;
  test1(0, 1) = 1;
  test1(1, 0) = 20;
  test1(1, 1) = -2;
  EXPECT_EQ(test1.Determinant(), -26);
  test1(0, 0) = 2;
  test1(0, 1) = 1;
  test1(1, 0) = 4;
  test1(1, 1) = -2;
  EXPECT_EQ(test1.Determinant(), -8);
  test1(0, 0) = 2;
  test1(0, 1) = -5;
  test1(1, 0) = 1;
  test1(1, 1) = -2;
  EXPECT_EQ(test1.Determinant(), 1);
  test1(0, 0) = 3;
  test1(0, 1) = -1;
  test1(1, 0) = 7;
  test1(1, 1) = -2;
  EXPECT_EQ(test1.Determinant(), 1);
}
TEST(test1, out_of_matrix) {
  S21Matrix test(2, 2);
  EXPECT_THROW(test(4, 4), std::logic_error);
}

 

 

 

TEST(test1, create_matrix_exception) {
  EXPECT_THROW(S21Matrix test(-3, 5), std::logic_error);
  EXPECT_THROW(S21Matrix test(3, -5), std::logic_error);
  EXPECT_THROW(S21Matrix test(-3, 0), std::logic_error);
}

 

 

TEST(test1, eq_matrix_ok) {
  S21Matrix test1(3, 5);
  S21Matrix test2(3, 5);
  EXPECT_TRUE(test1.EqMatrix(test2));
}

TEST(test1, eq_matrix_ok_2) {
  S21Matrix test1(3, 5);
  S21Matrix test2(3, 5);
  EXPECT_TRUE(test1 == test2);
}

TEST(test1, eq_matrix_fail) {
  S21Matrix test1(1, 5);
  S21Matrix test2(3, 4);
  EXPECT_FALSE(test1.EqMatrix(test2));
}

TEST(test1, eq_matrix_fail_2) {
  S21Matrix test1(1, 5);
  S21Matrix test2(1, 5);
  test1(0, 0) = 2;
  EXPECT_FALSE(test1.EqMatrix(test2));
}

TEST(test1, sum_matrix) {
  S21Matrix test1(3, 6);
  S21Matrix test2(3, 6);
  test1(0, 0) = 10;
  test1(2, 2) = 3;
  test2(0, 0) = -5.5;
  test2(2, 3) = -12.2;
  test1.SumMatrix(test2);
  EXPECT_DOUBLE_EQ(test1(0, 0), 4.5);
  EXPECT_DOUBLE_EQ(test1(2, 2), 3);
  EXPECT_DOUBLE_EQ(test1(2, 3), -12.2);
}

TEST(test1, sum_matrix_fail) {
  S21Matrix test1(3, 6);
  S21Matrix test2(3, 7);
  EXPECT_THROW(test1.SumMatrix(test2), std::logic_error);
}

TEST(test1, sub_matrix) {
  S21Matrix test1(3, 6);
  S21Matrix test2(3, 6);
  test1(0, 0) = 10;
  test1(2, 2) = 3;
  test2(0, 0) = -5.5;
  test2(2, 3) = -12.2;
  test1.SubMatrix(test2);
  EXPECT_DOUBLE_EQ(test1(0, 0), 15.5);
  EXPECT_DOUBLE_EQ(test1(2, 2), 3);
  EXPECT_DOUBLE_EQ(test1(2, 3), 12.2);
}

TEST(test1, sub_matrix_fail) {
  S21Matrix test1(3, 6);
  S21Matrix test2(3, 7);
  EXPECT_THROW(test1.SubMatrix(test2), std::logic_error);
}

TEST(test1, mul_number) {
  S21Matrix test(3, 6);
  test(0, 0) = 10;
  test(2, 2) = 3.5;
  test.MulNumber(2);
  EXPECT_DOUBLE_EQ(test(0, 0), 20);
  EXPECT_DOUBLE_EQ(test(2, 2), 7);
}

TEST(test1, mul_number_2) {
  S21Matrix test(3, 6);
  test(0, 0) = 10;
  test(2, 2) = 3.5;
  test *= 2;
  EXPECT_DOUBLE_EQ(test(0, 0), 20);
  EXPECT_DOUBLE_EQ(test(2, 2), 7);
}

TEST(test1, mul_number_3) {
  S21Matrix test(3, 6);
  test(0, 0) = 10;
  test(2, 2) = 3.5;
  S21Matrix tmp = test * 2;
  EXPECT_DOUBLE_EQ(tmp(0, 0), 20);
  EXPECT_DOUBLE_EQ(tmp(2, 2), 7);
}

TEST(test1, mul_matrix) {
  S21Matrix test1(2, 3);
  S21Matrix test2(3, 1);
  test1(0, 0) = 10;
  test1(0, 1) = 8;
  test1(0, 2) = 1.1;
  test1(1, 0) = 5;
  test1(1, 1) = -5;
  test1(1, 2) = -3;

  test2(0, 0) = 1;
  test2(1, 0) = 3;
  test2(2, 0) = 5;
  test1.MulMatrix(test2);

  EXPECT_EQ(test1(0, 0), 39.5);
  EXPECT_EQ(test1(1, 0), -25);
}

TEST(test1, mul_matrix_2) {
  S21Matrix test1(2, 3);
  S21Matrix test2(3, 1);
  test1(0, 0) = 10;
  test1(0, 1) = 8;
  test1(0, 2) = 1.1;
  test1(1, 0) = 5;
  test1(1, 1) = -5;
  test1(1, 2) = -3;

  test2(0, 0) = 1;
  test2(1, 0) = 3;
  test2(2, 0) = 5;
  test1 *= test2;

  EXPECT_EQ(test1(0, 0), 39.5);
  EXPECT_EQ(test1(1, 0), -25);
}

TEST(test1, nul_matrix_fail) {
  S21Matrix test1(2, 3);
  S21Matrix test2(5, 5);
  EXPECT_THROW(test1 * test2, std::logic_error);
}

TEST(test1, mul_matrix_3) {
  S21Matrix test1(2, 3);
  S21Matrix test2(3, 1);
  test1(0, 0) = 10;
  test1(0, 1) = 8;
  test1(0, 2) = 1.1;
  test1(1, 0) = 5;
  test1(1, 1) = -5;
  test1(1, 2) = -3;

  test2(0, 0) = 1;
  test2(1, 0) = 3;
  test2(2, 0) = 5;
  S21Matrix tmp = test1 * test2;

  EXPECT_EQ(tmp(0, 0), 39.5);
  EXPECT_EQ(tmp(1, 0), -25);
}


TEST(test1, mul_matrix_4) {
  S21Matrix test1(2, 2);
  S21Matrix test2(2, 2);
  test1(0, 0) = 10;
  test1(0, 1) = -10;
  test1(1, 0) = 5;
  test1(1, 1) = -5;

  test2 =   test1 * 2;
 

  EXPECT_EQ(test2(0, 0), 20);
  EXPECT_EQ(test2(0, 1), -20);
  EXPECT_EQ(test2(1, 0), 10);
  EXPECT_EQ(test2(1, 1), -10);

}


TEST(test1, boolean_test) {
  S21Matrix test1(2, 2);
  S21Matrix test2(2, 2);
  bool res  = test1==test2;

  EXPECT_EQ(res,true);

}

TEST(test1, mul_matrix_5) {
  S21Matrix test1(2, 2);
  S21Matrix test2(2, 2);
  test1(0, 0) = 10;
  test1(0, 1) = -10;
  test1(1, 0) = 5;
  test1(1, 1) = -5;

  test2 =  2 * test1;
 

  EXPECT_EQ(test2(0, 0), 20);
  EXPECT_EQ(test2(0, 1), -20);
  EXPECT_EQ(test2(1, 0), 10);
  EXPECT_EQ(test2(1, 1), -10);

}


TEST(test1, sum_matrix_op) {
  S21Matrix test1(3, 6);
  S21Matrix test2(3, 6);
  test1(0, 0) = 10;
  test1(2, 2) = 3;
  test2(0, 0) = -5.5;
  test2(2, 3) = -12.2;
  test1 = test1 + test2;
  EXPECT_DOUBLE_EQ(test1(0, 0), 4.5);
  EXPECT_DOUBLE_EQ(test1(2, 2), 3);
  EXPECT_DOUBLE_EQ(test1(2, 3), -12.2);
}

TEST(test1, sum_matrix_op_2) {
  S21Matrix test1(3, 6);
  S21Matrix test2(3, 6);
  test1(0, 0) = 10;
  test1(2, 2) = 3;
  test2(0, 0) = -5.5;
  test2(2, 3) = -12.2;
  test1 += test2;
  EXPECT_DOUBLE_EQ(test1(0, 0), 4.5);
  EXPECT_DOUBLE_EQ(test1(2, 2), 3);
  EXPECT_DOUBLE_EQ(test1(2, 3), -12.2);
}

TEST(test1, sub_matrix_op) {
  S21Matrix test1(3, 6);
  S21Matrix test2(3, 6);
  test1(0, 0) = 10;
  test1(2, 2) = 3;
  test2(0, 0) = -5.5;
  test2(2, 3) = -12.2;
  test1 = test1 - test2;
  EXPECT_DOUBLE_EQ(test1(0, 0), 15.5);
  EXPECT_DOUBLE_EQ(test1(2, 2), 3);
  EXPECT_DOUBLE_EQ(test1(2, 3), 12.2);
}

TEST(test1, sub_matrix_op_2) {
  S21Matrix test1(3, 6);
  S21Matrix test2(3, 6);
  test1(0, 0) = 10;
  test1(2, 2) = 3;
  test2(0, 0) = -5.5;
  test2(2, 3) = -12.2;
  test1 -= test2;
  EXPECT_DOUBLE_EQ(test1(0, 0), 15.5);
  EXPECT_DOUBLE_EQ(test1(2, 2), 3);
  EXPECT_DOUBLE_EQ(test1(2, 3), 12.2);
}

 

TEST(test1, determinant) {
  S21Matrix test(4, 4);
  test(0, 0) = 0;
  test(0, 1) = 1;
  test(0, 2) = 1;
  test(0, 3) = 1;
  test(1, 0) = 2;
  test(1, 1) = 2;
  test(1, 2) = 2;
  test(1, 3) = 2;
  test(2, 0) = 0;
  test(2, 1) = 0;
  test(2, 2) = 4;
  test(2, 3) = 20;
  test(3, 0) = 0;
  test(3, 1) = 0;
  test(3, 2) = 3;
  test(3, 3) = 5;
  EXPECT_DOUBLE_EQ(test.Determinant(), 80);
}

TEST(test1, det2) {
  S21Matrix test(2, 2);
  test(0, 0) = 6;
  test(0, 1) = 8;
  test(1, 0) = 7;
  test(1, 1) = 9;
  EXPECT_FLOAT_EQ(test.Determinant(), -2);
}

TEST(test1, calc_complements) {
  S21Matrix test(4, 4);
  test(0, 0) = 0;
  test(0, 1) = 1;
  test(0, 2) = 1;
  test(0, 3) = 1;
  test(1, 0) = 2;
  test(1, 1) = 2;
  test(1, 2) = 2;
  test(1, 3) = 2;
  test(2, 0) = 0;
  test(2, 1) = 0;
  test(2, 2) = 4;
  test(2, 3) = 20;
  test(3, 0) = 0;
  test(3, 1) = 0;
  test(3, 2) = 3;
  test(3, 3) = 5;
  S21Matrix tmp = test.CalcComplements();
  EXPECT_DOUBLE_EQ(tmp(1, 0), 40);
}
TEST(test1, calc_complements1) {
  S21Matrix test(1, 1);
  S21Matrix tmp = test.CalcComplements();
}


TEST(test1, inverse) {
  S21Matrix test(4, 4);
  test(0, 0) = 0;
  test(0, 1) = 1;
  test(0, 2) = 1;
  test(0, 3) = 1;
  test(1, 0) = 2;
  test(1, 1) = 2;
  test(1, 2) = 2;
  test(1, 3) = 2;
  test(2, 0) = 0;
  test(2, 1) = 0;
  test(2, 2) = 4;
  test(2, 3) = 20;
  test(3, 0) = 0;
  test(3, 1) = 0;
  test(3, 2) = 3;
  test(3, 3) = 5;
  S21Matrix tmp = test.InverseMatrix();
  EXPECT_DOUBLE_EQ(tmp(0, 1), 0.5);
}

TEST(test1, out_of_matrix1) {
  S21Matrix test(2, 2);
  EXPECT_THROW(test(4, 4), std::logic_error);
}

 
 

TEST(test1, determinant_dim) {
  S21Matrix test(4, 5);
  EXPECT_THROW(test.Determinant(), std::logic_error);
}

TEST(test1, calc_compl_dim) {
  S21Matrix test(4, 5);
  EXPECT_THROW(test.CalcComplements(), std::logic_error);
}

TEST(test1, inverse_dim) {
  S21Matrix test(4, 5);
  EXPECT_THROW(test.InverseMatrix(), std::logic_error);
}

TEST(test1, inverce_null) {
  S21Matrix test(2, 2);
  EXPECT_THROW(test.InverseMatrix(), std::logic_error);
}