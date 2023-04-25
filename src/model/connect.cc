#include "connect.h"

using namespace s21;

void Model::ParsingVertex(std::string &line) {
  int count_vertex{};
  char *token = std::strtok(const_cast<char *>(line.data() + 1), " ");
  while (token) {
    if (*token == '\r') {
      break;
    }
    ++count_vertex;
    vertexes_.push_back(std::stod(token));
    token = strtok(nullptr, " ");
  }
  if (count_vertex != 3) {
    throw std::invalid_argument("Invalid file .obj");
  }
}

void Model::ParsingFacet(std::string &line,
                         std::size_t &position_old_vertexes) {
  if (vertexes_.empty()) {
    throw std::invalid_argument("Invalid file .obj");
  }
  char *token = std::strtok(const_cast<char *>(line.data() + 1), " ");
  std::vector<unsigned> face{};
  while (token) {
    long tmp = std::stol(token);
    if (tmp < 0) {
      face.push_back(position_old_vertexes + tmp);
    } else {
      face.push_back(tmp - 1);
    }
    if (face.back() >= position_old_vertexes) {
      throw std::invalid_argument("Invalid file .obj");
    }
    token = strtok(nullptr, " ");
    if (!token || *token == '\r') {
      break;
    }
  }
  facets_.push_back(face);
}

void Model::OpenObject(std::string line) {
  std::ifstream file_in(line);
  std::size_t position_old_vertexes{};
  while (std::getline(file_in, line)) {
    if (line.length() < 2) {
      continue;
    }
    if (line[0] == 'v' && line[1] == ' ') {
      ParsingVertex(line);
      position_old_vertexes += 1;
    } else if (line[0] == 'f') {
      ParsingFacet(line, position_old_vertexes);
    }
  }
}

void Model::Rotate(double angle, Model::Axis axis) {
  if (axis == xAxis) {
    double tmp_first{}, tmp_second{};
    for (std::size_t index = 3; index < vertexes_.size(); index += 3) {
      tmp_first = vertexes_[index + yAxis];
      tmp_second = vertexes_[index + zAxis];
      vertexes_[index + yAxis] =
          cos(angle) * tmp_first - sin(angle) * tmp_second;
      vertexes_[index + zAxis] =
          cos(angle) * tmp_second + sin(angle) * tmp_first;
    }
  } else if (axis == yAxis) {
    double tmp_first{}, tmp_second{};
    for (std::size_t index = 3; index < vertexes_.size(); index += 3) {
      tmp_first = vertexes_[index + xAxis];
      tmp_second = vertexes_[index + zAxis];
      vertexes_[index + zAxis] =
          cos(angle) * tmp_second - sin(angle) * tmp_first;
      vertexes_[index + xAxis] =
          cos(angle) * tmp_first + sin(angle) * tmp_second;
    }
  } else if (axis == zAxis) {
    double tmp_first{}, tmp_second{};
    for (std::size_t index = 3; index < vertexes_.size(); index += 3) {
      tmp_first = vertexes_[index + xAxis];
      tmp_second = vertexes_[index + yAxis];
      vertexes_[index + xAxis] =
          cos(angle) * tmp_first - sin(angle) * tmp_second;
      vertexes_[index + yAxis] =
          cos(angle) * tmp_second + sin(angle) * tmp_first;
    }
  }
}

void Model::MoveReal(double coordinate, Model::AxisPoints axis) {
  for (std::size_t index = axis + 3; index < vertexes_.size(); index += 3) {
    vertexes_[index] += coordinate;
  }
}

void Model::Move(double coordinate, Model::AxisPoints axis) {
  move_coordinate_[axis] += coordinate;
}

void Model::Scale(double coordinate) {
  coordinate = coordinate / 100.;
  for (std::size_t index = 0; index < vertexes_.size(); index++) {
    vertexes_[index] *= coordinate;
  }
}

void Model::NormalizationAndCentralize() {
  if (vertexes_.empty()) {
    throw std::logic_error("Can't relocate. Haven't exist model");
  }
  double positionAxis[6] = {DBL_MAX,  DBL_MAX,  DBL_MAX,
                            -DBL_MAX, -DBL_MAX, -DBL_MAX};
  for (std::size_t index = 0; index < vertexes_.size(); index += 3) {
    positionAxis[xAxis] =
        std::min(positionAxis[xAxis], vertexes_[index + xAxis]);
    positionAxis[yAxis] =
        std::min(positionAxis[yAxis], vertexes_[index + yAxis]);
    positionAxis[zAxis] =
        std::min(positionAxis[zAxis], vertexes_[index + zAxis]);
    positionAxis[xAxis + 3] =
        std::max(positionAxis[xAxis + 3], vertexes_[index + xAxis]);
    positionAxis[yAxis + 3] =
        std::max(positionAxis[yAxis + 3], vertexes_[index + yAxis]);
    positionAxis[zAxis + 3] =
        std::max(positionAxis[zAxis + 3], vertexes_[index + zAxis]);
  }
  double deltaAxis[3] = {positionAxis[xAxis + 3] - positionAxis[xAxis],
                         positionAxis[yAxis + 3] - positionAxis[yAxis],
                         positionAxis[zAxis + 3] - positionAxis[zAxis]};
  MoveReal(-(positionAxis[xAxis] + deltaAxis[xAxis] / 2), xAxis);
  MoveReal(-(positionAxis[yAxis] + deltaAxis[yAxis] / 2), yAxis);
  MoveReal(-(positionAxis[zAxis] + deltaAxis[zAxis] / 2), zAxis);
  Scale(100 / std::max(std::max(deltaAxis[xAxis], deltaAxis[yAxis]),
                       deltaAxis[zAxis]));
  move_coordinate_[xAxis] = move_coordinate_[yAxis] = move_coordinate_[zAxis] =
      0.f;
}

void Model::CentralizeAfterMove() {
  move_coordinate_[xAxis] = move_coordinate_[yAxis] = move_coordinate_[zAxis] =
      0.f;
}

std::pair<std::size_t, std::size_t> Model::size() {
  return {vertexes_.size(), facets_.size()};
}

bool Model::empty() { return vertexes_.empty() && facets_.empty(); }

void Model::clear() {
  facets_.clear();
  vertexes_.clear();
  CentralizeAfterMove();
  prepare_data.clear();
}

const std::vector<double> &Model::GetVertexes(double width, double height) {
  char state_scaling{};
  double scale{};
  if (width > height) {
    state_scaling = 1;
    scale = height / width;
  } else if (height > width) {
    state_scaling = 2;
    scale = width / height;
  }

  prepare_data.clear();
  std::copy(vertexes_.begin(), vertexes_.end(),
            std::back_inserter(prepare_data));
  for (std::size_t index = 3; index < prepare_data.size(); index += 3) {
    prepare_data[index + xAxis] += move_coordinate_[xAxis];
    prepare_data[index + yAxis] += move_coordinate_[yAxis];
    prepare_data[index + zAxis] += move_coordinate_[zAxis];
    if (state_scaling == 1) {
      prepare_data[index + xAxis] *= scale;
    } else if (state_scaling == 2) {
      prepare_data[index + yAxis] *= scale;
    }
  }
  return prepare_data;
}

const std::vector<std::vector<unsigned>> &Model::GetFacets() { return facets_; }