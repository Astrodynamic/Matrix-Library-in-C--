#include <gtest/gtest.h>

#include "matrix.h"

TEST(create_matrix, test_1) {
  EXPECT_THROW({ Matrix mat_1(0, 0); }, e_error_matrix_t);
}

TEST(create_matrix, test_2) {
  Matrix mat_1(9, 4);
  ASSERT_EQ(mat_1.get_rows(), 9);
  ASSERT_EQ(mat_1.get_cols(), 4);

  EXPECT_THROW({ Matrix mat_2(-2, 4); }, e_error_matrix_t);
}

TEST(create_matrix, test_3) {
  Matrix mat_1(9, 4);
  Matrix mat_2(mat_1);
  ASSERT_TRUE(mat_1.eq_matrix(mat_2));
}

TEST(create_matrix, test_4) {
  Matrix mat_1(9, 4);
  Matrix mat_2(std::move(mat_1));
  ASSERT_FALSE(mat_1.eq_matrix(mat_2));
}

TEST(accessor, test_1) {
  Matrix mat_1(9, 4);
  ASSERT_EQ(mat_1.get_rows(), 9);
  ASSERT_EQ(mat_1.get_cols(), 4);
}

TEST(mutator, test_1) {
  Matrix mat_1(9, 4);
  mat_1.set_rows(6);
  mat_1.set_cols(6);
  ASSERT_EQ(mat_1.get_rows(), 6);
  ASSERT_EQ(mat_1.get_cols(), 6);
}

TEST(mutator, test_2) {
  Matrix mat_1(9, 4);
  mat_1.set_rows_cols(6, 6);
  ASSERT_EQ(mat_1.get_rows(), 6);
  ASSERT_EQ(mat_1.get_cols(), 6);
}

TEST(equal, test_1) {
  Matrix mat_1(9, 4);
  Matrix mat_2(5, 4);
  ASSERT_FALSE(mat_1.eq_matrix(mat_2));
  mat_1.set_rows(4);
  mat_2.set_rows(4);
  ASSERT_TRUE(mat_1.eq_matrix(mat_2));
  for (int i = 1; i <= 4; ++i) {
    for (int j = 1; j <= 4; ++j) {
      mat_1(i, j) = mat_2(i, j) = (double)(i + j) * 4.322 / M_PI;
    }
  }
  ASSERT_TRUE(mat_1.eq_matrix(mat_2));
}

TEST(equal, test_2) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  mat_1(1, 1) = 987654321.1234567;
  mat_1(1, 2) = 1111111111111.111111;
  mat_1(1, 3) = 2.0000005;
  mat_1(2, 1) = 3.0000001;
  mat_1(2, 2) = 4.1111111;
  mat_1(2, 3) = 5123454321.5123454;
  mat_1(3, 1) = 666666666666.0;
  mat_1(3, 2) = 7.0;
  mat_1(3, 3) = 987654321.9123456;

  mat_2(1, 1) = 987654321.1234567;
  mat_2(1, 2) = 1111111111111.111111;
  mat_2(1, 3) = 2.0000005;
  mat_2(2, 1) = 3.0000001;
  mat_2(2, 2) = 4.1111111;
  mat_2(2, 3) = 5123454321.5123454;
  mat_2(3, 1) = 666666666666.0;
  mat_2(3, 2) = 7.0;
  mat_2(3, 3) = 987654321.9123456;

  ASSERT_TRUE(mat_1.eq_matrix(mat_2));

  mat_1(2, 2) = 4.1;
  ASSERT_FALSE(mat_1.eq_matrix(mat_2));
}

TEST(sum, test_1) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  Matrix mat_3(3, 3);
  for (int i = 1; i <= 3; ++i) {
    for (int j = 1; j <= 3; ++j) {
      mat_1(i, j) = i * j * 1.34;
      mat_2(i, j) = i * j * 2.54;
      mat_3(i, j) = i * j * (1.34 + 2.54);
    }
  }
  mat_1.sum_matrix(mat_2);
  ASSERT_TRUE(mat_1.eq_matrix(mat_3));
}

TEST(sum, test_2) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  Matrix mat_3(3, 3);
  for (int i = 1; i <= 3; ++i) {
    for (int j = 1; j <= 3; ++j) {
      mat_1(i, j) = M_PI - i * j * 1.34;
      mat_2(i, j) = M_PI - i * j * 2.54;
      mat_3(i, j) = 2 * M_PI - i * j * (1.34 + 2.54);
    }
  }
  mat_1.sum_matrix(mat_2);
  ASSERT_TRUE(mat_1.eq_matrix(mat_3));
}

TEST(sum, test_3) {
  Matrix mat_1(3, 3);
  Matrix mat_2(5, 5);
  EXPECT_THROW({ mat_1.sum_matrix(mat_2); }, e_error_matrix_t);
}

TEST(sum, test_4) {
  Matrix mat_1(2, 2);
  Matrix mat_2(2, 2);
  Matrix mat_3(2, 2);
  mat_1(1, 1) = 2.987654;
  mat_1(1, 2) = -5.3456;
  mat_1(2, 1) = 6.23;
  mat_1(2, 2) = -3.9292;
  mat_2(1, 1) = 4.838;
  mat_2(1, 2) = 8.0987;
  mat_2(2, 1) = -8;
  mat_2(2, 2) = -0.921;
  mat_3(1, 1) = 7.825654;
  mat_3(1, 2) = 2.7531;
  mat_3(2, 1) = -1.77;
  mat_3(2, 2) = -4.8502;
  mat_1.sum_matrix(mat_2);
  ASSERT_TRUE(mat_1.eq_matrix(mat_3));
}

TEST(sub, test_1) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  Matrix mat_3(3, 3);
  for (int i = 1; i <= 3; ++i) {
    for (int j = 1; j <= 3; ++j) {
      mat_1(i, j) = i * j * 1.34;
      mat_2(i, j) = i * j * 2.54;
      mat_3(i, j) = i * j * (1.34 - 2.54);
    }
  }
  mat_1.sub_matrix(mat_2);
  ASSERT_TRUE(mat_1.eq_matrix(mat_3));
}

