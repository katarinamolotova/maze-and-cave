//
// Created by Manhunter Groot on 9/24/22.
//

#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include "../model/model_facade.h"

namespace s21 {

class Controller {
 private:
  static Controller *controller_;
  Model *model_;
  Controller() { model_ = s21::Model::GetInstance(); }
  ~Controller() { delete controller_; }

 public:
  static Controller *GetInstance() {
    if (!controller_) controller_ = new Controller();
    return controller_;
  }

  void GenerateMaze(int rows, int cols);
  std::pair<bool, bool> GetMazeBorders(int row, int col);

  void ReadCave(const std::string &file_name,
                std::pair<int, int> death_birth_limits);
  void ReadMaze(const std::string &file_name);
  void UpdateCave();
  void GenerationCave(int rows, int cols,
                      std::pair<int, int> death_birth_limits);
  bool GetCave(int x, int y);
  int GetRowsCave();
  int GetColsCave();
  int GetRowsMaze();
  int GetColsMaze();
  bool GetFlagEnd();
  void CreateMazeWay(std::pair<int, int> start, std::pair<int, int> end);
  std::vector<Direction> GetMazeWay();
  [[maybe_unused]] bool GetError() { return model_->GetError(); }
};

}  // namespace s21

#endif  // SRC_CONTROLLER_CONTROLLER_H_
