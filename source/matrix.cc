#include "matrix.h"

Matrix::Matrix(int rows, int cols) {
  if (!is_valid_matrix(rows, cols)) {
    throw MATRIX_E_MATCH;
  }
  init_matrix(rows, cols);
}

Matrix::Matrix(const Matrix& other) : Matrix(other.m_rows, other.m_cols) {
  copy_matrix(other);
}

Matrix::Matrix(Matrix&& other) noexcept {
  m_rows = other.m_rows;
  m_cols = other.m_cols;
  m_matrix = other.m_matrix;
  other.m_matrix = nullptr;
  other.matrix_data_reset();
}

Matrix::~Matrix() { matrix_data_reset(); }

int Matrix::get_rows() const { return m_rows; }

int Matrix::get_cols() const { return m_cols; }

void Matrix::set_rows(const int& rows) {
  if (!is_valid_matrix(rows, m_cols)) {
    throw MATRIX_E_MATCH;
  }
  Matrix temp(rows, m_cols);
  int min_rows = std::min(m_rows, rows);
  copy_temp_data(temp, min_rows, m_cols);
  *this = std::move(temp);
}

void Matrix::set_cols(const int& cols) {
  if (!is_valid_matrix(m_rows, cols)) {
    throw MATRIX_E_MATCH;
  }
  Matrix temp(m_rows, cols);
  int min_cols = std::min(m_cols, cols);
  copy_temp_data(temp, m_rows, min_cols);
  free_matrix();
  *this = std::move(temp);
}

void Matrix::set_rows_cols(const int& rows, const int& cols) {
  if (!is_valid_matrix(rows, cols)) {
    throw MATRIX_E_MATCH;
  }
  Matrix temp(rows, cols);
  int min_rows = std::min(m_rows, rows);
  int min_cols = std::min(m_cols, cols);
  copy_temp_data(temp, min_rows, min_cols);
  free_matrix();
  *this = std::move(temp);
}

bool Matrix::eq_matrix(const Matrix& other) const {
  bool result = false;
  if (equal(m_rows, other.m_rows) && equal(m_cols, other.m_cols)) {
    result = true;
    for (int i = 0; i < m_rows; ++i) {
      for (int j = 0; j < m_cols; ++j) {
        if (fabs(m_matrix[i][j] - other.m_matrix[i][j]) >= EPS) result = false;
      }
    }
  }
  return result;
}

void Matrix::sum_matrix(const Matrix& other) {
  if (!equal(m_rows, other.m_rows) || !equal(m_cols, other.m_cols)) {
    throw MATRIX_E_CALC;
  }
  for (int i = 0; i < m_rows; ++i) {
    for (int j = 0; j < m_cols; ++j) {
      m_matrix[i][j] += other.m_matrix[i][j];
    }
  }
}

void Matrix::sub_matrix(const Matrix& other) {
  if (!equal(m_rows, other.m_rows) || !equal(m_cols, other.m_cols)) {
    throw MATRIX_E_CALC;
  }
  for (int i = 0; i < m_rows; ++i) {
    for (int j = 0; j < m_cols; ++j) {
      m_matrix[i][j] -= other.m_matrix[i][j];
    }
  }
}

void Matrix::mul_number(const double num) {
  for (int i = 0; i < m_rows; ++i) {
    for (int j = 0; j < m_cols; ++j) {
      m_matrix[i][j] *= num;
    }
  }
}

void Matrix::mul_matrix(const Matrix& other) {
  if (!equal(m_cols, other.m_rows)) {
    throw MATRIX_E_CALC;
  }
  Matrix temp(m_rows, other.m_cols);
  for (int i = 0; i < temp.m_rows; ++i) {
    for (int j = 0; j < temp.m_cols; ++j) {
      temp.m_matrix[i][j] = 0.0;
      for (int k = 0; k < m_cols; ++k) {
        temp.m_matrix[i][j] += m_matrix[i][k] * other.m_matrix[k][j];
      }
    }
  }
  *this = std::move(temp);
}

Matrix Matrix::transpose() {
  Matrix temp(m_cols, m_rows);
  for (int i = 0; i < m_rows; ++i) {
    for (int j = 0; j < m_cols; ++j) {
      temp.m_matrix[j][i] = m_matrix[i][j];
    }
  }
  return temp;
}

Matrix Matrix::calc_complements() {
  if (!equal(m_rows, m_cols)) {
    throw MATRIX_E_CALC;
  }
  Matrix temp(m_rows, m_cols);
  if (m_rows == 1) {
    temp.m_matrix[0][0] = 1.0;
  } else {
    for (int i = 0; i < temp.m_rows; ++i) {
      for (int j = 0; j < temp.m_cols; ++j) {
        Matrix minor = minor_of_matrix(i, j);
        double det = minor.determinant();
        temp.m_matrix[i][j] = pow(-1.0, i + j) * det;
      }
    }
  }
  return temp;
}

