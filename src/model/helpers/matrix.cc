#include "matrix.h"

template <typename T>
s21::Matrix<T>::Matrix(int rows, int cols)
    : rows_(rows), cols_(cols), matrix_(nullptr) {
  if (rows_ < 0 || cols_ < 0) error_ = true;

  if (!error_) CreateMatrix();
}

template <typename T>
s21::Matrix<T>::Matrix(const Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  CreateMatrix();
  CopyMatrix(other);
}

template <typename T>
s21::Matrix<T>::~Matrix() {
  DeleteMatrix();
}

template <typename T>
void s21::Matrix<T>::CreateMatrix() {
  matrix_ = new T*[rows_];
  for (auto i = 0; i < rows_; i++) matrix_[i] = new T[cols_]();
}

template <typename T>
int s21::Matrix<T>::GetCols() const {
  return cols_;
}

template <typename T>
int s21::Matrix<T>::GetRows() const {
  return rows_;
}

template <typename T>
void s21::Matrix<T>::DeleteMatrix() {
  if (matrix_ != nullptr) {
    for (auto i = 0; i < rows_; i++) delete[] matrix_[i];
    delete[] matrix_;
    matrix_ = nullptr;
  }
  cols_ = 0;
  rows_ = 0;
}

template <typename T>
bool s21::Matrix<T>::IsEqualSize(const Matrix& other) {
  return (cols_ == other.cols_ && rows_ == other.rows_);
}

template <typename T>
bool s21::Matrix<T>::IsEqualMatrix(const Matrix& other) {
  bool flag_equal = IsEqualSize(other);
  if (flag_equal) {
    for (int i = 0; i < rows_ && flag_equal; i++)
      if (std::memcmp(matrix_[i], other.matrix_[i],
                      sizeof(*matrix_[i]) * cols_) != 0)
        flag_equal = false;
  }
  return flag_equal;
}

template <typename T>
void s21::Matrix<T>::CopyMatrix(Matrix const& other) {
  if (!IsEqualSize(other)) {
    DeleteMatrix();
    cols_ = other.cols_;
    rows_ = other.rows_;
    CreateMatrix();
  }
  if (matrix_ != nullptr) {
    for (auto i = 0; i < rows_; i++)
      std::memcpy(matrix_[i], other.matrix_[i], sizeof(*matrix_[i]) * cols_);
  }
}

template <typename T>
s21::Matrix<T>& s21::Matrix<T>::operator=(const Matrix& other) {
  if (&other != this) CopyMatrix(other);
  return *this;
}

template <typename T>
T& s21::Matrix<T>::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0)
    throw std::range_error("Incorrect matrix size");
  return matrix_[row][col];
}

template <class T>
bool s21::Matrix<T>::operator==(const Matrix& other) {
  return IsEqualMatrix(other);
}

template class s21::Matrix<bool>;
template class s21::Matrix<int>;