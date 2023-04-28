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

void Model::Memento::take(Model &other) {
  Memento_axisMovement[xAxis] = other.axisMovement[xAxis];
  Memento_axisMovement[yAxis] = other.axisMovement[yAxis];
  Memento_axisMovement[zAxis] = other.axisMovement[zAxis];
  for (int i = 0; i < other.vertexesAfterGetVertexes.size(); i++) {
    Memento_vertexesAfterGetVertexes.push_back(
        other.vertexesAfterGetVertexes[i]);
  }
  for (int i = 0; i < other.model.vertexes.size(); i++) {
    Memento_model.vertexes.push_back(
        other.model.vertexes[i]);
  }
//  for (auto &model_parse : other.model) {
//    model.vertexes.insert(model.vertexes.end(), model_parse.vertexes.begin(),
//                          model_parse.vertexes.end());
//    model.facets.insert(model.facets.end(), model_parse.facets.begin(),
//                        model_parse.facets.end());
//  }

//  std::copy(other.model.vertexes.begin(), other.model.vertexes.end(),
//            Memento_model.vertexes.begin());
//  std::copy(other.model.facets.begin(), other.model.facets.end(),
//            Memento_model.facets.begin());
  //  for (int i = 0; i < other.model.vertexes.size(); i++) {
  //    Memento_model.vertexes.push_back(other.model.vertexes[i]);
  //  }
}

void Model::Memento::recovery(Model &other) {
  other.clear();
  other.axisMovement[xAxis] = Memento_axisMovement[xAxis];
  other.axisMovement[yAxis] = Memento_axisMovement[yAxis];
  other.axisMovement[zAxis] = Memento_axisMovement[zAxis];
//  for (int i = 0; i < other.vertexesAfterGetVertexes.size(); i++) {
//    Memento_vertexesAfterGetVertexes.push_back(
//        other.vertexesAfterGetVertexes[i]);
//  }
  std::copy(Memento_vertexesAfterGetVertexes.begin(), Memento_vertexesAfterGetVertexes.end(),
            other.vertexesAfterGetVertexes.begin());
  std::copy(Memento_model.vertexes.begin(), Memento_model.vertexes.end(),
            other.model.vertexes.begin());
  std::copy(Memento_model.facets.begin(), Memento_model.facets.end(),
            other.model.facets.begin());
}