TEST(sub, test_2) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  Matrix mat_3(3, 3);
  for (int i = 1; i <= 3; ++i) {
    for (int j = 1; j <= 3; ++j) {
      mat_1(i, j) = M_PI - i * j * 1.34;
      mat_2(i, j) = M_PI - i * j * 2.54;
      mat_3(i, j) = -i * j * (1.34 - 2.54);
    }
  }
  mat_1.sub_matrix(mat_2);
  ASSERT_TRUE(mat_1.eq_matrix(mat_3));
}

TEST(sub, test_3) {
  Matrix mat_1(3, 3);
  Matrix mat_2(5, 5);
  EXPECT_THROW({ mat_1.sub_matrix(mat_2); }, e_error_matrix_t);
}

TEST(sub, test_4) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  Matrix mat_3(3, 3);
  mat_1(1, 1) = 0.1;
  mat_1(1, 2) = 0.2;
  mat_1(1, 3) = 0.3;
  mat_1(2, 1) = 0.4;
  mat_1(2, 2) = 0.5;
  mat_1(2, 3) = 0.6;
  mat_1(3, 1) = 0.7;
  mat_1(3, 2) = 0.8;
  mat_1(3, 3) = 0.9;
  mat_2(1, 1) = 1.0;
  mat_2(1, 2) = 2.0;
  mat_2(1, 3) = 3.0;
  mat_2(2, 1) = 4.0;
  mat_2(2, 2) = 5.0;
  mat_2(2, 3) = 6.0;
  mat_2(3, 1) = 7.0;
  mat_2(3, 2) = 8.0;
  mat_2(3, 3) = 9.0;
  mat_3(1, 1) = -0.9;
  mat_3(1, 2) = -1.8;
  mat_3(1, 3) = -2.7;
  mat_3(2, 1) = -3.6;
  mat_3(2, 2) = -4.5;
  mat_3(2, 3) = -5.4;
  mat_3(3, 1) = -6.3;
  mat_3(3, 2) = -7.2;
  mat_3(3, 3) = -8.1;
  mat_1.sub_matrix(mat_2);
  ASSERT_TRUE(mat_1.eq_matrix(mat_3));
}

TEST(mul_number, test_1) {
  Matrix mat_1(3, 9);
  Matrix mat_2(3, 9);
  for (int i = 1; i <= 3; ++i) {
    for (int j = 1; j <= 9; ++j) {
      mat_1(i, j) = 53.32423;
      mat_2(i, j) = 53.32423 * 1.2342;
    }
  }
  mat_1.mul_number(1.2342);
  ASSERT_TRUE(mat_1.eq_matrix(mat_2));
}

TEST(mul_number, test_2) {
  Matrix mat_1(3, 9);
  Matrix mat_2(3, 9);
  for (int i = 1; i <= 3; ++i) {
    for (int j = 1; j <= 9; ++j) {
      mat_1(i, j) = 53.32423;
      mat_2(i, j) = -53.32423 * 1.13;
    }
  }
  mat_1.mul_number(-1.13);
  ASSERT_TRUE(mat_1.eq_matrix(mat_2));
}

TEST(mul_matrix, test_1) {
  Matrix mat_1(3, 9);
  Matrix mat_2(3, 9);
  EXPECT_THROW({ mat_1.mul_matrix(mat_2); }, e_error_matrix_t);
}

TEST(mul_matrix, test_2) {
  Matrix mat_1(5, 4);
  Matrix mat_2(4, 4);
  Matrix mat_3(5, 4);
  mat_1(1, 1) = 2;
  mat_1(1, 2) = 5;
  mat_1(1, 3) = 7;
  mat_1(1, 4) = -4;
  mat_1(2, 1) = 6;
  mat_1(2, 2) = 3;
  mat_1(2, 3) = 4;
  mat_1(2, 4) = 14;
  mat_1(3, 1) = 5;
  mat_1(3, 2) = -2;
  mat_1(3, 3) = -3;
  mat_1(3, 4) = -1;
  mat_1(4, 1) = 10;
  mat_1(4, 2) = 3;
  mat_1(4, 3) = 9;
  mat_1(4, 4) = -3;
  mat_1(5, 1) = -3;
  mat_1(5, 2) = 3;
  mat_1(5, 3) = 1;
  mat_1(5, 4) = 5;
  mat_2(1, 1) = 8;
  mat_2(1, 2) = 8;
  mat_2(1, 3) = 3;
  mat_2(1, 4) = 5;
  mat_2(2, 1) = -7;
  mat_2(2, 2) = 7;
  mat_2(2, 3) = 1;
  mat_2(2, 4) = 1;
  mat_2(3, 1) = 7;
  mat_2(3, 2) = 3;
  mat_2(3, 3) = 4;
  mat_2(3, 4) = -4;
  mat_2(4, 1) = 10;
  mat_2(4, 2) = 3;
  mat_2(4, 3) = 9;
  mat_2(4, 4) = -3;
  mat_3(1, 1) = -10;
  mat_3(1, 2) = 60;
  mat_3(1, 3) = 3;
  mat_3(1, 4) = -1;
  mat_3(2, 1) = 195;
  mat_3(2, 2) = 123;
  mat_3(2, 3) = 163;
  mat_3(2, 4) = -25;
  mat_3(3, 1) = 23;
  mat_3(3, 2) = 14;
  mat_3(3, 3) = -8;
  mat_3(3, 4) = 38;
  mat_3(4, 1) = 92;
  mat_3(4, 2) = 119;
  mat_3(4, 3) = 42;
  mat_3(4, 4) = 26;
  mat_3(5, 1) = 12;
  mat_3(5, 2) = 15;
  mat_3(5, 3) = 43;
  mat_3(5, 4) = -31;
  mat_1.mul_matrix(mat_2);
  ASSERT_TRUE(mat_1.eq_matrix(mat_3));
}

TEST(mul_matrix, test_3) {
  Matrix mat_1(5, 4);
  Matrix mat_2(4, 4);
  Matrix mat_3(5, 4);
  mat_1(1, 1) = 2.987654;
  mat_1(1, 2) = -5.3456;
  mat_1(2, 1) = 6.23;
  mat_1(2, 2) = -3.9292;
  mat_2(1, 1) = 4.838;
  mat_2(1, 2) = 8.0987;
  mat_2(1, 3) = 8.09;
  mat_2(1, 4) = -987;
  mat_2(2, 1) = -8;
  mat_2(2, 2) = -0.921;
  mat_2(2, 3) = -0.91;
  mat_2(2, 4) = 21;
  mat_3(1, 1) = 57.219070052;
  mat_3(1, 2) = 29.1194110498;
  mat_3(1, 3) = 29.03461686;
  mat_3(1, 4) = -3061.072098;
  mat_3(2, 1) = 61.57434;
  mat_3(2, 2) = 54.0736942;
  mat_3(2, 3) = 53.976272;
  mat_3(2, 4) = -6231.5232;
  mat_1.mul_matrix(mat_2);
  ASSERT_TRUE(mat_1.eq_matrix(mat_3));
}

