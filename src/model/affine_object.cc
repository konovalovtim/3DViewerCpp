#include "object_model.h"

using namespace s21;

void ObjectModel::Rotate(double angle, ObjectModel::Axis axis) {
  if (axis == xAxis) {
    double tmp_first{}, tmp_second{};
    for (std::size_t index = 0; index < model.vertexes.size(); index += 3) {
      tmp_first = model.vertexes[index + yAxis];
      tmp_second = model.vertexes[index + zAxis];
      model.vertexes[index + yAxis] =
          cos(angle) * tmp_first - sin(angle) * tmp_second;
      model.vertexes[index + zAxis] =
          cos(angle) * tmp_second + sin(angle) * tmp_first;
    }

  } else if (axis == yAxis) {
    double tmp_first{}, tmp_second{};
    for (std::size_t index = 0; index < model.vertexes.size(); index += 3) {
      tmp_first = model.vertexes[index + xAxis];
      tmp_second = model.vertexes[index + zAxis];
      model.vertexes[index + zAxis] =
          cos(angle) * tmp_second - sin(angle) * tmp_first;
      model.vertexes[index + xAxis] =
          cos(angle) * tmp_first + sin(angle) * tmp_second;
    }

  } else if (axis == zAxis) {
    double tmp_first{}, tmp_second{};
    for (std::size_t index = 0; index < model.vertexes.size(); index += 3) {
      tmp_first = model.vertexes[index + xAxis];
      tmp_second = model.vertexes[index + yAxis];
      model.vertexes[index + xAxis] =
          cos(angle) * tmp_first - sin(angle) * tmp_second;
      model.vertexes[index + yAxis] =
          cos(angle) * tmp_second + sin(angle) * tmp_first;
    }
  }
}

void ObjectModel::MoveReal(double coordinate, ObjectModel::AxisPoints axis) {
  for (std::size_t index = axis; index < model.vertexes.size(); index += 3) {
    model.vertexes[index] += coordinate;
  }
}

void ObjectModel::Move(double coordinate, ObjectModel::AxisPoints axis) {
  move_coordinate[axis] += coordinate;
}

void ObjectModel::Scale(double coordinate) {
  coordinate = coordinate / 100.;
  for (std::size_t index = 0; index < model.vertexes.size(); index++) {
    model.vertexes[index] *= coordinate;
  }
}
