#ifndef MATRIX_INCLUDE_MATRIX_H_
#define MATRIX_INCLUDE_MATRIX_H_

#include <algorithm>
#include <cmath>
#include <cstring>
#include <utility>

#define EPS 1e-7

typedef enum : std::uint8_t {
  MATRIX_E_OK,      // - Success
  MATRIX_E_MATCH,   // - Incorrect matrix sizes
  MATRIX_E_CALC,    // - Calculation error
  MATRIX_E_MEMORY,  // - Memory allocation error
  MATRIX_E_RANGE    // - Going beyond the matrix
} e_error_matrix_t;

class Matrix {
 private:
  int m_rows, m_cols;
  double** m_matrix;

 public:
  Matrix() = delete;
  Matrix(int rows, int cols);
  Matrix(const Matrix& other);
  Matrix(Matrix&& other) noexcept;
  ~Matrix();

  int get_rows() const;
  int get_cols() const;
  void set_rows(const int& rows);
  void set_cols(const int& cols);
  void set_rows_cols(const int& rows, const int& cols);

  bool eq_matrix(const Matrix& other) const;
  void sum_matrix(const Matrix& other);
  void sub_matrix(const Matrix& other);
  void mul_number(const double num);
  void mul_matrix(const Matrix& other);
  Matrix transpose();
  Matrix calc_complements();
  double determinant();
  Matrix inverse_matrix();

  Matrix operator+(const Matrix& other);
  Matrix operator-(const Matrix& other);
  Matrix operator*(const Matrix& other);
  Matrix operator*(const double& other);
  bool operator==(const Matrix& other) const;
  Matrix& operator=(const Matrix& other);
  Matrix& operator=(Matrix&& other) noexcept;
  void operator+=(const Matrix& other);
  void operator-=(const Matrix& other);
  void operator*=(const Matrix& other);
  void operator*=(const double& other);
  double& operator()(int i, int j);
  const double& operator()(int i, int j) const;

 protected:
  void copy_temp_data(const Matrix& src, const int rows, const int cols);
  Matrix minor_of_matrix(const int row, const int col);
  void init_matrix(const int& rows, const int& cols);
  bool equal(const int& a, const int& b) const;
  bool is_valid_matrix(int rows, int cols);
  void copy_matrix(const Matrix& other);
  void matrix_data_reset();
  void free_matrix();
};

#endif  // MATRIX_INCLUDE_MATRIX_H_
