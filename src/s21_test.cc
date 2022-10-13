#include <gtest/gtest.h>

#include "model/cave/model_cave.h"
#include "model/maze/model_maze.h"

class GenerationMaze : public testing::Test {
 protected:
  void SetUp() {}
  void TearDown() {}
};

TEST_F(GenerationMaze, randomMaze) {
  s21::Maze first_maze(10, 10);
  s21::Maze second_maze(10, 10);

  bool result = true;
  for (int i = 0; i < second_maze.GetRows() && result; i++) {
    for (int j = 0; j < second_maze.GetCols() && result; j++) {
      if (second_maze(i, j, s21::M_RIGHT) != first_maze(i, j, s21::M_RIGHT))
        result = false;
    }
  }

  EXPECT_EQ(result, false);
}

TEST_F(GenerationMaze, readMaze) {
  s21::Maze first_maze("../datasets/test_small_maze.txt");
  std::vector<int> right_result = {0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0,
                                   1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1};
  std::vector<int> bottom_result = {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1,
                                    0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1};

  int index = 0;
  for (int i = 0; i < first_maze.GetRows(); i++) {
    for (int j = 0; j < first_maze.GetCols(); j++, index++) {
      bool right = first_maze(i, j, s21::M_RIGHT);
      bool bottom = first_maze(i, j, s21::M_BOTTOM);
      EXPECT_EQ(right, right_result[index]);
      EXPECT_EQ(bottom, bottom_result[index]);
    }
  }
}

TEST_F(GenerationMaze, solutionMaze) {
  s21::Maze first_maze("../datasets/test_maze.txt");
  first_maze.FindPath(std::make_pair(0, 0), std::make_pair(9, 9));
  std::vector<s21::Direction> maze_way = first_maze.GetPath();
  std::vector<int> result_way = {3, 3, 1, 3, 0, 3, 3, 3, 3, 1,
                                 3, 3, 1, 1, 1, 1, 1, 1, 1, 1};

  for (size_t i = 0; i < result_way.size(); i++)
    EXPECT_EQ(maze_way[i], result_way[i]);
}

class GenerationCave : public testing::Test {
 protected:
  void SetUp() {}
  void TearDown() {}
};

TEST_F(GenerationCave, randomCave) {
  s21::Cave first_cave(10, 10, std::make_pair(4, 4));
  s21::Cave second_cave(10, 10, std::make_pair(4, 4));

  bool result = true;
  for (int i = 0; i < first_cave.GetRows() && result; i++) {
    for (int j = 0; j < first_cave.GetCols() && result; j++) {
      if (first_cave(i, j) != second_cave(i, j)) result = false;
    }
  }

  EXPECT_EQ(result, false);
}

TEST_F(GenerationCave, finalCave) {
  s21::Cave second_cave("../datasets/result_test_cave.txt",
                        std::make_pair(4, 4));
  s21::Cave first_cave("../datasets/semple3.txt", std::make_pair(4, 4));

  while (!first_cave.GetThisEnd()) first_cave.UpdateCaveMap();

  for (int i = 0; i < first_cave.GetRows(); i++)
    for (int j = 0; j < first_cave.GetCols(); j++)
      EXPECT_EQ(first_cave(i, j), second_cave(i, j));
}

TEST_F(GenerationCave, updateCave) {
  s21::Cave first_cave(10, 10, std::make_pair(4, 4));
  s21::Cave second_cave(10, 10, std::make_pair(4, 4));

  first_cave.UpdateCaveMap();
  bool result = true;
  for (int i = 0; i < first_cave.GetRows() && result; i++) {
    for (int j = 0; j < first_cave.GetCols() && result; j++) {
      if (first_cave(i, j) != second_cave(i, j)) result = false;
    }
  }

  EXPECT_EQ(result, false);
}

TEST_F(GenerationCave, readCave) {
  s21::Cave second_cave("../datasets/test_small_cave.txt",
                        std::make_pair(4, 4));
  std::vector<int> result = {1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0,
                             0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0};

  int index = 0;
  for (int i = 0; i < second_cave.GetRows(); i++)
    for (int j = 0; j < second_cave.GetCols(); j++, index++)
      EXPECT_EQ(second_cave(i, j), result[index]);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
