//
// Created by Rebbecca Gormond on 9/27/22.
//

#include "model_facade.h"

using namespace s21;

Model* Model::model_ = nullptr;

void Model::CreateCave(int rows, int cols,
                       std::pair<int, int> death_birth_limits) {
  cave_ = Cave(rows, cols, death_birth_limits);
  error_ = cave_.GetError();
}

void Model::CreateCave(const std::string& file_name,
                       std::pair<int, int> death_birth_limits) {
  cave_ = Cave(file_name, death_birth_limits);
  error_ = cave_.GetError();
}

bool Model::GetCaveEnd() { return cave_.GetThisEnd(); }

void Model::UpdateCave() { cave_.UpdateCaveMap(); }

int Model::GetRows(MODEL_TYPE type) {
  int result = 0;
  if (type == CAVE)
    result = cave_.GetRows();
  else if (type == MAZE)
    result = maze_.GetRows();
  return result;
}

int Model::GetCols(MODEL_TYPE type) {
  int result = 0;
  if (type == CAVE)
    result = cave_.GetCols();
  else if (type == MAZE)
    result = maze_.GetCols();
  return result;
}

void Model::CreateMaze(const std::string& file_name) {
  maze_ = Maze(file_name);
  error_ = maze_.GetError();
}

void Model::CreateMaze(int rows, int cols) {
  maze_ = Maze(rows, cols);
  error_ = maze_.GetError();
}

void Model::CreateMazeWay(std::pair<int, int> start, std::pair<int, int> end) {
  maze_.FindPath(start, end);
  error_ = maze_.GetError();
}
bool Model::operator()(int row, int col, enum Model_matrix_type type) {
  bool result = false;
  if (type == MAZE_RIGHT) {
    result = maze_(row, col, M_RIGHT);
  } else if (type == MAZE_BOTTOM) {
    result = maze_(row, col, M_BOTTOM);
  } else if (type == CAVE) {
    result = cave_(row, col);
  } else {
    error_ = true;
  }
  return result;
}
std::vector<Direction> Model::GetMazeWay() { return maze_.GetPath(); }