TEST(mul_matrix, test_4) {
  Matrix mat_1(5, 4);
  Matrix mat_2(4, 4);
  Matrix mat_3(5, 4);
  for (int i = 1; i <= 4; ++i) {
    for (int j = 1; j <= 4; ++j) {
      mat_2(i, j) = i + j;
    }
  }
  mat_1.mul_matrix(mat_2);
  ASSERT_TRUE(mat_1.eq_matrix(mat_3));
}

TEST(mul_matrix, test_5) {
  Matrix mat_1(5, 4);
  Matrix mat_2(4, 4);
  Matrix mat_3(5, 4);
  mat_1(1, 1) = 0;
  mat_1(1, 2) = 9;
  mat_1(1, 3) = 1;
  mat_1(2, 1) = 1;
  mat_1(2, 2) = 3;
  mat_1(2, 3) = 7;
  mat_1(3, 1) = 2;
  mat_1(3, 2) = 7;
  mat_1(3, 3) = 0;
  mat_2(1, 1) = 0;
  mat_2(1, 2) = 9;
  mat_2(1, 3) = 8;
  mat_2(2, 1) = 0;
  mat_2(2, 2) = 9;
  mat_2(2, 3) = 9;
  mat_2(3, 1) = 1;
  mat_2(3, 2) = 9;
  mat_2(3, 3) = 6;
  mat_3(1, 1) = 1;
  mat_3(1, 2) = 90;
  mat_3(1, 3) = 87;
  mat_3(2, 1) = 7;
  mat_3(2, 2) = 99;
  mat_3(2, 3) = 77;
  mat_3(3, 1) = 0;
  mat_3(3, 2) = 81;
  mat_3(3, 3) = 79;
  mat_1.mul_matrix(mat_2);
  ASSERT_TRUE(mat_1.eq_matrix(mat_3));
}

TEST(transpose, test_1) {
  Matrix mat_1(5, 4);
  Matrix mat_2(mat_1.transpose());
  Matrix mat_3(4, 5);
  ASSERT_TRUE(mat_2.eq_matrix(mat_3));
}

TEST(transpose, test_2) {
  Matrix mat_1(1, 4);
  mat_1(1, 1) = 5.0;
  mat_1(1, 2) = 3.5;
  mat_1(1, 3) = 9.1;
  mat_1(1, 4) = 1.9;
  Matrix mat_2(mat_1.transpose());
  Matrix mat_3(4, 1);
  mat_3(1, 1) = 5.0;
  mat_3(2, 1) = 3.5;
  mat_3(3, 1) = 9.1;
  mat_3(4, 1) = 1.9;
  ASSERT_TRUE(mat_2.eq_matrix(mat_3));
}

TEST(determinant, test_1) {
  Matrix mat_1(3, 3);
  mat_1(1, 1) = 1;
  mat_1(1, 2) = 2;
  mat_1(1, 3) = 3;
  mat_1(2, 1) = 5;
  mat_1(2, 2) = 3;
  mat_1(2, 3) = 2;
  mat_1(3, 1) = -5;
  mat_1(3, 2) = 3;
  mat_1(3, 3) = 3;
  ASSERT_NEAR(mat_1.determinant(), 43, 1e-7);
}

TEST(determinant, test_2) {
  Matrix mat_1(1, 1);
  mat_1(1, 1) = 1.5;
  ASSERT_NEAR(mat_1.determinant(), 1.5, 1e-7);
}

TEST(determinant, test_3) {
  Matrix mat_1(2, 2);
  mat_1(1, 1) = 55.5;
  mat_1(1, 2) = 14.4;
  mat_1(2, 1) = -0.752;
  mat_1(2, 2) = 156.2;
  ASSERT_NEAR(mat_1.determinant(), 8679.9288, 1e-7);
}

TEST(determinant, test_4) {
  Matrix mat_1(4, 4);
  mat_1(1, 1) = 11.1;
  mat_1(1, 2) = 2.2;
  mat_1(1, 3) = 3.3;
  mat_1(1, 4) = 4.4;
  mat_1(2, 1) = 8.8;
  mat_1(2, 2) = -9.9;
  mat_1(2, 3) = 10.1;
  mat_1(2, 4) = 11.11;
  mat_1(3, 1) = 15.15;
  mat_1(3, 2) = 16.16;
  mat_1(3, 3) = 17.17;
  mat_1(3, 4) = 18.18;
  mat_1(4, 1) = -22.22;
  mat_1(4, 2) = 23.23;
  mat_1(4, 3) = 24.24;
  mat_1(4, 4) = 25.25;
  ASSERT_NEAR(mat_1.determinant(), -11770.2443124, 1e-7);
}

TEST(determinant, test_5) {
  Matrix mat_1(4, 4);
  ASSERT_NEAR(mat_1.determinant(), 0.0, 1e-7);
}

TEST(determinant, test_6) {
  Matrix mat_1(5, 4);
  EXPECT_THROW({ mat_1.determinant(); }, e_error_matrix_t);
}

TEST(complements, test_1) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  mat_1(1, 1) = 1;
  mat_1(1, 2) = 2;
  mat_1(1, 3) = 3;
  mat_1(2, 1) = 0;
  mat_1(2, 2) = 4;
  mat_1(2, 3) = 2;
  mat_1(3, 1) = 5;
  mat_1(3, 2) = 2;
  mat_1(3, 3) = 1;
  mat_2(1, 1) = 0;
  mat_2(1, 2) = 10;
  mat_2(1, 3) = -20;
  mat_2(2, 1) = 4;
  mat_2(2, 2) = -14;
  mat_2(2, 3) = 8;
  mat_2(3, 1) = -8;
  mat_2(3, 2) = -2;
  mat_2(3, 3) = 4;
  Matrix mat_3(std::move(mat_1.calc_complements()));
  ASSERT_TRUE(mat_3.eq_matrix(mat_2));
}

