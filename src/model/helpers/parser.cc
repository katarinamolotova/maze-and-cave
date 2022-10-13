#include "parser.h"

#include <iostream>

using namespace s21;

Parser::Parser(const string& file_name) : error_(false) {
  file_ = new std::ifstream(file_name);
  if (!file_->is_open()) error_ = true;
}

void Parser::FillMatrix(Matrix<bool>& matrix_right,
                        Matrix<bool>& matrix_bottom) {
  if (!error_) {
    std::pair<int, int> matrix_size = GetMatrixSize();
    matrix_right = Matrix<bool>(matrix_size.first, matrix_size.second);
    matrix_bottom = Matrix<bool>(matrix_size.first, matrix_size.second);
    GetMatrix(matrix_right);
    GetMatrix(matrix_bottom);
  }
}

void Parser::FillMatrix(Matrix<bool>& matrix) {
  if (!error_) {
    std::pair<int, int> matrix_size = GetMatrixSize();
    matrix = Matrix<bool>(matrix_size.first, matrix_size.second);
    GetMatrix(matrix);
  }
}

std::pair<int, int> Parser::GetMatrixSize() {
  int rows = 0, cols = 0;
  if (!error_) {
    string line;
    getline(*file_, line);
    size_t pos = 0;
    rows = std::stoi(line, &pos, 10);
    cols = std::stoi(&line[pos], &pos, 10);
  }
  return {rows, cols};
}

void Parser::GetMatrix(Matrix<bool>& matrix) {
  int row = 0;
  string line;
  while (getline(*file_, line) && row < matrix.GetRows()) {
    if (line.length() > 1) {
      for (int col = 0; col < matrix.GetCols() && !error_; ++col) {
        int num = std::stoi(&line[col * 2], nullptr, 10);
        matrix(row, col) = num;
      }
      row++;
    }
  }
  if (row != matrix.GetRows()) {
    error_ = true;
  }
}
