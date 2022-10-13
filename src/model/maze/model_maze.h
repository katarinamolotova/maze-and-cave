//
// Created by Manhunter Groot on 9/24/22.
//

#ifndef SRC_MODEL_MODEL_MAZE_H_
#define SRC_MODEL_MODEL_MAZE_H_

#include <map>
#include <random>
#include <utility>

#include "../helpers/matrix.h"
#include "../helpers/parser.h"

using std::pair;

namespace s21 {

enum Direction { LEFT, RIGHT, UP, DOWN };

typedef enum Matrix_type { M_RIGHT, M_BOTTOM } MATRIX_TYPE;

class Maze {
 private:
  bool error_{};
  int rows_{};
  int cols_{};
  int p_row_{};
  int p_col_{};
  int move_vector_ = DOWN;
  std::map<int, int> set_map_{};
  int set_counter_{};
  s21::Matrix<bool> right_borders_;
  s21::Matrix<bool> bottom_borders_;
  static bool RandomBorder();
  void CreateNewRow(int row);
  void CreateFirstRow();
  void ChangeSet(int from, int to);
  void AddRightBorders(int row);
  void AddBottomBorders(int row);
  void AddEndRow();
  void TurnLeft();
  void TurnRight();
  static Direction CalcDirection(pair<int, int> from, pair<int, int> to);
  bool StepUp();
  std::vector<int> set_row_;
  std::vector<pair<int, int>> path_{};
  std::map<pair<int, int>, int> path_point_counter_{};

 public:
  Maze() = default;
  Maze(int rows, int cols);
  explicit Maze(const std::string& file_name);
  ~Maze() = default;

  bool operator()(int row, int col, MATRIX_TYPE type);

  void Generate();
  void FindPath(pair<int, int> start, pair<int, int> end);
  std::vector<Direction> GetPath();

  [[nodiscard]] int GetRows() const { return rows_; }
  [[nodiscard]] int GetCols() const { return cols_; }
  [[nodiscard]] bool GetError() const { return error_; }
};

}  // namespace s21

#endif  // SRC_MODEL_MODEL_MAZE_H_