TEST(complements, test_2) {
  Matrix mat_1(2, 2);
  Matrix mat_2(2, 2);
  mat_1(1, 1) = 2;
  mat_1(1, 2) = 4;
  mat_1(2, 1) = 6;
  mat_1(2, 2) = 3;
  mat_2(1, 1) = 3;
  mat_2(1, 2) = -6;
  mat_2(2, 1) = -4;
  mat_2(2, 2) = 2;
  Matrix mat_3(std::move(mat_1.calc_complements()));
  ASSERT_TRUE(mat_3.eq_matrix(mat_2));
}

TEST(complements, test_3) {
  Matrix mat_1(2, 3);
  EXPECT_THROW({ mat_1.calc_complements(); }, e_error_matrix_t);
}

TEST(inverse_matrix, test_1) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  mat_1(1, 1) = 2;
  mat_1(1, 2) = 5;
  mat_1(1, 3) = 7;
  mat_1(2, 1) = 6;
  mat_1(2, 2) = 3;
  mat_1(2, 3) = 4;
  mat_1(3, 1) = 5;
  mat_1(3, 2) = -2;
  mat_1(3, 3) = -3;
  mat_2(1, 1) = 1;
  mat_2(1, 2) = -1;
  mat_2(1, 3) = 1;
  mat_2(2, 1) = -38;
  mat_2(2, 2) = 41;
  mat_2(2, 3) = -34;
  mat_2(3, 1) = 27;
  mat_2(3, 2) = -29;
  mat_2(3, 3) = 24;
  Matrix mat_3(mat_1.inverse_matrix());
  ASSERT_TRUE(mat_3.eq_matrix(mat_2));
}

TEST(inverse_matrix, test_2) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  mat_1(1, 1) = 2;
  mat_1(1, 2) = 1.3;
  mat_1(1, 3) = 0.7;
  mat_1(2, 1) = -1;
  mat_1(2, 2) = 0;
  mat_1(2, 3) = 3;
  mat_1(3, 1) = 0.3;
  mat_1(3, 2) = -0.3;
  mat_1(3, 3) = 2;
  mat_2(1, 1) = 45.0 / 289.0;
  mat_2(1, 2) = -281.0 / 578.0;
  mat_2(1, 3) = 195.0 / 289.0;
  mat_2(2, 1) = 145.0 / 289.0;
  mat_2(2, 2) = 379.0 / 578.0;
  mat_2(2, 3) = -335.0 / 289.0;
  mat_2(3, 1) = 15.0 / 289.0;
  mat_2(3, 2) = 99.0 / 578.0;
  mat_2(3, 3) = 65.0 / 289.0;
  Matrix mat_3(mat_1.inverse_matrix());
  ASSERT_TRUE(mat_3.eq_matrix(mat_2));
}

TEST(inverse_matrix, test_3) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  mat_1(1, 1) = 2.8;
  mat_1(1, 2) = 1.3;
  mat_1(1, 3) = 7.01;
  mat_1(2, 1) = -1.03;
  mat_1(2, 2) = -2.3;
  mat_1(2, 3) = 3.01;
  mat_1(3, 1) = 0;
  mat_1(3, 2) = -3;
  mat_1(3, 3) = 2;
  mat_2(1, 1) = 44300.0 / 367429.0;
  mat_2(1, 2) = -236300.0 / 367429.0;
  mat_2(1, 3) = 200360.0 / 367429.0;
  mat_2(2, 1) = 20600.0 / 367429.0;
  mat_2(2, 2) = 56000.0 / 367429.0;
  mat_2(2, 3) = -156483.0 / 367429.0;
  mat_2(3, 1) = 30900.0 / 367429.0;
  mat_2(3, 2) = 84000.0 / 367429.0;
  mat_2(3, 3) = -51010.0 / 367429.0;
  Matrix mat_3(mat_1.inverse_matrix());
  ASSERT_TRUE(mat_3.eq_matrix(mat_2));
}

TEST(inverse_matrix, test_4) {
  Matrix mat_1(1, 1);
  Matrix mat_2(1, 1);
  mat_1(1, 1) = 777.0;
  mat_2(1, 1) = 1.0 / 777.0;
  Matrix mat_3(mat_1.inverse_matrix());
  ASSERT_TRUE(mat_3.eq_matrix(mat_2));
}

TEST(inverse_matrix, test_5) {
  Matrix mat_1(3, 3);
  EXPECT_THROW({ mat_1.inverse_matrix(); }, e_error_matrix_t);
}

TEST(operator_sum, test_1) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  Matrix mat_3(3, 3);
  for (int i = 1; i <= 3; ++i) {
    for (int j = 1; j <= 3; ++j) {
      mat_1(i, j) = i * j * 1.34;
      mat_2(i, j) = i * j * 2.54;
      mat_3(i, j) = i * j * (1.34 + 2.54);
    }
  }
  Matrix mat_4 = mat_1 + mat_2;
  ASSERT_TRUE(mat_4.eq_matrix(mat_3));
}

TEST(operator_sum, test_2) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  Matrix mat_3(3, 3);
  for (int i = 1; i <= 3; ++i) {
    for (int j = 1; j <= 3; ++j) {
      mat_1(i, j) = M_PI - i * j * 1.34;
      mat_2(i, j) = M_PI - i * j * 2.54;
      mat_3(i, j) = 2 * M_PI - i * j * (1.34 + 2.54);
    }
  }
  Matrix mat_4 = mat_1 + mat_2;
  ASSERT_TRUE(mat_4.eq_matrix(mat_3));
}

TEST(operator_sum, test_3) {
  Matrix mat_1(3, 3);
  Matrix mat_2(5, 5);
  EXPECT_THROW({ mat_1 + mat_2; }, e_error_matrix_t);
}

TEST(operator_sum, test_4) {
  Matrix mat_1(2, 2);
  Matrix mat_2(2, 2);
  Matrix mat_3(2, 2);
  mat_1(1, 1) = 2.987654;
  mat_1(1, 2) = -5.3456;
  mat_1(2, 1) = 6.23;
  mat_1(2, 2) = -3.9292;
  mat_2(1, 1) = 4.838;
  mat_2(1, 2) = 8.0987;
  mat_2(2, 1) = -8;
  mat_2(2, 2) = -0.921;
  mat_3(1, 1) = 7.825654;
  mat_3(1, 2) = 2.7531;
  mat_3(2, 1) = -1.77;
  mat_3(2, 2) = -4.8502;
  Matrix mat_4 = mat_1 + mat_2;
  ASSERT_TRUE(mat_4.eq_matrix(mat_3));
}

