# Matrix Library

This is a C++ library that provides a Matrix class with various matrix operations, such as addition, subtraction, multiplication, and more.

## Building the Project

To build the project, you can use CMake. Here are the steps to build the project:

1. Clone the repository to your local machine.
2. Navigate to the project directory
3. Run `make`

## Reusing and Compiling with Other Projects

To use this library in your own C++ project, simply link against the `Matrix.a` library file generated in the lib directory.

## Dependencies

This project depends on the Google Test framework for unit testing. CMake will download and build this dependency automatically when building the project.

## Running Tests

To run the unit tests for this library, navigate to the `build` directory and run the following command:

```
make tests
```

## Matrix operations

There is a brief description of the matrix operations below that need to be implemented in the developing library.
They are similar to the operations you performed earlier in «structured programming», so you can see a more detailed description of them there.
Note that some operations have exceptional situations that require special handling using the exception mechanism.

| Operation | Description | Exceptional situations |
| ----------- | ----------- | ----------- |
| `bool eq_matrix(const Matrix& other)` | Checks matrices for equality with each other |  |
| `void sum_matrix(const Matrix& other)` | Adds the second matrix to the current one | different matrix dimensions |
| `void sub_matrix(const Matrix& other)` | Subtracts another matrix from the current one | different matrix dimensions |
| `void mul_number(const double num) ` | Multiplies the current matrix by a number |  |
| `void mul_matrix(const Matrix& other)` | Multiplies the current matrix by the second matrix | the number of columns of the first matrix is not equal to the number of rows of the second matrix |
| `Matrix transpose()` | Creates a new transposed matrix from the current one and returns it |  |
| `Matrix calc_complements()` | Calculates the algebraic addition matrix of the current one and returns it | the matrix is not square |
| `double determinant()` | Calculates and returns the determinant of the current matrix | the matrix is not square |
| `Matrix inverse_matrix()` | Calculates and returns the inverse matrix | matrix determinant is 0 |

Apart from those operations, you also need to implement constructors and destructors:

| Method | Description |
| ----------- | ----------- |
| `Matrix()` | A basic constructor that initialises a matrix of some predefined dimension |  
| `Matrix(int rows, int cols) ` | Parametrized constructor with number of rows and columns |
| `Matrix(const Matrix& other)` | Copy constructor |
| `Matrix(Matrix&& other)` | Move constructor |
| `~Matrix()` | Destructor |

And you also need to overload the following operators, partly corresponding to the operations above:

| Operator | Description | Exceptional situations |
| ----------- | ----------- | ----------- |
| `+`      | Addition of two matrices | different matrix dimensions |
| `-`   | Subtraction of one matrix from another | different matrix dimensions |
| `*`  | Matrix multiplication and matrix multiplication by a number | the number of columns of the first matrix does not equal the number of rows of the second matrix |
| `==`  | Checks for matrices equality (`eq_matrix`) | |
| `=`  | Assignment of values from one matrix to another one | |
| `+=`  | Addition assignment (`sum_matrix`) | different matrix dimensions |
| `-=`  | Difference assignment (`sub_matrix`) | different matrix dimensions |
| `*=`  | Multiplication assignment (`mul_matrix`/`mul_number`) | the number of columns of the first matrix does not equal the number of rows of the second matrix |
| `(int i, int j)`  | Indexation by matrix elements (row, column) | index is outside the matrix |



## Examples

Here is an example of how to use the Matrix class to perform matrix operations:

```
#include "matrix.h"

int main() {
  Matrix m1(2, 3);
  Matrix m2(3, 2);

  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(0, 2) = 3;
  m1(1, 0) = 4;
  m1(1, 1) = 5;
  m1(1, 2) = 6;

  m2(0, 0) = 7;
  m2(0, 1) = 8;
  m2(1, 0) = 9;
  m2(1, 1) = 10;
  m2(2, 0) = 11;
  m2(2, 1) = 12;

  Matrix m3 = m1 * m2;
  m3.print();
}
```

This will create two matrices, set their values, multiply them, and print the resulting matrix.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.