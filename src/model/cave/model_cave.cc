//
// Created by Rebbecca Gormond on 9/25/22.
//
#include "model_cave.h"

using namespace s21;

Cave::Cave(int rows, int cols, std::pair<int, int> death_birth_limits) {
  this_end_ = false;
  death_limit_ = death_birth_limits.first;
  birth_limit_ = death_birth_limits.second;
  cave_map_ = Matrix<bool>(rows, cols);
  RandomCave_();
  error_ = cave_map_.GetError();
}

Cave::Cave(const std::string& file_name,
           std::pair<int, int> death_birth_limits) {
  Parser parser(file_name);
  parser.FillMatrix(cave_map_);
  death_limit_ = death_birth_limits.first;
  birth_limit_ = death_birth_limits.second;
  error_ = parser.GetError();
}

void Cave::RandomCave_() {
  for (auto i = 0; i < cave_map_.GetRows(); ++i)
    for (auto j = 0; j < cave_map_.GetCols(); ++j)
      cave_map_(i, j) = RandomGenerate_();
}

bool Cave::RandomGenerate_() {
  std::random_device rd;
  std::default_random_engine engine(rd());
  std::uniform_int_distribution<int> dist(0, 1);
  return static_cast<bool>(dist(engine));
}

void Cave::UpdateCaveMap() {
  if (!this_end_) {
    Matrix<bool> tmp_cave_map(cave_map_);

    for (int i = 0; i < cave_map_.GetRows(); ++i) {
      for (int j = 0; j < cave_map_.GetCols(); ++j) {
        int nbs = CountAliveNeighbor_(tmp_cave_map, i, j);
        if (tmp_cave_map(i, j))
          cave_map_(i, j) = (nbs < death_limit_);
        else
          cave_map_(i, j) = (nbs <= birth_limit_);
      }
    }
    if (tmp_cave_map == cave_map_ || cave_old_map_ == cave_map_)
      this_end_ = true;

    cave_old_map_ = tmp_cave_map;
  }
}

int Cave::CountAliveNeighbor_(Matrix<bool>& sample_matrix, int row, int col) {
  int count = 0;
  for (int i = -1; i < 2; ++i) {
    for (int j = -1; j < 2; ++j) {
      if (i == 0 && j == 0)
        continue;
      else if ((row + i) < 0 || (col + j) < 0 ||
               (row + i) >= sample_matrix.GetRows() ||
               (col + j) >= sample_matrix.GetCols() ||
               sample_matrix((row + i), (col + j))) {
        count++;
      }
    }
  }
  return count;
}

int Cave::GetRows() const { return cave_map_.GetRows(); }

int Cave::GetCols() const { return cave_map_.GetCols(); }

bool Cave::GetThisEnd() const { return this_end_; }

bool Cave::operator()(int row, int col) { return cave_map_(row, col); }

int Cave::GetError() const { return error_; }