TEST(operator_sub, test_1) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  Matrix mat_3(3, 3);
  for (int i = 1; i <= 3; ++i) {
    for (int j = 1; j <= 3; ++j) {
      mat_1(i, j) = i * j * 1.34;
      mat_2(i, j) = i * j * 2.54;
      mat_3(i, j) = i * j * (1.34 - 2.54);
    }
  }
  Matrix mat_4 = mat_1 - mat_2;
  ASSERT_TRUE(mat_4.eq_matrix(mat_3));
}

TEST(operator_sub, test_2) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  Matrix mat_3(3, 3);
  for (int i = 1; i <= 3; ++i) {
    for (int j = 1; j <= 3; ++j) {
      mat_1(i, j) = M_PI - i * j * 1.34;
      mat_2(i, j) = M_PI - i * j * 2.54;
      mat_3(i, j) = -i * j * (1.34 - 2.54);
    }
  }
  Matrix mat_4 = mat_1 - mat_2;
  ASSERT_TRUE(mat_4.eq_matrix(mat_3));
}

TEST(operator_sub, test_3) {
  Matrix mat_1(3, 3);
  Matrix mat_2(5, 5);
  EXPECT_THROW({ mat_1 - mat_2; }, e_error_matrix_t);
}

TEST(operator_sub, test_4) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  Matrix mat_3(3, 3);
  mat_1(1, 1) = 0.1;
  mat_1(1, 2) = 0.2;
  mat_1(1, 3) = 0.3;
  mat_1(2, 1) = 0.4;
  mat_1(2, 2) = 0.5;
  mat_1(2, 3) = 0.6;
  mat_1(3, 1) = 0.7;
  mat_1(3, 2) = 0.8;
  mat_1(3, 3) = 0.9;
  mat_2(1, 1) = 1.0;
  mat_2(1, 2) = 2.0;
  mat_2(1, 3) = 3.0;
  mat_2(2, 1) = 4.0;
  mat_2(2, 2) = 5.0;
  mat_2(2, 3) = 6.0;
  mat_2(3, 1) = 7.0;
  mat_2(3, 2) = 8.0;
  mat_2(3, 3) = 9.0;
  mat_3(1, 1) = -0.9;
  mat_3(1, 2) = -1.8;
  mat_3(1, 3) = -2.7;
  mat_3(2, 1) = -3.6;
  mat_3(2, 2) = -4.5;
  mat_3(2, 3) = -5.4;
  mat_3(3, 1) = -6.3;
  mat_3(3, 2) = -7.2;
  mat_3(3, 3) = -8.1;
  Matrix mat_4 = mat_1 - mat_2;
  ASSERT_TRUE(mat_4.eq_matrix(mat_3));
}

TEST(operator_mul_number, test_1) {
  Matrix mat_1(3, 9);
  Matrix mat_2(3, 9);
  for (int i = 1; i <= 3; ++i) {
    for (int j = 1; j <= 9; ++j) {
      mat_1(i, j) = 53.32423;
      mat_2(i, j) = 53.32423 * 1.2342;
    }
  }
  Matrix mat_3 = mat_1 * 1.2342;
  ASSERT_TRUE(mat_3.eq_matrix(mat_2));
}

TEST(operator_mul_number, test_2) {
  Matrix mat_1(3, 9);
  Matrix mat_2(3, 9);
  for (int i = 1; i <= 3; ++i) {
    for (int j = 1; j <= 9; ++j) {
      mat_1(i, j) = 53.32423;
      mat_2(i, j) = -53.32423 * 1.13;
    }
  }
  Matrix mat_3 = mat_1 * -1.13;
  ASSERT_TRUE(mat_3.eq_matrix(mat_2));
}

TEST(operator_mul_matrix, test_1) {
  Matrix mat_1(3, 9);
  Matrix mat_2(3, 9);
  EXPECT_THROW({ mat_1 * mat_2; }, e_error_matrix_t);
}

TEST(operator_mul_matrix, test_2) {
  Matrix mat_1(5, 4);
  Matrix mat_2(4, 4);
  Matrix mat_3(5, 4);
  mat_1(1, 1) = 2;
  mat_1(1, 2) = 5;
  mat_1(1, 3) = 7;
  mat_1(1, 4) = -4;
  mat_1(2, 1) = 6;
  mat_1(2, 2) = 3;
  mat_1(2, 3) = 4;
  mat_1(2, 4) = 14;
  mat_1(3, 1) = 5;
  mat_1(3, 2) = -2;
  mat_1(3, 3) = -3;
  mat_1(3, 4) = -1;
  mat_1(4, 1) = 10;
  mat_1(4, 2) = 3;
  mat_1(4, 3) = 9;
  mat_1(4, 4) = -3;
  mat_1(5, 1) = -3;
  mat_1(5, 2) = 3;
  mat_1(5, 3) = 1;
  mat_1(5, 4) = 5;
  mat_2(1, 1) = 8;
  mat_2(1, 2) = 8;
  mat_2(1, 3) = 3;
  mat_2(1, 4) = 5;
  mat_2(2, 1) = -7;
  mat_2(2, 2) = 7;
  mat_2(2, 3) = 1;
  mat_2(2, 4) = 1;
  mat_2(3, 1) = 7;
  mat_2(3, 2) = 3;
  mat_2(3, 3) = 4;
  mat_2(3, 4) = -4;
  mat_2(4, 1) = 10;
  mat_2(4, 2) = 3;
  mat_2(4, 3) = 9;
  mat_2(4, 4) = -3;
  mat_3(1, 1) = -10;
  mat_3(1, 2) = 60;
  mat_3(1, 3) = 3;
  mat_3(1, 4) = -1;
  mat_3(2, 1) = 195;
  mat_3(2, 2) = 123;
  mat_3(2, 3) = 163;
  mat_3(2, 4) = -25;
  mat_3(3, 1) = 23;
  mat_3(3, 2) = 14;
  mat_3(3, 3) = -8;
  mat_3(3, 4) = 38;
  mat_3(4, 1) = 92;
  mat_3(4, 2) = 119;
  mat_3(4, 3) = 42;
  mat_3(4, 4) = 26;
  mat_3(5, 1) = 12;
  mat_3(5, 2) = 15;
  mat_3(5, 3) = 43;
  mat_3(5, 4) = -31;
  Matrix mat_4 = mat_1 * mat_2;
  ASSERT_TRUE(mat_4.eq_matrix(mat_3));
}

