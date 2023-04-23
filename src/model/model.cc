#include "model.h"

using namespace s21;

void PartObject::ParsingVertex(std::string &line) {
  int count_vertex = 0;
  char *token = std::strtok(const_cast<char *>(line.data() + 1), " ");
  while (token) {
    ++count_vertex;
    vertexes_.push_back(std::stod(token));
    token = strtok(nullptr, " ");
  }
  if (count_vertex != 3) {
    throw std::invalid_argument("Invalid file .obj");
  }
}

void PartObject::ParsingFacet(std::string &line,
                              std::size_t &position_old_vertexes) {
  if (vertexes_.empty()) {
    throw std::invalid_argument("Invalid file .obj");
  }
  char *token = std::strtok(const_cast<char *>(line.data() + 1), " ");
  std::vector<unsigned> face;
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

void PartObject::OpenObject(std::string line) {
  std::ifstream file_in(line);
  std::size_t position_old_vertexes;
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