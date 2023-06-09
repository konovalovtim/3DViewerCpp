#include <gtest/gtest.h>

#include "../model/model.h"

struct ExampleObject {
  std::vector<double> vertexesData{0.0, 0.0, 0.0, 0.0, 0.0, 2.0, 0.0, 2.0,
                                   0.0, 0.0, 2.0, 2.0, 2.0, 0.0, 0.0, 2.0,
                                   0.0, 2.0, 2.0, 2.0, 0.0, 2.0, 2.0, 2.0,
                                   2.0, 2.0, 0.0, 2.0, 2.0, 2.0};
  std::vector<std::vector<unsigned>> facetsData{
      {0, 6, 4}, {0, 2, 6}, {0, 3, 2}, {0, 1, 3}, {2, 7, 6},
      {2, 3, 7}, {4, 6, 7}, {4, 7, 5}, {0, 4, 5}, {0, 5, 1}};
};

TEST(parsing, parsingObject) {
  s21::Model &object = *s21::Model::GetInstance();
  object.OpenObject("tests/test.txt");
  ExampleObject pattern;
  EXPECT_EQ(pattern.vertexesData.size(), 30);
  for (std::size_t index{}; index < pattern.vertexesData.size(); ++index) {
    EXPECT_NEAR(pattern.vertexesData[index], object.GetVertexes()[index], 1e-6);
  }
  for (std::size_t i{}; i < pattern.facetsData.size(); ++i) {
    for (std::size_t j{}; j < pattern.facetsData[i].size(); ++j) {
      EXPECT_EQ(pattern.facetsData[i][j], object.GetFacets()[i][j]);
    }
  }
  EXPECT_EQ(object.size().first, 30);
  EXPECT_EQ(object.size().second, 10);
  EXPECT_FALSE(object.empty());
  object.clear();
}

TEST(parsing, clearObject) {
  s21::Model &object = *s21::Model::GetInstance();
  object.OpenObject("tests/test.txt");
  EXPECT_FALSE(object.empty());
  object.clear();
  EXPECT_TRUE(object.empty());
  object.clear();
}

TEST(moving, normalization) {
  s21::Model &object = *s21::Model::GetInstance();
  object.OpenObject("tests/test.txt");
  object.NormalizationAndCentralize();
  for (std::size_t index{}; index < object.GetVertexes().size(); ++index) {
    EXPECT_NEAR(std::fabs(object.GetVertexes()[index]), 0.5, 1e-6);
  }
  object.clear();
}

TEST(moving, getVertexes) {
  s21::Model &object = *s21::Model::GetInstance();
  object.OpenObject("tests/test.txt");
  auto &dataVertexes = object.GetVertexes(2, 1);
  ExampleObject pattern;
  for (std::size_t index{}; index < pattern.vertexesData.size(); index += 3) {
    EXPECT_NEAR(pattern.vertexesData[index + s21::Model::xAxis] * 0.5,
                dataVertexes[index + s21::Model::xAxis], 1e-6);
    EXPECT_NEAR(pattern.vertexesData[index + s21::Model::yAxis],
                dataVertexes[index + s21::Model::yAxis], 1e-6);
    EXPECT_NEAR(pattern.vertexesData[index + s21::Model::zAxis],
                dataVertexes[index + s21::Model::zAxis], 1e-6);
  }
  object.clear();
}

TEST(moving, getVertexes2) {
  s21::Model &object = *s21::Model::GetInstance();
  object.OpenObject("tests/test.txt");
  auto &dataVertexes = object.GetVertexes(1, 2);
  ExampleObject pattern;
  for (std::size_t index{}; index < pattern.vertexesData.size(); index += 3) {
    EXPECT_NEAR(pattern.vertexesData[index + s21::Model::xAxis],
                dataVertexes[index + s21::Model::xAxis], 1e-6);
    EXPECT_NEAR(pattern.vertexesData[index + s21::Model::yAxis] * 0.5,
                dataVertexes[index + s21::Model::yAxis], 1e-6);
    EXPECT_NEAR(pattern.vertexesData[index + s21::Model::zAxis],
                dataVertexes[index + s21::Model::zAxis], 1e-6);
  }
  object.clear();
}