TEST(operator_mul_matrix, test_3) {
  Matrix mat_1(5, 4);
  Matrix mat_2(4, 4);
  Matrix mat_3(5, 4);
  mat_1(1, 1) = 2.987654;
  mat_1(1, 2) = -5.3456;
  mat_1(2, 1) = 6.23;
  mat_1(2, 2) = -3.9292;
  mat_2(1, 1) = 4.838;
  mat_2(1, 2) = 8.0987;
  mat_2(1, 3) = 8.09;
  mat_2(1, 4) = -987;
  mat_2(2, 1) = -8;
  mat_2(2, 2) = -0.921;
  mat_2(2, 3) = -0.91;
  mat_2(2, 4) = 21;
  mat_3(1, 1) = 57.219070052;
  mat_3(1, 2) = 29.1194110498;
  mat_3(1, 3) = 29.03461686;
  mat_3(1, 4) = -3061.072098;
  mat_3(2, 1) = 61.57434;
  mat_3(2, 2) = 54.0736942;
  mat_3(2, 3) = 53.976272;
  mat_3(2, 4) = -6231.5232;
  Matrix mat_4 = mat_1 * mat_2;
  ASSERT_TRUE(mat_4.eq_matrix(mat_3));
}

TEST(operator_mul_matrix, test_4) {
  Matrix mat_1(5, 4);
  Matrix mat_2(4, 4);
  Matrix mat_3(5, 4);
  for (int i = 1; i <= 4; ++i) {
    for (int j = 1; j <= 4; ++j) {
      mat_2(i, j) = i + j;
    }
  }
  Matrix mat_4 = mat_1 * mat_2;
  ASSERT_TRUE(mat_4.eq_matrix(mat_3));
}

TEST(operator_mul_matrix, test_5) {
  Matrix mat_1(5, 4);
  Matrix mat_2(4, 4);
  Matrix mat_3(5, 4);
  mat_1(1, 1) = 0;
  mat_1(1, 2) = 9;
  mat_1(1, 3) = 1;
  mat_1(2, 1) = 1;
  mat_1(2, 2) = 3;
  mat_1(2, 3) = 7;
  mat_1(3, 1) = 2;
  mat_1(3, 2) = 7;
  mat_1(3, 3) = 0;
  mat_2(1, 1) = 0;
  mat_2(1, 2) = 9;
  mat_2(1, 3) = 8;
  mat_2(2, 1) = 0;
  mat_2(2, 2) = 9;
  mat_2(2, 3) = 9;
  mat_2(3, 1) = 1;
  mat_2(3, 2) = 9;
  mat_2(3, 3) = 6;
  mat_3(1, 1) = 1;
  mat_3(1, 2) = 90;
  mat_3(1, 3) = 87;
  mat_3(2, 1) = 7;
  mat_3(2, 2) = 99;
  mat_3(2, 3) = 77;
  mat_3(3, 1) = 0;
  mat_3(3, 2) = 81;
  mat_3(3, 3) = 79;
  Matrix mat_4 = mat_1 * mat_2;
  ASSERT_TRUE(mat_4.eq_matrix(mat_3));
}

TEST(operator_equal, test_1) {
  Matrix mat_1(9, 4);
  Matrix mat_2(5, 4);
  ASSERT_FALSE(mat_1.eq_matrix(mat_2));
  mat_1.set_rows(4);
  mat_2.set_rows(4);
  ASSERT_TRUE(mat_1.eq_matrix(mat_2));
  for (int i = 1; i <= 4; ++i) {
    for (int j = 1; j <= 4; ++j) {
      mat_1(i, j) = mat_2(i, j) = (double)(i + j) * 4.322 / M_PI;
    }
  }
  ASSERT_TRUE(mat_1 == mat_2);
}

TEST(operator_equal, test_2) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  mat_1(1, 1) = 987654321.1234567;
  mat_1(1, 2) = 1111111111111.111111;
  mat_1(1, 3) = 2.0000005;
  mat_1(2, 1) = 3.0000001;
  mat_1(2, 2) = 4.1111111;
  mat_1(2, 3) = 5123454321.5123454;
  mat_1(3, 1) = 666666666666.0;
  mat_1(3, 2) = 7.0;
  mat_1(3, 3) = 987654321.9123456;

  mat_2(1, 1) = 987654321.1234567;
  mat_2(1, 2) = 1111111111111.111111;
  mat_2(1, 3) = 2.0000005;
  mat_2(2, 1) = 3.0000001;
  mat_2(2, 2) = 4.1111111;
  mat_2(2, 3) = 5123454321.5123454;
  mat_2(3, 1) = 666666666666.0;
  mat_2(3, 2) = 7.0;
  mat_2(3, 3) = 987654321.9123456;

  ASSERT_TRUE(mat_1 == mat_2);

  mat_1(2, 2) = 4.1;
  ASSERT_FALSE(mat_1 == mat_2);
}

TEST(operator_assignment, test_1) {
  Matrix mat_1(6, 3);
  Matrix mat_2(4, 9);
  for (int i = 1; i <= 4; ++i) {
    for (int j = 1; j <= 9; ++j) {
      mat_2(i, j) = i + j + 1.5;
    }
  }
  mat_1 = mat_2;
  ASSERT_TRUE(mat_1.eq_matrix(mat_2));
}

TEST(operator_assignment, test_2) {
  Matrix mat_1(6, 3);
  Matrix mat_2(4, 9);
  for (int i = 1; i <= 4; ++i) {
    for (int j = 1; j <= 9; ++j) {
      mat_2(i, j) = pow(i + j + 1.5, 2.0);
    }
  }
  mat_1 = mat_2;
  ASSERT_EQ(mat_1.get_rows(), 4);
  ASSERT_EQ(mat_1.get_cols(), 9);
  ASSERT_TRUE(mat_1.eq_matrix(mat_2));
}