double Matrix::determinant() {
  if (!equal(m_rows, m_cols)) {
    throw MATRIX_E_CALC;
  }
  double result = 0;
  if (m_rows == 1) {
    result = m_matrix[0][0];
  } else if (m_rows == 2) {
    result = m_matrix[0][0] * m_matrix[1][1] - m_matrix[0][1] * m_matrix[1][0];
  } else {
    for (int i = 0; i < m_rows; ++i) {
      Matrix minor = minor_of_matrix(i, 0);
      double det = minor.determinant();
      result += m_matrix[i][0] * pow(-1.0, i) * det;
    }
  }
  return result;
}

Matrix Matrix::minor_of_matrix(const int row, const int col) {
  Matrix t_matrix(m_rows - 1, m_cols - 1);
  for (int i = 0, t_i = 0; i < m_rows; ++i) {
    if (i != row) {
      for (int j = 0, t_j = 0; j < m_cols; ++j) {
        if (j != col) t_matrix.m_matrix[t_i][t_j++] = m_matrix[i][j];
      }
      ++t_i;
    }
  }
  return t_matrix;
}

Matrix Matrix::inverse_matrix() {
  double det = determinant();
  if (fabs(det) < EPS) {
    throw MATRIX_E_CALC;
  }
  Matrix comp_temp = calc_complements();
  Matrix tran_temp = comp_temp.transpose();
  tran_temp.mul_number(1.0 / det);
  return tran_temp;
}

Matrix Matrix::operator+(const Matrix& other) {
  Matrix result(*this);
  result.sum_matrix(other);
  return result;
}

Matrix Matrix::operator-(const Matrix& other) {
  Matrix result(*this);
  result.sub_matrix(other);
  return result;
}

Matrix Matrix::operator*(const Matrix& other) {
  Matrix result(*this);
  result.mul_matrix(other);
  return result;
}

Matrix Matrix::operator*(const double& other) {
  Matrix result(*this);
  result.mul_number(other);
  return result;
}

bool Matrix::operator==(const Matrix& other) const { return eq_matrix(other); }

Matrix& Matrix::operator=(const Matrix& other) {
  if (this != &other) {
    matrix_data_reset();
    init_matrix(other.m_rows, other.m_cols);
    copy_matrix(other);
  }
  return *this;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept {
  if (this != &other) {
    matrix_data_reset();
    m_rows = other.m_rows;
    m_cols = other.m_cols;
    m_matrix = other.m_matrix;
    other.m_matrix = nullptr;
    other.matrix_data_reset();
  }
  return *this;
}

void Matrix::operator+=(const Matrix& other) { sum_matrix(other); }

void Matrix::operator-=(const Matrix& other) { sub_matrix(other); }

void Matrix::operator*=(const Matrix& other) { mul_matrix(other); }

void Matrix::operator*=(const double& other) { mul_number(other); }

double& Matrix::operator()(int i, int j) {
  if (i < 1 || i > m_rows || j < 1 || j > m_cols) {
    throw MATRIX_E_RANGE;
  }
  return m_matrix[i - 1][j - 1];
}

const double& Matrix::operator()(int i, int j) const {
  if (i < 1 || i > m_rows || j < 1 || j > m_cols) {
    throw MATRIX_E_RANGE;
  }
  return m_matrix[i - 1][j - 1];
}

bool Matrix::is_valid_matrix(int rows, int cols) {
  return (rows > 0 && cols > 0);
}

void Matrix::init_matrix(const int& rows, const int& cols) {
  m_rows = rows;
  m_cols = cols;
  if ((m_matrix = new double*[m_rows]) == nullptr) {
    throw MATRIX_E_MEMORY;
  }
  for (int i = 0; i < m_rows; ++i) {
    if ((m_matrix[i] = new double[m_cols]) == nullptr) {
      throw MATRIX_E_MEMORY;
    }
    std::memset(m_matrix[i], 0, m_cols * sizeof(double));
  }
}

void Matrix::free_matrix() {
  if (m_matrix != nullptr) {
    for (int i = 0; i < m_rows; ++i)
      if (m_matrix[i] != nullptr) delete[] m_matrix[i];
    delete[] m_matrix;
    m_matrix = nullptr;
  }
}

void Matrix::matrix_data_reset() {
  free_matrix();
  m_rows = 0;
  m_cols = 0;
}

void Matrix::copy_temp_data(const Matrix& src, const int rows, const int cols) {
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      src.m_matrix[i][j] = m_matrix[i][j];
    }
  }
}

bool Matrix::equal(const int& a, const int& b) const { return a == b; }

void Matrix::copy_matrix(const Matrix& other) {
  for (int i = 0; i < m_rows; ++i) {
    for (int j = 0; j < m_cols; ++j) {
      m_matrix[i][j] = other.m_matrix[i][j];
    }
  }
}
