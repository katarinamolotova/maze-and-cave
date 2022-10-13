#ifndef SRC_MODEL_HELPERS_MATRIX_H_
#define SRC_MODEL_HELPERS_MATRIX_H_

#include <cmath>
#include <cstring>
#include <iostream>
#include <stdexcept>

namespace s21 {
template <class T>
class Matrix {
 private:
  int rows_{}, cols_{};
  T **matrix_{};
  bool error_{false};

 private:
  void CreateMatrix();
  void DeleteMatrix();
  void CopyMatrix(Matrix const &other);
  bool IsEqualSize(const Matrix &other);

 public:
  [[nodiscard]] int GetRows() const;
  [[nodiscard]] int GetCols() const;
  bool GetError() { return error_; };
  bool IsEqualMatrix(const Matrix &other);

  Matrix() = default;
  Matrix(int rows, int cols);
  Matrix(const Matrix &other);

  bool operator==(const Matrix &other);
  Matrix &operator=(const Matrix &other);
  T &operator()(int row, int col);

  ~Matrix();
};
}  // namespace s21

#endif  // SRC_MODEL_HELPERS_MATRIX_H_