TEST(operator_copy, test_1) {
  Matrix mat_1(6, 3);
  Matrix mat_2(4, 9);
  for (int i = 1; i <= 4; ++i) {
    for (int j = 1; j <= 9; ++j) {
      mat_2(i, j) = pow(i + j + 1.5, 2.0);
    }
  }
  mat_1 = std::move(mat_2);
  ASSERT_EQ(mat_2.get_rows(), 0);
  ASSERT_EQ(mat_2.get_cols(), 0);
  ASSERT_FALSE(mat_1.eq_matrix(mat_2));
}

TEST(operator_sum_eq, test_1) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  Matrix mat_3(3, 3);
  for (int i = 1; i <= 3; ++i) {
    for (int j = 1; j <= 3; ++j) {
      mat_1(i, j) = i * j * 1.34;
      mat_2(i, j) = i * j * 2.54;
      mat_3(i, j) = i * j * (1.34 + 2.54);
    }
  }
  mat_1 += mat_2;
  ASSERT_TRUE(mat_1.eq_matrix(mat_3));
}

TEST(operator_sum_eq, test_2) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  Matrix mat_3(3, 3);
  for (int i = 1; i <= 3; ++i) {
    for (int j = 1; j <= 3; ++j) {
      mat_1(i, j) = M_PI - i * j * 1.34;
      mat_2(i, j) = M_PI - i * j * 2.54;
      mat_3(i, j) = 2 * M_PI - i * j * (1.34 + 2.54);
    }
  }
  mat_1 += mat_2;
  ASSERT_TRUE(mat_1.eq_matrix(mat_3));
}

TEST(operator_sum_eq, test_3) {
  Matrix mat_1(3, 3);
  Matrix mat_2(5, 5);
  EXPECT_THROW({ mat_1 += mat_2; }, e_error_matrix_t);
}

TEST(operator_sum_eq, test_4) {
  Matrix mat_1(2, 2);
  Matrix mat_2(2, 2);
  Matrix mat_3(2, 2);
  mat_1(1, 1) = 2.987654;
  mat_1(1, 2) = -5.3456;
  mat_1(2, 1) = 6.23;
  mat_1(2, 2) = -3.9292;
  mat_2(1, 1) = 4.838;
  mat_2(1, 2) = 8.0987;
  mat_2(2, 1) = -8;
  mat_2(2, 2) = -0.921;
  mat_3(1, 1) = 7.825654;
  mat_3(1, 2) = 2.7531;
  mat_3(2, 1) = -1.77;
  mat_3(2, 2) = -4.8502;
  mat_1 += mat_2;
  ASSERT_TRUE(mat_1.eq_matrix(mat_3));
}

TEST(operator_sub_eq, test_1) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  Matrix mat_3(3, 3);
  for (int i = 1; i <= 3; ++i) {
    for (int j = 1; j <= 3; ++j) {
      mat_1(i, j) = i * j * 1.34;
      mat_2(i, j) = i * j * 2.54;
      mat_3(i, j) = i * j * (1.34 - 2.54);
    }
  }
  mat_1 -= mat_2;
  ASSERT_TRUE(mat_1.eq_matrix(mat_3));
}

TEST(operator_sub_eq, test_2) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  Matrix mat_3(3, 3);
  for (int i = 1; i <= 3; ++i) {
    for (int j = 1; j <= 3; ++j) {
      mat_1(i, j) = M_PI - i * j * 1.34;
      mat_2(i, j) = M_PI - i * j * 2.54;
      mat_3(i, j) = -i * j * (1.34 - 2.54);
    }
  }
  mat_1 -= mat_2;
  ASSERT_TRUE(mat_1.eq_matrix(mat_3));
}

TEST(operator_sub_eq, test_3) {
  Matrix mat_1(3, 3);
  Matrix mat_2(5, 5);
  EXPECT_THROW({ mat_1 -= mat_2; }, e_error_matrix_t);
}

TEST(operator_sub_eq, test_4) {
  Matrix mat_1(3, 3);
  Matrix mat_2(3, 3);
  Matrix mat_3(3, 3);
  mat_1(1, 1) = 0.1;
  mat_1(1, 2) = 0.2;
  mat_1(1, 3) = 0.3;
  mat_1(2, 1) = 0.4;
  mat_1(2, 2) = 0.5;
  mat_1(2, 3) = 0.6;
  mat_1(3, 1) = 0.7;
  mat_1(3, 2) = 0.8;
  mat_1(3, 3) = 0.9;
  mat_2(1, 1) = 1.0;
  mat_2(1, 2) = 2.0;
  mat_2(1, 3) = 3.0;
  mat_2(2, 1) = 4.0;
  mat_2(2, 2) = 5.0;
  mat_2(2, 3) = 6.0;
  mat_2(3, 1) = 7.0;
  mat_2(3, 2) = 8.0;
  mat_2(3, 3) = 9.0;
  mat_3(1, 1) = -0.9;
  mat_3(1, 2) = -1.8;
  mat_3(1, 3) = -2.7;
  mat_3(2, 1) = -3.6;
  mat_3(2, 2) = -4.5;
  mat_3(2, 3) = -5.4;
  mat_3(3, 1) = -6.3;
  mat_3(3, 2) = -7.2;
  mat_3(3, 3) = -8.1;
  mat_1 -= mat_2;
  ASSERT_TRUE(mat_1.eq_matrix(mat_3));
}

TEST(operator_mul_number_eq, test_1) {
  Matrix mat_1(3, 9);
  Matrix mat_2(3, 9);
  for (int i = 1; i <= 3; ++i) {
    for (int j = 1; j <= 9; ++j) {
      mat_1(i, j) = 53.32423;
      mat_2(i, j) = 53.32423 * 1.2342;
    }
  }
  mat_1 *= 1.2342;
  ASSERT_TRUE(mat_1.eq_matrix(mat_2));
}

TEST(operator_mul_number_eq, test_2) {
  Matrix mat_1(3, 9);
  Matrix mat_2(3, 9);
  for (int i = 1; i <= 3; ++i) {
    for (int j = 1; j <= 9; ++j) {
      mat_1(i, j) = 53.32423;
      mat_2(i, j) = -53.32423 * 1.13;
    }
  }
  mat_1 *= -1.13;
  ASSERT_TRUE(mat_1.eq_matrix(mat_2));
}

TEST(operator_mul_mutrix_eq, test_1) {
  Matrix mat_1(3, 9);
  Matrix mat_2(3, 9);
  EXPECT_THROW({ mat_1 *= mat_2; }, e_error_matrix_t);
}

