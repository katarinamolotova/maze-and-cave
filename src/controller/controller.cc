//
// Created by Manhunter Groot on 9/24/22.
//

#include "controller.h"

#include <utility>

namespace s21 {

Controller* Controller::controller_ = nullptr;

void Controller::ReadCave(const std::string& file_name,
                          std::pair<int, int> death_birth_limits) {
  model_->CreateCave(file_name, death_birth_limits);
}

void Controller::ReadMaze(const std::string& file_name) {
  model_->CreateMaze(file_name);
}

int s21::Controller::GetRowsCave() { return model_->GetRows(CAVE); }
int s21::Controller::GetColsCave() { return model_->GetCols(CAVE); }

void Controller::GenerationCave(int rows, int cols,
                                std::pair<int, int> death_birth_limits) {
  model_->CreateCave(rows, cols, death_birth_limits);
}

bool Controller::GetCave(int x, int y) {
  return model_->operator()(x, y, CAVE);
}

void Controller::GenerateMaze(int rows, int cols) {
  model_->CreateMaze(rows, cols);
}

std::pair<bool, bool> Controller::GetMazeBorders(int row, int col) {
  return {model_->operator()(row, col, MAZE_RIGHT),
          model_->operator()(row, col, MAZE_BOTTOM)};
}

void Controller::UpdateCave() { model_->UpdateCave(); }

int Controller::GetRowsMaze() { return model_->GetRows(MAZE); }

int Controller::GetColsMaze() { return model_->GetCols(MAZE); }

bool Controller::GetFlagEnd() { return model_->GetCaveEnd(); }

std::vector<Direction> Controller::GetMazeWay() { return model_->GetMazeWay(); }
void Controller::CreateMazeWay(std::pair<int, int> start,
                               std::pair<int, int> end) {
  model_->CreateMazeWay(start, end);
}

}  // namespace s21
