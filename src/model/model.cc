#include "model.h"

using namespace s21;

std::pair<std::size_t, std::size_t> Model::size() {
  return {model.vertexes.size(), model.facets.size()};
}

bool Model::empty() { return model.vertexes.empty() && model.facets.empty(); }

void Model::clear() {
  model.facets.clear();
  model.vertexes.clear();
  CentralizeAfterMove();
  vertexesAfterGetVertexes.clear();
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

  vertexesAfterGetVertexes.clear();
  std::copy(model.vertexes.begin(), model.vertexes.end(),
            std::back_inserter(vertexesAfterGetVertexes));
  for (std::size_t index = 0; index < vertexesAfterGetVertexes.size();
       index += 3) {
    vertexesAfterGetVertexes[index + xAxis] += axisMovement[xAxis];
    vertexesAfterGetVertexes[index + yAxis] += axisMovement[yAxis];
    vertexesAfterGetVertexes[index + zAxis] += axisMovement[zAxis];
    if (state_scaling == 1) {
      vertexesAfterGetVertexes[index + xAxis] *= scale;
    } else if (state_scaling == 2) {
      vertexesAfterGetVertexes[index + yAxis] *= scale;
    }
  }
  return vertexesAfterGetVertexes;
}

const std::vector<std::vector<unsigned>> &Model::GetFacets() {
  return model.facets;
}

void Model::Memento::takeFortune(Model &other) {
  Memento_axisMovement[xAxis] = other.axisMovement[xAxis];
  Memento_axisMovement[yAxis] = other.axisMovement[yAxis];
  Memento_axisMovement[zAxis] = other.axisMovement[zAxis];
  for (size_t i = 0; i < other.model.vertexes.size(); i++) {
    Memento_model.vertexes.push_back(other.model.vertexes[i]);
  }
  for (size_t i = 0; i < other.model.facets.size(); i++) {
    std::vector<unsigned> vect{};
    for (size_t j = 0; j < other.model.facets[i].size(); j++) {
      vect.push_back(other.model.facets[i][j]);
    }
    Memento_model.facets.push_back(vect);
  }
}

void Model::Memento::recovery(Model &other) {
  other.clear();
  other.axisMovement[xAxis] = Memento_axisMovement[xAxis];
  other.axisMovement[yAxis] = Memento_axisMovement[yAxis];
  other.axisMovement[zAxis] = Memento_axisMovement[zAxis];
  for (size_t i = 0; i < Memento_model.vertexes.size(); i++) {
    other.model.vertexes.push_back(Memento_model.vertexes[i]);
  }
  for (size_t i = 0; i < Memento_model.facets.size(); i++) {
    std::vector<unsigned> vect{};
    for (size_t j = 0; j < Memento_model.facets[i].size(); j++) {
      vect.push_back(Memento_model.facets[i][j]);
    }
    other.model.facets.push_back(vect);
  }
}

void Model::Memento::clear() {
  Memento_model.facets.clear();
  Memento_model.vertexes.clear();
  Memento_vertexesAfterGetVertexes.clear();
}