TEST(moving, rotateX) {
  s21::Model &object = *s21::Model::GetInstance();
  object.OpenObject("tests/test.txt");
  double angle = 2;
  object.Rotate(angle, s21::Model::xAxis);
  auto &dataVertexes = object.GetVertexes();
  ExampleObject pattern;
  for (std::size_t index{}; index < pattern.vertexesData.size(); index += 3) {
    double tmp_first = pattern.vertexesData[index + s21::Model::yAxis],
           tmp_second = pattern.vertexesData[index + s21::Model::zAxis];
    EXPECT_NEAR(pattern.vertexesData[index + s21::Model::xAxis],
                dataVertexes[index + s21::Model::xAxis], 1e-6);
    EXPECT_NEAR(cos(angle) * tmp_first - sin(angle) * tmp_second,
                dataVertexes[index + s21::Model::yAxis], 1e-6);
    EXPECT_NEAR(cos(angle) * tmp_second + sin(angle) * tmp_first,
                dataVertexes[index + s21::Model::zAxis], 1e-6);
  }
  object.clear();
}

TEST(moving, rotateX2) {
  s21::Model &object = *s21::Model::GetInstance();
  object.OpenObject("tests/test.txt");
  double angle = -234;
  object.Rotate(angle, s21::Model::xAxis);
  auto &dataVertexes = object.GetVertexes();
  ExampleObject pattern;
  for (std::size_t index{}; index < pattern.vertexesData.size(); index += 3) {
    double tmp_first = pattern.vertexesData[index + s21::Model::yAxis],
           tmp_second = pattern.vertexesData[index + s21::Model::zAxis];
    EXPECT_NEAR(pattern.vertexesData[index + s21::Model::xAxis],
                dataVertexes[index + s21::Model::xAxis], 1e-6);
    EXPECT_NEAR(cos(angle) * tmp_first - sin(angle) * tmp_second,
                dataVertexes[index + s21::Model::yAxis], 1e-6);
    EXPECT_NEAR(cos(angle) * tmp_second + sin(angle) * tmp_first,
                dataVertexes[index + s21::Model::zAxis], 1e-6);
  }
  object.clear();
}

TEST(moving, rotateY) {
  s21::Model &object = *s21::Model::GetInstance();
  object.OpenObject("tests/test.txt");
  double angle = 15;
  object.Rotate(angle, s21::Model::yAxis);
  auto &dataVertexes = object.GetVertexes();
  ExampleObject pattern;
  for (std::size_t index{}; index < pattern.vertexesData.size(); index += 3) {
    double tmp_first = pattern.vertexesData[index + s21::Model::xAxis],
           tmp_second = pattern.vertexesData[index + s21::Model::zAxis];
    EXPECT_NEAR(cos(angle) * tmp_first + sin(angle) * tmp_second,
                dataVertexes[index + s21::Model::xAxis], 1e-6);
    EXPECT_NEAR(pattern.vertexesData[index + s21::Model::yAxis],
                dataVertexes[index + s21::Model::yAxis], 1e-6);
    EXPECT_NEAR(cos(angle) * tmp_second - sin(angle) * tmp_first,
                dataVertexes[index + s21::Model::zAxis], 1e-6);
  }
  object.clear();
}

TEST(moving, rotateY2) {
  s21::Model &object = *s21::Model::GetInstance();
  object.OpenObject("tests/test.txt");
  double angle = -57;
  object.Rotate(angle, s21::Model::yAxis);
  auto &dataVertexes = object.GetVertexes();
  ExampleObject pattern;
  for (std::size_t index{}; index < pattern.vertexesData.size(); index += 3) {
    double tmp_first = pattern.vertexesData[index + s21::Model::xAxis],
           tmp_second = pattern.vertexesData[index + s21::Model::zAxis];
    EXPECT_NEAR(cos(angle) * tmp_first + sin(angle) * tmp_second,
                dataVertexes[index + s21::Model::xAxis], 1e-6);
    EXPECT_NEAR(pattern.vertexesData[index + s21::Model::yAxis],
                dataVertexes[index + s21::Model::yAxis], 1e-6);
    EXPECT_NEAR(cos(angle) * tmp_second - sin(angle) * tmp_first,
                dataVertexes[index + s21::Model::zAxis], 1e-6);
  }
  object.clear();
}

TEST(moving, rotateZ) {
  s21::Model &object = *s21::Model::GetInstance();
  object.OpenObject("tests/test.txt");
  double angle = 543;
  object.Rotate(angle, s21::Model::zAxis);
  auto &dataVertexes = object.GetVertexes();
  ExampleObject pattern;
  for (std::size_t index{}; index < pattern.vertexesData.size(); index += 3) {
    double tmp_first = pattern.vertexesData[index + s21::Model::xAxis],
           tmp_second = pattern.vertexesData[index + s21::Model::yAxis];
    EXPECT_NEAR(cos(angle) * tmp_first - sin(angle) * tmp_second,
                dataVertexes[index + s21::Model::xAxis], 1e-6);
    EXPECT_NEAR(cos(angle) * tmp_second + sin(angle) * tmp_first,
                dataVertexes[index + s21::Model::yAxis], 1e-6);
    EXPECT_NEAR(pattern.vertexesData[index + s21::Model::zAxis],
                dataVertexes[index + s21::Model::zAxis], 1e-6);
  }
  object.clear();
}

