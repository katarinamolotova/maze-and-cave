//
// Created by Manhunter Groot on 9/24/22.
//

#include "model_maze.h"

namespace s21 {

Maze::Maze(int rows, int cols) : rows_(rows), cols_(cols) {
  right_borders_ = Matrix<bool>(rows_, cols_);
  bottom_borders_ = Matrix<bool>(rows_, cols_);
  Generate();
}

Maze::Maze(const std::string& file_name) {
  Parser parser(file_name);
  parser.FillMatrix(right_borders_, bottom_borders_);
  rows_ = right_borders_.GetRows();
  cols_ = right_borders_.GetCols();
  error_ = parser.GetError();
}

bool Maze::operator()(int row, int col, MATRIX_TYPE type) {
  int result;
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
    error_ = true;
    return false;
  }

  if (type == M_RIGHT) {
    result = right_borders_(row, col);
  } else if (type == M_BOTTOM) {
    result = bottom_borders_(row, col);
  } else {
    result = true;
  }
  return result;
}

void Maze::CreateFirstRow() {
  set_counter_ = 1;

  for (auto col = 0; col < cols_; ++col) {
    set_row_.push_back(set_counter_);
    set_map_[set_counter_] = 1;
    set_counter_++;
  }
}

void Maze::CreateNewRow(int row) {
  set_map_.clear();

  for (auto col = 0; col < cols_; ++col) {
    right_borders_(row, col) = false;
    if (bottom_borders_(row - 1, col)) {
      set_row_[col] = set_counter_++;
    }
    set_map_[set_row_[col]]++;
    bottom_borders_(row, col) = false;
  }
}

void Maze::ChangeSet(int from, int to) {
  for (auto col = 0; col < cols_; ++col) {
    if (set_row_[col] == from) {
      set_row_[col] = to;
      set_map_[from]--;
      set_map_[to]++;
    }
  }
}

void Maze::AddRightBorders(int row) {
  for (auto col = 0; col < cols_ - 1; ++col) {
    if (set_row_[col] == set_row_[col + 1]) {
      right_borders_(row, col) = true;
    } else {
      right_borders_(row, col) = RandomBorder();
    }
    if (!right_borders_(row, col)) {
      ChangeSet(set_row_[col + 1], set_row_[col]);
    }
  }
  right_borders_(row, cols_ - 1) = true;
}

void Maze::AddBottomBorders(int row) {
  for (auto col = 0; col < cols_; ++col) {
    if (set_map_[set_row_[col]] > 1) {
      bottom_borders_(row, col) = RandomBorder();
      if (bottom_borders_(row, col)) set_map_[set_row_[col]]--;
    }
  }
}

void Maze::AddEndRow() {
  for (auto col = 0; col < cols_ - 1; ++col) {
    if (set_row_[col] != set_row_[col + 1]) {
      right_borders_(rows_ - 1, col) = false;
      ChangeSet(set_row_[col + 1], set_row_[col]);
    }
    bottom_borders_(rows_ - 1, col) = true;
  }
  bottom_borders_(rows_ - 1, cols_ - 1) = true;
}

void Maze::Generate() {
  CreateFirstRow();

  for (auto row = 0; row < rows_; ++row) {
    if (row > 0) CreateNewRow(row);
    AddRightBorders(row);
    AddBottomBorders(row);
  }
  AddEndRow();
}

bool Maze::RandomBorder() {
  std::random_device rd;
  std::default_random_engine engine(rd());
  std::uniform_int_distribution<int> dist(0, 1);
  return static_cast<bool>(dist(engine));
}

void Maze::TurnLeft() {
  switch (move_vector_) {
    case LEFT:
      move_vector_ = DOWN;
      break;
    case RIGHT:
      move_vector_ = UP;
      break;
    case UP:
      move_vector_ = LEFT;
      break;
    case DOWN:
      move_vector_ = RIGHT;
      break;
  }
}

void Maze::TurnRight() {
  switch (move_vector_) {
    case LEFT:
      move_vector_ = UP;
      break;
    case RIGHT:
      move_vector_ = DOWN;
      break;
    case UP:
      move_vector_ = RIGHT;
      break;
    case DOWN:
      move_vector_ = LEFT;
      break;
  }
}

bool Maze::StepUp() {
  bool result = false;
  if (move_vector_ == RIGHT && !right_borders_(p_row_, p_col_)) {
    p_col_++;
    result = true;
  }
  if (move_vector_ == DOWN && !bottom_borders_(p_row_, p_col_)) {
    p_row_++;
    result = true;
  }
  if (move_vector_ == LEFT && p_col_ > 0 &&
      !right_borders_(p_row_, p_col_ - 1)) {
    p_col_--;
    result = true;
  }
  if (move_vector_ == UP && p_row_ > 0 &&
      !bottom_borders_(p_row_ - 1, p_col_)) {
    p_row_--;
    result = true;
  }
  return result;
}

void Maze::FindPath(pair<int, int> start, pair<int, int> end) {
  path_.clear();
  path_point_counter_.clear();
  p_row_ = start.first;
  p_col_ = start.second;
  int e_row = end.first;
  int e_col = end.second;

  while ((p_row_ != e_row || p_col_ != e_col) && !error_) {
    path_.emplace_back(p_row_, p_col_);
    path_point_counter_[std::make_pair(p_row_, p_col_)]++;
    TurnLeft();
    while (!StepUp()) {
      TurnRight();
    }
  }
  path_.emplace_back(e_row, e_col);
}

Direction Maze::CalcDirection(pair<int, int> from, pair<int, int> to) {
  Direction direction;
  if (to.first - from.first == 1) direction = DOWN;
  if (to.first - from.first == -1) direction = UP;
  if (to.second - from.second == 1) direction = RIGHT;
  if (to.second - from.second == -1) direction = LEFT;
  return direction;
}

std::vector<Direction> Maze::GetPath() {
  std::vector<Direction> path{};
  bool skip_flag = false;
  int counter;
  pair<int, int> path_point;
  pair<int, int> prev_point;
  if (!path_.empty()) {
    prev_point = path_[0];
  }
  for (auto& element : path_) {
    if (!skip_flag) counter = path_point_counter_[element];
    if (counter > 1 && !skip_flag) {
      path_point = element;
      skip_flag = true;
    }
    if (skip_flag && path_point == element) counter--;
    if (skip_flag && counter > 0) continue;
    if (skip_flag && path_point == element && counter == 0) skip_flag = false;
    if (!skip_flag && counter <= 1) {
      if (element != prev_point) {
        path.push_back(CalcDirection(prev_point, element));
      }
      prev_point = element;
    }
  }
  return path;
}

}  // namespace s21