//
// Created by Rebbecca Gormond on 9/25/22.
//
#ifndef SRC_MODEL_CAVE_MODEL_CAVE_H
#define SRC_MODEL_CAVE_MODEL_CAVE_H

#include <cstdlib>
#include <random>

#include "../helpers/matrix.h"
#include "../helpers/parser.h"

namespace s21 {
class Cave {
 private:
  Matrix<bool> cave_map_;
  Matrix<bool> cave_old_map_;
  int death_limit_{};
  int birth_limit_{};
  bool this_end_{};
  bool error_{};

 private:
  void RandomCave_();
  static int CountAliveNeighbor_(Matrix<bool>& sample_matrix, int row, int col);
  static bool RandomGenerate_();

 public:
  Cave() = default;
  Cave(int rows, int cols, std::pair<int, int> death_birth_limits);
  Cave(const std::string& file_name, std::pair<int, int> death_birth_limits);
  ~Cave() = default;

  bool operator()(int row, int col);

  void UpdateCaveMap();
  [[nodiscard]] bool GetThisEnd() const;
  [[nodiscard]] int GetRows() const;
  [[nodiscard]] int GetCols() const;
  [[nodiscard]] int GetError() const;
};
}  // namespace s21

#endif  // SRC_MODEL_CAVE_MODEL_CAVE_H
