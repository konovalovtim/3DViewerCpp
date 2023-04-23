#include "moving.h"

using namespace s21;

void Model::Rotate(double angle, Model::Axis axis) {
  if (axis == xAxis) {
    double tmp_first{}, tmp_second{};
    for (std::size_t index = 3; index < model.vertexes_.size(); index += 3) {
      tmp_first = model.vertexes_[index + yAxis];
      tmp_second = model.vertexes_[index + zAxis];
      model.vertexes_[index + yAxis] =
          cos(angle) * tmp_first - sin(angle) * tmp_second;
      model.vertexes_[index + zAxis] =
          cos(angle) * tmp_second + sin(angle) * tmp_first;
    }
  } else if (axis == yAxis) {
    double tmp_first{}, tmp_second{};
    for (std::size_t index = 3; index < model.vertexes_.size(); index += 3) {
      tmp_first = model.vertexes_[index + xAxis];
      tmp_second = model.vertexes_[index + zAxis];
      model.vertexes_[index + zAxis] =
          cos(angle) * tmp_second - sin(angle) * tmp_first;
      model.vertexes_[index + xAxis] =
          cos(angle) * tmp_first + sin(angle) * tmp_second;
    }
  } else if (axis == zAxis) {
    double tmp_first{}, tmp_second{};
    for (std::size_t index = 3; index < model.vertexes_.size(); index += 3) {
      tmp_first = model.vertexes_[index + xAxis];
      tmp_second = model.vertexes_[index + yAxis];
      model.vertexes_[index + xAxis] =
          cos(angle) * tmp_first - sin(angle) * tmp_second;
      model.vertexes_[index + yAxis] =
          cos(angle) * tmp_second + sin(angle) * tmp_first;
    }
  }
}

void Model::MoveReal(double coordinate, Model::AxisPoints axis) {
  for (std::size_t index = axis + 3; index < model.vertexes_.size();
       index += 3) {
    model.vertexes_[index] += coordinate;
  }
}

void Model::Move(double coordinate, Model::AxisPoints axis) {
  move_coordinate[axis] += coordinate;
}

void Model::Scale(double coordinate) {
  coordinate = coordinate / 100.;
  for (std::size_t index = 0; index < model.vertexes_.size(); index++) {
    model.vertexes_[index] *= coordinate;
  }
}

void Model::NormalizationAndCentralize() {
  if (model.vertexes_.empty()) {
    throw std::logic_error("Can't relocate. Haven't exist model");
  }
  double positionAxis[6] = {DBL_MAX,  DBL_MAX,  DBL_MAX,
                            -DBL_MAX, -DBL_MAX, -DBL_MAX};
  for (std::size_t index = 0; index < model.vertexes_.size(); index += 3) {
    positionAxis[xAxis] =
        std::min(positionAxis[xAxis], model.vertexes_[index + xAxis]);
    positionAxis[yAxis] =
        std::min(positionAxis[yAxis], model.vertexes_[index + yAxis]);
    positionAxis[zAxis] =
        std::min(positionAxis[zAxis], model.vertexes_[index + zAxis]);
    positionAxis[xAxis + 3] =
        std::max(positionAxis[xAxis + 3], model.vertexes_[index + xAxis]);
    positionAxis[yAxis + 3] =
        std::max(positionAxis[yAxis + 3], model.vertexes_[index + yAxis]);
    positionAxis[zAxis + 3] =
        std::max(positionAxis[zAxis + 3], model.vertexes_[index + zAxis]);
  }
  double deltaAxis[3] = {positionAxis[xAxis + 3] - positionAxis[xAxis],
                         positionAxis[yAxis + 3] - positionAxis[yAxis],
                         positionAxis[zAxis + 3] - positionAxis[zAxis]};
  MoveReal(-(positionAxis[xAxis] + deltaAxis[xAxis] / 2), xAxis);
  MoveReal(-(positionAxis[yAxis] + deltaAxis[yAxis] / 2), yAxis);
  MoveReal(-(positionAxis[zAxis] + deltaAxis[zAxis] / 2), zAxis);
  Scale(100 / std::max(std::max(deltaAxis[xAxis], deltaAxis[yAxis]),
                       deltaAxis[zAxis]));
  move_coordinate[xAxis] = move_coordinate[yAxis] = move_coordinate[zAxis] =
      0.f;
}

void Model::CentralizeAfterMove() {
  move_coordinate[xAxis] = move_coordinate[yAxis] = move_coordinate[zAxis] =
      0.f;
}