TEST(operator_mul_mutrix_eq, test_2) {
  Matrix mat_1(5, 4);
  Matrix mat_2(4, 4);
  Matrix mat_3(5, 4);
  mat_1(1, 1) = 2;
  mat_1(1, 2) = 5;
  mat_1(1, 3) = 7;
  mat_1(1, 4) = -4;
  mat_1(2, 1) = 6;
  mat_1(2, 2) = 3;
  mat_1(2, 3) = 4;
  mat_1(2, 4) = 14;
  mat_1(3, 1) = 5;
  mat_1(3, 2) = -2;
  mat_1(3, 3) = -3;
  mat_1(3, 4) = -1;
  mat_1(4, 1) = 10;
  mat_1(4, 2) = 3;
  mat_1(4, 3) = 9;
  mat_1(4, 4) = -3;
  mat_1(5, 1) = -3;
  mat_1(5, 2) = 3;
  mat_1(5, 3) = 1;
  mat_1(5, 4) = 5;
  mat_2(1, 1) = 8;
  mat_2(1, 2) = 8;
  mat_2(1, 3) = 3;
  mat_2(1, 4) = 5;
  mat_2(2, 1) = -7;
  mat_2(2, 2) = 7;
  mat_2(2, 3) = 1;
  mat_2(2, 4) = 1;
  mat_2(3, 1) = 7;
  mat_2(3, 2) = 3;
  mat_2(3, 3) = 4;
  mat_2(3, 4) = -4;
  mat_2(4, 1) = 10;
  mat_2(4, 2) = 3;
  mat_2(4, 3) = 9;
  mat_2(4, 4) = -3;
  mat_3(1, 1) = -10;
  mat_3(1, 2) = 60;
  mat_3(1, 3) = 3;
  mat_3(1, 4) = -1;
  mat_3(2, 1) = 195;
  mat_3(2, 2) = 123;
  mat_3(2, 3) = 163;
  mat_3(2, 4) = -25;
  mat_3(3, 1) = 23;
  mat_3(3, 2) = 14;
  mat_3(3, 3) = -8;
  mat_3(3, 4) = 38;
  mat_3(4, 1) = 92;
  mat_3(4, 2) = 119;
  mat_3(4, 3) = 42;
  mat_3(4, 4) = 26;
  mat_3(5, 1) = 12;
  mat_3(5, 2) = 15;
  mat_3(5, 3) = 43;
  mat_3(5, 4) = -31;
  mat_1 *= mat_2;
  ASSERT_TRUE(mat_1.eq_matrix(mat_3));
}

TEST(operator_mul_mutrix_eq, test_3) {
  Matrix mat_1(5, 4);
  Matrix mat_2(4, 4);
  Matrix mat_3(5, 4);
  mat_1(1, 1) = 2.987654;
  mat_1(1, 2) = -5.3456;
  mat_1(2, 1) = 6.23;
  mat_1(2, 2) = -3.9292;
  mat_2(1, 1) = 4.838;
  mat_2(1, 2) = 8.0987;
  mat_2(1, 3) = 8.09;
  mat_2(1, 4) = -987;
  mat_2(2, 1) = -8;
  mat_2(2, 2) = -0.921;
  mat_2(2, 3) = -0.91;
  mat_2(2, 4) = 21;
  mat_3(1, 1) = 57.219070052;
  mat_3(1, 2) = 29.1194110498;
  mat_3(1, 3) = 29.03461686;
  mat_3(1, 4) = -3061.072098;
  mat_3(2, 1) = 61.57434;
  mat_3(2, 2) = 54.0736942;
  mat_3(2, 3) = 53.976272;
  mat_3(2, 4) = -6231.5232;
  mat_1 *= mat_2;
  ASSERT_TRUE(mat_1.eq_matrix(mat_3));
}

TEST(operator_mul_mutrix_eq, test_4) {
  Matrix mat_1(5, 4);
  Matrix mat_2(4, 4);
  Matrix mat_3(5, 4);
  for (int i = 1; i <= 4; ++i) {
    for (int j = 1; j <= 4; ++j) {
      mat_2(i, j) = i + j;
    }
  }
  mat_1 *= mat_2;
  ASSERT_TRUE(mat_1.eq_matrix(mat_3));
}

TEST(operator_mul_mutrix_eq, test_5) {
  Matrix mat_1(5, 4);
  Matrix mat_2(4, 4);
  Matrix mat_3(5, 4);
  mat_1(1, 1) = 0;
  mat_1(1, 2) = 9;
  mat_1(1, 3) = 1;
  mat_1(2, 1) = 1;
  mat_1(2, 2) = 3;
  mat_1(2, 3) = 7;
  mat_1(3, 1) = 2;
  mat_1(3, 2) = 7;
  mat_1(3, 3) = 0;
  mat_2(1, 1) = 0;
  mat_2(1, 2) = 9;
  mat_2(1, 3) = 8;
  mat_2(2, 1) = 0;
  mat_2(2, 2) = 9;
  mat_2(2, 3) = 9;
  mat_2(3, 1) = 1;
  mat_2(3, 2) = 9;
  mat_2(3, 3) = 6;
  mat_3(1, 1) = 1;
  mat_3(1, 2) = 90;
  mat_3(1, 3) = 87;
  mat_3(2, 1) = 7;
  mat_3(2, 2) = 99;
  mat_3(2, 3) = 77;
  mat_3(3, 1) = 0;
  mat_3(3, 2) = 81;
  mat_3(3, 3) = 79;
  mat_1 *= mat_2;
  ASSERT_TRUE(mat_1.eq_matrix(mat_3));
}

TEST(indexing, test_1) {
  Matrix mat_1(4, 7);
  for (int i = 1; i <= 4; ++i) {
    for (int j = 1; j <= 7; ++j) {
      mat_1(i, j) = i + j * 3.42;
    }
  }
  ASSERT_NEAR(mat_1(3, 4), 16.68, 1E-7);
  ASSERT_NEAR(mat_1(2, 3), 12.26, 1E-7);
  ASSERT_NEAR(mat_1(4, 7), 27.94, 1E-7);
  ASSERT_NEAR(mat_1(1, 1), 4.42, 1E-7);
  ASSERT_THROW(mat_1(0, 1), e_error_matrix_t);
  ASSERT_THROW(mat_1(9, 1), e_error_matrix_t);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
