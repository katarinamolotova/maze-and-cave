//
// Created by Rebbecca Gormond on 9/27/22.
//

#ifndef SRC_MODEL_MODEL_FACADE_H_
#define SRC_MODEL_MODEL_FACADE_H_

#include "cave/model_cave.h"
#include "maze/model_maze.h"

namespace s21 {

typedef enum Model_matrix_type {
  CAVE,
  MAZE,
  MAZE_RIGHT,
  MAZE_BOTTOM
} MODEL_TYPE;

class Model {
 private:
  Cave cave_;
  Maze maze_;
  bool error_{false};

  static Model* model_;
  Model() = default;
  ~Model() { delete model_; }

 public:
  static Model* GetInstance() {
    if (!model_) model_ = new Model();
    return model_;
  }

  void CreateCave(int rows, int cols, std::pair<int, int> death_birth_limits);
  void CreateCave(const std::string& file_name,
                  std::pair<int, int> death_birth_limits);
  bool GetCaveEnd();
  void UpdateCave();
  void CreateMaze(const std::string& file_name);
  void CreateMaze(int rows, int cols);
  void CreateMazeWay(std::pair<int, int> start, std::pair<int, int> end);
  int GetRows(MODEL_TYPE type);
  int GetCols(MODEL_TYPE type);
  [[nodiscard]] bool GetError() const { return error_; }
  bool operator()(int row, int col, MODEL_TYPE type);
  std::vector<Direction> GetMazeWay();
};

}  // namespace s21

#endif  //  SRC_MODEL_MODEL_FACADE_H_
