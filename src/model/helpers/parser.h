#ifndef SRC_MODEL_HELPERS_PARSER_H_
#define SRC_MODEL_HELPERS_PARSER_H_

#include <cmath>
#include <fstream>
#include <set>
#include <string>

#include "matrix.h"

using std::set;
using std::string;

namespace s21 {

class Parser {
 private:
  s21::Matrix<bool> startingMatrix_;
  std::ifstream* file_{};
  bool error_{false};

  std::pair<int, int> GetMatrixSize();
  void GetMatrix(Matrix<bool>& matrix);

 public:
  explicit Parser(const string& file_name);
  Parser() = default;
  ~Parser() {
    if (file_->is_open()) file_->close();
    delete file_;
  }

  void FillMatrix(Matrix<bool>& matrix);
  void FillMatrix(Matrix<bool>& matrix_right, Matrix<bool>& matrix_bottom);

  [[nodiscard]] bool GetError() const { return error_; };
};
}  // namespace s21
#endif  //  SRC_MODEL_HELPERS_PARSER_H_