TEST(moving, rotateZ2) {
  s21::Model &object = *s21::Model::GetInstance();
  object.OpenObject("tests/test.txt");
  double angle = -84;
  object.Rotate(angle, s21::Model::zAxis);
  auto &dataVertexes = object.GetVertexes();
  ExampleObject pattern;
  for (std::size_t index{}; index < pattern.vertexesData.size(); index += 3) {
    double tmp_first = pattern.vertexesData[index + s21::Model::xAxis],
           tmp_second = pattern.vertexesData[index + s21::Model::yAxis];
    EXPECT_NEAR(cos(angle) * tmp_first - sin(angle) * tmp_second,
                dataVertexes[index + s21::Model::xAxis], 1e-6);
    EXPECT_NEAR(cos(angle) * tmp_second + sin(angle) * tmp_first,
                dataVertexes[index + s21::Model::yAxis], 1e-6);
    EXPECT_NEAR(pattern.vertexesData[index + s21::Model::zAxis],
                dataVertexes[index + s21::Model::zAxis], 1e-6);
  }
  object.clear();
}

TEST(moving, move) {
  s21::Model &object = *s21::Model::GetInstance();
  object.OpenObject("tests/test.txt");
  double move_coords[3] = {42, -23, 1234};
  object.Move(move_coords[s21::Model::xAxis], s21::Model::xAxis);
  object.Move(move_coords[s21::Model::yAxis], s21::Model::yAxis);
  object.Move(move_coords[s21::Model::zAxis], s21::Model::zAxis);
  auto &dataVertexes = object.GetVertexes();
  ExampleObject pattern;
  for (std::size_t index{}; index < pattern.vertexesData.size(); index += 3) {
    EXPECT_NEAR(pattern.vertexesData[index + s21::Model::xAxis] +
                    move_coords[s21::Model::xAxis],
                dataVertexes[index + s21::Model::xAxis], 1e-6);
    EXPECT_NEAR(pattern.vertexesData[index + s21::Model::yAxis] +
                    move_coords[s21::Model::yAxis],
                dataVertexes[index + s21::Model::yAxis], 1e-6);
    EXPECT_NEAR(pattern.vertexesData[index + s21::Model::zAxis] +
                    move_coords[s21::Model::zAxis],
                dataVertexes[index + s21::Model::zAxis], 1e-6);
  }
  object.clear();
}

TEST(pattern, memento) {
  s21::Model &object = *s21::Model::GetInstance();

  object.OpenObject("tests/test.txt");
  ExampleObject pattern;
  EXPECT_EQ(pattern.vertexesData.size(), 30);
  for (std::size_t index{}; index < pattern.vertexesData.size(); ++index) {
    EXPECT_NEAR(pattern.vertexesData[index], object.GetVertexes()[index], 1e-6);
  }
  for (std::size_t i{}; i < pattern.facetsData.size(); ++i) {
    for (std::size_t j{}; j < pattern.facetsData[i].size(); ++j) {
      EXPECT_EQ(pattern.facetsData[i][j], object.GetFacets()[i][j]);
    }
  }
  EXPECT_EQ(object.size().first, 30);
  EXPECT_EQ(object.size().second, 10);
  EXPECT_FALSE(object.empty());

  s21::Model::Memento memento1;
  memento1.takeFortune(object);
  memento1.recovery(object);
  memento1.clear();
  object.clear();
}

TEST(errors, error) {
  s21::Model &object = *s21::Model::GetInstance();
  EXPECT_ANY_THROW(object.OpenObject("tests/invalid_test.txt"));
  EXPECT_TRUE(object.empty());
  object.clear();
}

TEST(errors, error2) {
  s21::Model &object = *s21::Model::GetInstance();
  EXPECT_ANY_THROW(object.OpenObject("tests/invalid_size_vertex.txt"));
  EXPECT_TRUE(object.empty());
  object.clear();
}

TEST(errors, error3) {
  s21::Model &object = *s21::Model::GetInstance();
  EXPECT_ANY_THROW(object.OpenObject("tests/invalid_facet.txt"));
  EXPECT_TRUE(object.empty());
  object.clear();
}

TEST(errors, normalizationError) {
  s21::Model &object = *s21::Model::GetInstance();
  EXPECT_ANY_THROW(object.NormalizationAndCentralize());
  object.clear();
}