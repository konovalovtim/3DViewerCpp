#include "model.h"

using namespace s21;

std::pair<std::size_t, std::size_t> Model::size() {
  return {model.vertexes.size(), model.facets.size()};
}

bool Model::empty() {
  return model.vertexes.empty() && model.facets.empty();
}

void Model::clear() {
  model.facets.clear();
  model.vertexes.clear();
  CentralizeAfterMove();
  vertexesAfterGetVertexes.clear();
}

const std::vector<double>& Model::GetVertexes(double width,
                                                    double height) {
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
  for (std::size_t index = 0; index < vertexesAfterGetVertexes.size(); index += 3) {
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

const std::vector<std::vector<unsigned>>& Model::GetFacets() {
  return model.facets;
}
